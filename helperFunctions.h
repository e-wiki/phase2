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
#ifndef HELPERFUNCTS_H
#define HELPERFUNCTS_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "nodes.h"

/************ Function Declarations ****************/

//translates a string of characters to its decimal value
int strToInt(char *strValue , int pos);

//converts a string to its decimal value
int strToDec(char *strValue, int pos);

//takes a string line of characters and tokenizes the line
// returns a struct containing the tokenized line
struct tLine parseLine(char *line);

//converts a line form lower case to upper case ;
void lineToUpper(char* line);

//inserts a header on the intermediate file
void interFileHeader(FILE* fp,const char* name,const int start);


/*****************Function definitions ***********************/

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

            parsedLine.tokens[cnt] = (char*)malloc(sizeof(strLine));
            strcpy(parsedLine.tokens[cnt],strLine);
            cnt++ ;

        }

        strLine = strtok(NULL,WHITESPACE);

    }
    parsedLine.count = cnt ;



    return parsedLine ;
};

//translates a string of characters to its decimal value
int strToInt(char *strValue , int pos)//<----- You gotta fix this!!!
{
    int value = 1 ;
    int size = (strlen(strValue) < 9)?(strlen(strValue)):(8);
    int decimalValue[size] ;
    int i ;


    if(toupper(strValue[pos]) > 'F')
    {
        value *= 0 ;
        pos--;
        return value += strToInt(strValue,pos);
    }
    else
    {
        switch(toupper(strValue[pos]))
        {
        case 'A':
            decimalValue[pos] = 10 ;
            break;
        case 'B':
            decimalValue[pos] = 11 ;
            break;
        case 'C':
            decimalValue[pos] = 12 ;
            break;
        case 'D':
            decimalValue[pos] = 13 ;
            break;
        case 'E':
            decimalValue[pos] = 14 ;
            break;
        case 'F':
            decimalValue[pos] = 15 ;
            break;
        default:
            decimalValue[pos] = strValue[pos] - '0' ;
            break ;
        }
    }


    for(i=pos ; i < size -1; i++)
    {
        value *= HEX_BASE ;

    }

    if( pos == 0)
    {
        return value * decimalValue[pos] ;
    }
    else
    {
        value *= decimalValue[pos] ;
        pos--;
        return value += strToInt(strValue,pos);
    }


}


//converts a string to its decimal value
int strToDec(char *strValue, int pos)
{
    int value = 1 ;
    int size = (strlen(strValue) < 9)?(strlen(strValue)):(8);
    int decimalValue[size] ;
    int i ;

    decimalValue[pos] = strValue[pos] - '0' ;

    for(i=pos ; i < size -1; i++)
    {
        value *= 10 ;

    }

    if( pos == 0)
    {
        return value * decimalValue[pos] ;
    }
    else
    {
        value *= decimalValue[pos] ;
        pos--;
        return value += strToDec(strValue,pos);
    }



}

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

void interFileHeader(FILE* fp,const char* name, const int start)
{
    fprintf(fp,"Program Name: %s\t\t Starting Address: %x\n",name,start);
    fprintf(fp,"LOCCTR\tLABEL\tOPCODE\tOPERAND\tCOMMENTS\n");
    fprintf(fp,"********************************************");
    fprintf(fp,"*****************************\n");


}


#endif
