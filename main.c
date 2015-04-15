#include <stdio.h>
#include <stdlib.h>
#include "helperFunctions.h"
#include "lineHandling.h"
#include "nodes.h"
#include "symCodeHash.h"
#include "opCodeHash.h"


int main(int argc, char* argv[])
{
    FILE* ioData[3] ;

    initDataIo(argv,ioData);//initialize files

    FILE* inFile    = ioData[0] ;//assembly source file
    FILE* labels    = ioData[1] ;//stores the labels and addresses
    FILE* interFile = ioData[2]; //stores the intermediate data from source file

    //initializers
    initSymHashTbl();//initializes symbols table
    initOpHashTbl();//initializes opcode table

    int startAddrs  = 0 ;//starting address of program
    int locctr  = 0 ;//address of current instruction

    char* line  = (char*)malloc(MAX_LINE_LENGTH);// stores the line obtained from file

    //counters
    int counter = 0 ; //counts the num of tokens in tokenized line
    int lineCount   = 0 ;

    tokenLine theLine ; // holds tokens from a parsed line

    //error codes for line
    errCodes errors[7] = {0} ;
    //keeps count of error codes
    int err = 0 ;



    //start loop that goes to every line of file ending at end of file
    while(!feof(inFile))
    {
        //reset error counter
        err = 0 ;

        //read line form file
        readLine(line, inFile);
        //changes al characters in line to upper case
        lineToUpper(line);

        //ommit line if it starts with a . or a new line character
        if(line[0] != '\n' && line[0] != '.')
        {
            theLine = parseLine(line) ;
            lineCount++ ;
        }
        else
        {
            continue ;
        }

        //check line one for START directive
        if(lineCount == 1)
        {
            for(counter = 0 ; counter < theLine.count; counter++)
            {
                if(strcmp(theLine.tokens[counter],"START") == 0)
                {
                    locctr = startAddrs = strToInt(theLine.tokens[counter + 1],strlen(theLine.tokens[counter+1]-1));
                    interFileHeader(interFile,theLine.tokens[counter -1],startAddrs);
                    break ;
                }


            }
            if(counter == theLine.count)
            {

                errors[err++] = NO_START_DIR ;

                interFileHeader(interFile,"Default",startAddrs);
                //continue ;
            }

            //add line to intermediate file
            fprintf(interFile,"\t|");//,locctr);
            for(counter = 0 ; counter < 3 ; counter++)
            {
                fprintf(interFile,"%s\t|",theLine.tokens[counter]);
            }
            fprintf(interFile,"\t\t|");

            printErrorCodes(interFile,errors);

        }
        //***************************************************************************************

        if(isSymbol(theLine.tokens[COL1]) && strcmp(theLine.tokens[COL2],"START") != 0 )
        {
            //check for duplicate label
            errors[err++] = isSymbolDuplicate(theLine.tokens[COL1]);

            //insert label to table
            insertSymNode(theLine.tokens[COL1],locctr);

            //print line for label only
            if(theLine.count == 1)
            {
                printLineToFile(interFile,locctr,theLine.tokens,-1);
                fprintf(interFile,"\t|\t|\t\t|");
                printErrorCodes(interFile,errors);
                continue ;

            }
            else
            {
                printLineToFile(interFile,locctr,theLine.tokens,COL2);

            }
                //increment locctr
                if(!searchOp(theLine.tokens[COL2]))
                {
                    locctr += incrementLC(theLine.tokens,COL2) ;

                }


                printErrorCodes(interFile,errors);


        }
        else if(!searchOp(theLine.tokens[COL1]))
        {

            printLineToFile(interFile,locctr,theLine.tokens,COL1);


            locctr += incrementLC(theLine.tokens,COL1) ;

            printErrorCodes(interFile,errors);

            if(strcmp(theLine.tokens[COL1],"END") == 0)
            {
                break ;
            }

        }

        /*
        //if line is not empyt and is not a comment then process line
        if(line[0] != '\n' && line[0] != '.')
        {
            //tokenize line and store in struct
            theLine = parseLine(line);//the tokenized line
            lineCount++ ;

            //if opcode is start directive at line one then
            if(strcmp(theLine.tokens[1],"START")== 0 && lineCount == 1)
            {
                //set starting address to operand
                startAddrs = strToInt(theLine.tokens[2],strlen(theLine.tokens[2])-1);

                //set locctr to starting address
                locctr = startAddrs ;

                //print intermediate file header
                interFileHeader(interFile,theLine.tokens[0],startAddrs);

                //add line to intermediate file
                fprintf(interFile,"\t|");//,locctr);
                for(counter = 0 ; counter < 3 ; counter++)
                    fprintf(interFile,"%s\t|",theLine.tokens[counter]);

                fprintf(interFile,"\n");


            }
            else
            {

                if(searchOp(theLine.tokens[0]))//if is a symbol
                {
                    insertSymNode(theLine.tokens[0],locctr);//insert symbol in table


                    //**************Print line to file ******************************
                    fprintf(interFile,"%x\t|",locctr);
                    for(counter = 0 ; counter < 3 ; counter++)
                        fprintf(interFile,"%s\t|",theLine.tokens[counter]);
                    //***************************************************************

                    if(!searchOp(theLine.tokens[1]))//if next item in token list is an opcode
                    {

                        if(strcmp(theLine.tokens[1],"WORD") == 0) //if it equals word
                        {
                            locctr += 3 ; //increment counter by 3

                        }
                        else if(strcmp(theLine.tokens[1],"RESW") ==0)//if equals resw
                        {
                            //increment counter by 3 times the number of the operand
                            locctr += 3 * strToDec(theLine.tokens[2],strlen(theLine.tokens[2]-1)) ;

                        }
                        else if(strcmp(theLine.tokens[1],"RESB")==0)//if equals resb
                        {
                            //increment counter by adding the operand
                            locctr += strToDec(theLine.tokens[2],strlen(theLine.tokens[2])-1) ;
                        }
                        else if(strcmp(theLine.tokens[1],"BYTE")==0)//if equals byte
                        {
                           locctr +=  operandToBytes(theLine.tokens[2]);
                        }
                        else //if just regular operator
                        {
                            locctr += 3 ;
                        }
                        //prints the mnemonic value of the opcode
                        fprintf(interFile,"%x\t|",mnValue(theLine.tokens[1]));



                    }
                    else
                    {
                        //set error code ;

                    }

                    //prints error code in the line
                }
                else if(!searchOp(theLine.tokens[0]))//if is opcode
                {

                    //***************print line to file ******************************
                    fprintf(interFile,"%x\t|\t|",locctr);
                    for(counter = 0 ; counter < 2 ; counter++)
                        fprintf(interFile,"%s\t|",theLine.tokens[counter]);
                    //****************************************************************

                    if(strcmp(theLine.tokens[0],"WORD") == 0)
                    {
                        locctr += 3 ;

                    }
                    else if(strcmp(theLine.tokens[0],"RESW") ==0)
                    {
                        locctr += 3 * strToInt(theLine.tokens[1],strlen(theLine.tokens[1]-1)) ;

                    }
                    else if(strcmp(theLine.tokens[0],"RESB")==0)
                    {
                        locctr += strToInt(theLine.tokens[1],strlen(theLine.tokens[1])-1) ;
                    }
                    else if(strcmp(theLine.tokens[0],"BYTE")==0)
                    {
                        locctr += operandToBytes(theLine.tokens[1]);
                    }
                    else //if just regular operator
                    {
                        locctr += 3 ;
                    }

                    //prints the mnemonic value of the opcode
                    fprintf(interFile,"%x\t|",mnValue(theLine.tokens[0]));


                }
                else
                {
                    //for any illegal operation
                }

                //prints error code in the line

                fprintf(interFile,"\n");

            }
            //********************************************************
        */


    }


    printTblToFile(labels);

    fclose(inFile);
    fclose(labels);
    fclose(interFile);

    exit(EXIT_SUCCESS);

}
