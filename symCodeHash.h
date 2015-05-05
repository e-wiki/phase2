/***********************************************************
// Name : Gerardo Hernandez
// Filename : symCodeHash.h
// Class: CMPE 3334
// Date: 03/02/2015
// Revised: 03/02/2015
// Description:
// The source file contains the hash table to store symNodes
// with their respective lable and address
************************************************************/

#ifndef SYMCODEHASH_H
#define SYMCODEHASH_H

#include "nodes.h"
#include <string.h>
#include <stdio.h>




/*********************************
//      Struct Definitions
//
**********************************/

struct symHash
{
    symLinkedList symbols[MAX_SYMTBL_LENGTH] ;
    int size ;
};

/************ Function declarations *******************/
//initialize hash table
void initSymHashTbl();

//hashing function
int symHashingFunc(const char *key);

//inserts a opNode at n position in hashtable
//takes a pointer to the hashTable
void insertSymNode(const char* label, int addr);


//prints hash table to screen
void printTblToScreen();

//prints hash table to file
void printTblToFile(FILE *fp);

//searches through hash table for specific item
//returns 1 if found, if not found returns 0
int searchSym(const char* itemLbl);


/*****************Generate symbol Hash Table ***********/

struct symHash symHashTbl ;



/*********** Function definitions *********************/
//initialize hash table
void initSymHashTbl()
{
    int i ;
    for(i = 0 ; i < MAX_SYMTBL_LENGTH; i++)
    {
        symHashTbl.symbols[i].head = NULL ;
        symHashTbl.symbols[i].last = NULL ;

    }

    symHashTbl.size = 0 ;

}

//hashing function
int symHashingFunc(const char *key)
{
    int k = 0;
    int total = 0 ;

    while(key[k] && k <MAX_LABEL_LENGTH)
    {
        total +=  key[k]- '0' ;
        k++ ;

    }

    return total % MAX_SYMTBL_LENGTH ;
}

//inserts a opNode at n position in hashtable
//takes a pointer to the hashTable
void insertSymNode(const char* label, int addr)
{

    int key = symHashingFunc(label);

    if(symHashTbl.size <= MAX_LABELS)
    {
        symNode* newItem  = (symNode*)malloc(sizeof(symNode));
        //newItem->label = label ;
        //newItem->address = addr;
        //newItem->int = int ;
        newItem->next = NULL ;


        symNode* current =  symHashTbl.symbols[key].head ;

        if(symHashTbl.symbols[key].head == NULL)
        {
            symHashTbl.symbols[key].head = malloc(sizeof(opNode));
            symHashTbl.symbols[key].head= newItem ;
            symHashTbl.symbols[key].last = newItem ;
            symHashTbl.size++ ;


        }
        else
        {
            current = symHashTbl.symbols[key].last ;

            if(current->next == NULL)
            {
                current->next = newItem ;
                symHashTbl.symbols[key].last = newItem ;
                symHashTbl.size++ ;

            }

        }
    }

}

//print hash table to screen
void printTblToScreen()
{

    int i ;
    symNode* current ;
    for(i =0 ; i < MAX_SYMTBL_LENGTH ; i++)
    {
        current = symHashTbl.symbols[i].head ;
        printf("%d.\t************************\n",i);
        while(current != NULL)
        {
            printf("\t|%s , %x\n",current->label,current->address);
           // printf("\t|Error code: %d\n",current->errCode);
            printf("\t|------------------\n");
            current = current->next ;
        }
    }

    free(current);
}

//print hash table to screen
void printTblToFile(FILE* fp)
{

    int i ;
    symNode* current ;
    for(i =0 ; i < MAX_SYMTBL_LENGTH ; i++)
    {
        current = symHashTbl.symbols[i].head ;

        while(current != NULL)
        {
            fprintf(fp,"%d.\t************************\n",i);
            fprintf(fp,"\t|%s , %x\n",current->label,current->address);
            //fprintf(fp,"\t|Error code: %d\n",current->errCode);
            current = current->next ;
        }
    }

    free(current);
}

//searches through the hash table looking for a matching
// label or a duplicate address. returns a variable of type
//enum depending on error code
int searchSym(const char* itemLbl)
{
    int key = symHashingFunc(itemLbl);

    symNode* current = symHashTbl.symbols[key].head ;

    while(current != NULL)
    {

        if(strcmp(current->label,itemLbl) == 0)
        {
            //current->errorCode = FOUND ;
            return 0 ;//if found returns zero
        }

        current = current->next ;
    }


    return 1 ;//if not found returns one
}


#endif
