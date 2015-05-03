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
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "nodes.h"


/************ Function Declarations ****************/

//translates a string of characters to its decimal value
int strToInt(char *strValue , int pos);

//converts a string to its decimal value
int strToDec(char *strValue, int pos);

//inserts a header on the intermediate file
void interFileHeader(FILE* fp,const char* name,const int start);

//translates operand into number of bytes required
int operandToBytes(const char* operand);

//initialize files
void initDataIo(char** filenames, FILE** files);

//checks to see if tokens is symbol
int isSymbol(char* token);

//checks if symbol is duplicate
int isSymbolDuplicate(char* token);

//checks if lable is illegal
int isSymbolIllegal(char* token);

//increments the location counter
int incrementLC(char** cols,int column,errCodes* codes);

//Prints line to file
void printLineToFile(FILE* inF,int loc,char** token,int col);

//print error codes to file
void printErrorCodes(FILE* fp,errCodes* codes);



#endif
