/***********************************************************
// Name : Gerardo Hernandez
// Filename  : nodes.h
// Class: CMPE 3334
// Date: 02/12/2015
// Revised: 02/12/2015
// Description:
// The source file contains the opNode and symNode
// structs for storing the instructions used in program
// and to store the labels and its values found in the
// program
************************************************************/


#ifndef NODES_H
#define NODES_H

#include <stdio.h>
#include <string.h>
#include "definitions.h"
#include "helperFunctions.h"

/********************************
//      Enum definition
//
*********************************/


typedef enum {FOUND,NOT_FOUND,ILLEGAL_LABEL,ILLEGAL_OPERATION} errorCode ;


/************************************************************
// Structure definitions
//
*************************************************************/

/************** Opcode structs ***************************/

//defines a node to store opcode
typedef struct strOpNode
{
    char* operatorCode;//[MAX_OPCODE_LENGTH] ;
    int mnValue ;
    struct strOpNode* next ;

} opNode ;


//defines the beginning and end of a linked list
typedef struct opContainer
{
    opNode* head ;
    opNode* last ;

} opLinkedList;

/************** Symbol tabel structs ********************/

//defines a node to store label
typedef struct strSymNode
{
    char *label ;
    int address ;
    errorCode errCode ; //<----change this to the error type
    struct strSymNode* next ;

} symNode ;

typedef struct symContainer
{
    symNode* head ;
    symNode* last ;

} symLinkedList ;

/*********** Line tokenize structs ***********************/

//stores the tokenized line and the number of tokens
typedef struct tLine
{
    char* tokens[MAX_TOKENS] ;
    int count ;

} tokenLine ;


#endif
