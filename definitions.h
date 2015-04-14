#ifndef DEFINITIONS_H
#define DEFINITIONS_H

//#include <stdio.h>

//defines the max number of characters in a line
#define MAX_LINE_LENGTH 100

//defines the max number instructions
#define MAX_NUMBER_OF_INST 25 //TBA!!!!!

//defines the max number of directives in the instruction set
#define MAX_NUMBER_OF_DIRS 6 //TBA !!!!!!

//defines the max number of tokens per line
#define MAX_TOKENS 6

//defines the max length of a label
#define MAX_LABEL_LENGTH 7

//defines the max length of a opcode instruction in characters
#define MAX_OPCODE_LENGTH 6 // TBA !!!!!

//defines the max number of labels to be stored in an array
#define MAX_LABELS 500

//defines the max number of characters for a character string
#define MAX_STRING_CHARS 30

//defines the max numbef of characters for a hexadecimal string
#define MAX_HEX_CHARS 32

//defines which characters are to be ignored or used as delimeters
#define WHITESPACE " \t\n"

//defines the max size of the hash table to be an even integer
#define MAX_HASHTBL_LENGTH 13

//defines the max size of the hash table to be an odd intenger
#define MAX_SYMTBL_LENGTH 101

//defines the hexadecimal base value
#define HEX_BASE 16

//defines the max number for characters for a token
#define MAX_TOKEN_LEN 50

//gives you the size of an array
#define ARRSIZE(x) (sizeof(x)/sizeof(x[0]))-1

//DEFINES COLUMN ONE
#define COL1 0

//DEFINES COLUMN TWO
#define COL2 1

//DEFINES COLUMN THREE
#define COL3 2


#endif
