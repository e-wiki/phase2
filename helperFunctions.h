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

//takes a string line of characters and tokenizes the line
// returns a struct containing the tokenized line
struct tLine parseLine(char *line);

//converts a line form lower case to upper case ;
void lineToUpper(char* line);

//inserts a header on the intermediate file
void interFileHeader(FILE* fp,const char* name,const int start);

//translates operand into number of bytes required
int operandToBytes(const char* operand);

//checks for errors in program line
void checkErrors(const char* item,errorCode errorCodes);

//initialize files
void initDataIo(char** filenames, FILE** files);

//reads line from specified file
void readLine(char* line , FILE* fp);



#endif
