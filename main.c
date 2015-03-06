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
    {

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


    }


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
                fprintf(interFile,"%d\t|",locctr);
                for(counter = 0 ; counter < theLine.count ; counter++)
                    fprintf(interFile,"%s\t|",theLine.tokens[counter]);

                fprintf(interFile,"\n");


            }
            else
            {
                if(searchOp(theLine.tokens[0]))
                    insertSymNode(theLine.tokens[0],locctr);
                else
                {
                    //NOTE TO SELF, FIX ISSUE WITH CONVERTING TO UPPERCASE,
                    //FIX OPNODE HASHING FUNCTION


                }

                //add line to intermediate file
                fprintf(interFile,"%d\t|",locctr);
                for(counter = 0 ; counter < theLine.count ; counter++)
                    fprintf(interFile,"%s\t|",theLine.tokens[counter]);

                fprintf(interFile,"\n");
                locctr += 3 ;
            }
        }


    }


    printTblToFile(labels);

    fclose(inFile);
    fclose(labels);

    exit(EXIT_SUCCESS);

}
