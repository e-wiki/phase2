#include <stdio.h>
#include <stdlib.h>
#include "helperFunctions.h"
#include "nodes.h"
#include "opCodeHash.h"
#include "symCodeHash.h"

int main()
{

    FILE* inFile; //assembly source file
    FILE* labels ; //stores the labels and addresses
    FILE* interFile ; //stores the intermediate data from source file

    int startAddrs = 0 ;//starting address of program
    int locctr = 0 ;//address of current instruction

    char* line = NULL;
    size_t len = 0;

    int counter = 0 ;

    tokenLine theLine ; // holds tokens from a parsed line


    initSymHashTbl();//initializes symbols table
    initOpHashTbl();//initializes opcode table
    insertSymNode("CLOOP",04);

    //open assembly source file, exit if not able to open
    inFile = fopen("source.asm", "r");
    if (inFile == NULL)
        exit(EXIT_FAILURE);

    //open labels file for writting, exit if not able to open
    labels = fopen("labels.txt","w");
    if(labels == NULL)
        exit(EXIT_FAILURE);

    //open intermidate file for writting, exit if not able to open
    interFile = fopen("intermediateFile.txt","w");
    if(interFile == NULL)
        exit(EXIT_FAILURE);





    //start loop that goes to every line of file ending at end of file
    while(!feof(inFile))
    {
        getline(&line, &len, inFile);

        lineToUpper(line);

        //if line is not empyt and is not a comment then process line
        if(line[0] != '\n' && line[0] != '.')
        {
            //tokenize line and store in struct
            theLine = parseLine(line);//the tokenized line

            //if opcode is start directive then
            if(strcmp(theLine.tokens[1],"START")== 0)
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
            //I AM WORKING ON THIS SECTION RIGHT HERE
            else
            {

                if(searchOp(theLine.tokens[0]))//if is a symbol
                {
                    insertSymNode(theLine.tokens[0],locctr);//insert symbol in table

                    fprintf(interFile,"%d\t|",locctr);
                    for(counter = 0 ; counter < 3 ; counter++)
                    fprintf(interFile,"%s\t|",theLine.tokens[counter]);

                    if(!searchOp(theLine.tokens[1]))//if next item in token list is an opcode
                    {

                        if(strcmp(theLine.tokens[1],"WORD") == 0) //if it equals word
                        {
                            locctr += 3 ;

                        }
                        else if(strcmp(theLine.tokens[1],"RESW") ==0)//if equals resw
                        {

                            locctr += 3 * strToDec(theLine.tokens[2],strlen(theLine.tokens[2]-1)) ;

                        }
                        else if(strcmp(theLine.tokens[1],"RESB")==0)//if equals resb
                        {
                            locctr += strToDec(theLine.tokens[2],strlen(theLine.tokens[2])-1) ;
                        }
                        else if(strcmp(theLine.tokens[1],"BYTE")==0)//if equals byte
                        {
                            locctr += 0 ;
                        }
                        else
                        {
                            locctr += 3 ;
                        }

                    }
                    else
                    {
                        //set error code ;

                    }
                }
                else if(!searchOp(theLine.tokens[0]))//if is opcode
                {
                    //NOTE TO SELF, FIX ISSUE WITH CONVERTING TO UPPERCASE,
                    //FIX OPNODE HASHING FUNCTION

                    fprintf(interFile,"%d\t|\t|",locctr);
                    for(counter = 0 ; counter < 2 ; counter++)
                    fprintf(interFile,"%s\t|",theLine.tokens[counter]);

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
                        locctr += 0 ;
                    }
                    else
                    {
                        locctr += 3 ;
                    }


                }
                else
                {
                    //for any illegal operation
                }

                /*//add line to intermediate file
                fprintf(interFile,"\t|");//%d\t|",locctr);
                for(counter = 0 ; counter < theLine.count ; counter++)
                    fprintf(interFile,"%s\t|",theLine.tokens[counter]);
*/
                fprintf(interFile,"\n");

            }
            /********************************************************/
        }


    }


    printTblToFile(labels);

    fclose(inFile);
    fclose(labels);

    exit(EXIT_SUCCESS);

}
