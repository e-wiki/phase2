/***********************************************************
// Name : Gerardo Hernandez
// Filename : ppCodeHash.h
// Class: CMPE 3334
// Date: 02/13/2015
// Revised: 02/13/2015
// Description:
// The source file contains the hash table to store opNodes
// with their respective mnemonic and value
************************************************************/
#ifndef OPCODEHASH_H
#define OPCODEHASH_H

#include "nodes.h"
#include <stdio.h>


/************* Structures definitions *****************/
//stores a fixed size of opNodes in an array
struct opHash
{
    opLinkedList opCode[MAX_HASHTBL_LENGTH] ;
    int size ;

} ;

/************ Function declarations *******************/
//initialize hash table
void initOpHashTbl();

//hashing function
int hashingFunc(const char *key);

//inserts a opNode at n position in hashtable
//takes a pointer to the hashTable
void insertNode(char *mnemonic, char* value);

//returns the mnemonic value of opcode
int mnValue(char *mnemonic);

//prints hash table to screen
void printToScreen();

//prints hash table to file
void printToFile();

//searches through hash table for specific item
//returns 1 if found, if not found returns 0
errorCode searchOp(const char* item);


/*****************Generate Opcode Hash Table ***********/

struct opHash opHashTbl ;



/*********** Function definitions *********************/

//hashing function
int hashingFunc(const char *key)
{
    int k = 0 ;
    int i = 0 ;

    for(k = 0 ; k < strlen(key); k++)
    {
        i += key[k]-'0' ;

    }
    //fixs this for negative values
    return  (i% MAX_HASHTBL_LENGTH) ;
    //return (i[0] + 27 i[1] + 729 * i[2]) % MAX_HASHTBL_LENGTH ;

}


//initialize opcode hashing table
void initOpHashTbl()
{
    int i = 0 ;

    for(i ; i < MAX_HASHTBL_LENGTH ; i++)
    {
        opHashTbl.opCode[i].head = NULL ;

    }

    opHashTbl.size = 0 ;


    insertNode("ADD","18");
    insertNode("AND","58");
    insertNode("COMP","28");
    insertNode("DIV","24");
    insertNode("J","3c");
    insertNode("JEQ","30");
    insertNode("JGT","34");
    insertNode("JLT","38");
    insertNode("JSUB","48");
    insertNode("LDA","00");
    insertNode("LDCH","50");
    insertNode("LDL","08");
    insertNode("LDX","04");
    insertNode("MUL","20");
    insertNode("OR","44");
    insertNode("RD","d8");
    insertNode("RSUB","4c");
    insertNode("STA","0c");
    insertNode("STCH","54");
    insertNode("STL","14");
    insertNode("STX","10");
    insertNode("SUB","1c");
    insertNode("TD","e0");
    insertNode("TIX","2c");
    insertNode("WD","dc");
    insertNode("START","0");
    insertNode("END","0");
    insertNode("BYTE","0");
    insertNode("WORD","0");
    insertNode("RESB","0");
    insertNode("RESW","0");

}

//inserts node at beginning of table list if empty
//or at the end if list is not empty
void insertNode(char *mnemonic, char* value)
{

    int key = hashingFunc(mnemonic);

    opNode* newItem  = (opNode*)malloc(sizeof(opNode));
    newItem->operatorCode = mnemonic ;
    newItem->mnValue = strToInt(value,strlen(value)-1);
    newItem->next = NULL ;


    opNode* current = opHashTbl.opCode[key].head ;

    if(opHashTbl.opCode[key].head == NULL)
    {
        opHashTbl.opCode[key].head = (opNode*)malloc(sizeof(opNode));
        opHashTbl.opCode[key].head= newItem ;
        opHashTbl.opCode[key].last = newItem ;
        opHashTbl.size++ ;


    }
    else
    {
        current = opHashTbl.opCode[key].last ;

        if(current->next == NULL)
        {
            current->next = newItem ;
            opHashTbl.opCode[key].last = newItem ;
            opHashTbl.size++ ;

        }

    }


}


//prints hash table to screen
void printToScreen()
{

    int i ;
    opNode* current ;
    for(i =0 ; i < MAX_HASHTBL_LENGTH ; i++)
    {
        current = opHashTbl.opCode[i].head ;
        printf("%d. *********************\n",i);
        while(current != NULL)
        {
            printf("\t%s , %x\n",current->operatorCode,current->mnValue);
            current = current->next ;
        }
    }

    free(current);
}

//searches through hash table for specific item
//returns 1 if found, if not found returns 0
errorCode searchOp(const char* item)
{

    int key = hashingFunc(item);

    opNode* current = opHashTbl.opCode[key].head ;

    while(current != NULL)
    {

        if(strcmp(current->operatorCode,item) == 0 )
        {

            return FOUND ; //returns zero
        }

        current = current->next ;

    }


    return NOT_FOUND ;//returns one
}

//returns the mnemonic value of opcode
int mnValue(char *mnemonic)
{

    int key = hashingFunc(mnemonic);

    opNode* current = opHashTbl.opCode[key].head ;

    while(current != NULL)
    {

        if(strcmp(current->operatorCode,mnemonic) == 0 )
        {

            return current->mnValue ; //returns mnemonic value
        }


        current = current->next ;

    }


    return 0 ;

}

#endif // OPCODEHASH_H



