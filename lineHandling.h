/***********************************************************
// Name : Gerardo Hernandez
// Filename : helperFunctions.h
// Class: CMPE 3334
// Date: 02/12/2015
// Revised: 02/12/2015
// Description:
// The source file contains the opNode and symNode
// structs for storing the instructions used in program
// and to store the labels and its values found in the
// program
************************************************************/
#ifndef LINEHANDLING_H
#define LINEHANDLING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "nodes.h"

/************ Function Declarations ************************/

//takes a string line of characters and tokenizes the line
// returns a struct containing the tokenized line
struct tLine parseLine(char *line);


//converts a line form lower case to upper case ;
void lineToUpper(char* line);

//reads line from specified file
void readLine(char* line , FILE* fp);

/*************** Function definitions ************************/

//takes a string line of characters and tokenizes the line
//returns a struct cotntainig the tokenized line
struct tLine parseLine(char *line)
{
    //tokenized line to be returned
    tokenLine parsedLine ;

    //keeps count of tokens in line
    int cnt = 0 ;

    char* strLine ;

    strLine = strtok(line,WHITESPACE);

    while(strLine != NULL)
    {

        if(cnt < MAX_TOKENS)
        {

            parsedLine.tokens[cnt] = (char*)malloc(MAX_TOKEN_LEN);
            strcpy(parsedLine.tokens[cnt],strLine);
            cnt++ ;

        }

        strLine = strtok(NULL,WHITESPACE);

    }
    parsedLine.count = cnt ;



    return parsedLine ;
};


//converts a line form lower case to upper case ;
void lineToUpper(char* line)
{
    char tmp ;
    int i = 0 ;

    while(line[i])
    {
        tmp = toupper(line[i]);
        line[i] = tmp ;
        i++ ;

    }


}


//reads line from specified file
void readLine(char* line , FILE* fp)
{

    size_t* len = MAX_LINE_LENGTH ;

    getline(&line,&len,fp);


}

#endif
