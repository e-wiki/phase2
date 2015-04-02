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

