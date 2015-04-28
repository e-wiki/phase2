#include "helperFunctions.h"
/*****************Function definitions ***********************/



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



void interFileHeader(FILE* fp,const char* name, const int start)
{
    fprintf(fp,"Program Name: %s\t\t Starting Address: %x\n",name,start);
    fprintf(fp,"LOCCTR\t|LABEL\t|OPCODE\t|OPERAND|MNEMONIC VALUE\t|ERROR CODE\n");
    fprintf(fp,"********************************************");
    fprintf(fp,"*****************************\n");


}


//translates operand into number of bytes required
int operandToBytes(const char* operand)
{
    char* newString = malloc(sizeof(operand));
    int i = 2 ;
    int size ;

    switch(tolower(operand[0]))
    {
    case 'x':
        size = strlen(operand)-3 ;

        if(size <= MAX_HEX_CHARS && size % 2 == 0)
        {
            while(operand[i] != NULL)
            {
                if(operand[i] != '\'')
                {
                    newString[i-2] = operand[i];
                }
                i++ ;
            }
            return strToInt(newString,strlen(newString)-1);
        }
        else
        {
            //record error message
            printf("Line is too long\n");
        }
        break;

    case 'c':
        return strlen(operand)-3 ;
        break;

    default:
        return 0 ;
        break ;



    }//end switch


}


//initialize files
void initDataIo(char** filenames, FILE** files)
{
    //open assembly source file, exit if not able to open
    files[0] = fopen("source.asm", "r");
    if (files[0] == NULL)
        exit(EXIT_FAILURE);

    //open labels file for writting, exit if not able to open
    files[1] = fopen("labels.txt","w");
    if(files[1] == NULL)
        exit(EXIT_FAILURE);

    //open intermidate file for writting, exit if not able to open
    files[2] = fopen("intermediateFile.txt","w");
    if(files[2] == NULL)
        exit(EXIT_FAILURE);


}


//returns true if token is not opcode
int isSymbol(char* token)
{
    return (searchOp(token));

}

//returns true if symbol is a duplicate
int isSymbolDuplicate(char* token)
{
    return (searchSym(token));
}

//checks if lable is illegal
int isSymbolIllegal(char* token)
{
    int i = 0 ;
    if(strlen(token) > 6 )
    {
        return ILLEGAL_LABEL ;
    }
    if(token[i] < '0')
    {
        return ILLEGAL_LABEL ;
    }
    else if(token[i] > '9' && token[i] < 'A')
    {
        return ILLEGAL_LABEL ;
    }
    else if(token[i] > 'Z')
    {
        return ILLEGAL_LABEL ;
    }
    else
    {
        return 0 ;
    }

}

//increments location counter
int incrementLC(char** cols,int column)
{

    if(strcmp(cols[column],"WORD") == 0) //if it equals word
    {
        return 3 ; //increment counter by 3

    }
    else if(strcmp(cols[column],"RESW") ==0)//if equals resw
    {
        //increment counter by 3 times the number of the operand
        return 3 * strToDec(cols[column+1],strlen(cols[column+1]-1)) ;

    }
    else if(strcmp(cols[column],"RESB")==0)//if equals resb
    {
        //increment counter by adding the operand
        return strToDec(cols[column+1],strlen(cols[column+1]-1)) ;
    }
    else if(strcmp(cols[column],"BYTE")==0)//if equals byte
    {
        return  operandToBytes(cols[column+1]);
    }
    else //if just regular operator
    {
        return 3 ;
    }

}

//prints line to intermediate file
void printLineToFile(FILE* inF,int loc,char** token,int col)
{
    int counter = 0 ;
    if(col == 0 )
    {
        fprintf(inF,"%x\t|\t|",loc);
    }
    else
    {
        fprintf(inF,"%x\t|",loc);
    }
    for(counter = 0 ; counter < (col+2) ; counter++)
        fprintf(inF,"%s\t|",token[counter]);

    if(col != -1)
    fprintf(inF,"%x\t\t|",mnValue(token[col]));

}

//print error codes to file
void printErrorCodes(FILE* fp, int** codes)
{
    int i = 0 ;

    fprintf(fp,"\t");
    for(i = 0 ; i < 7 ; i++)
    {
        fprintf(fp,"%d",codes[i]);

    }
    fprintf(fp,"\n");

    //reset array
    for(i = 0 ; i < 7 ; i++)
    {
        codes[i] = 0 ;
    }
}





