#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SUCCESS (0)
#define MEM_ALLOC_ERROR (-1)
#define EMPTY_LIST_WARNING (-1)
#define MEMBER_NOT_FOUND (-1)
#define DEL_ERROR (-1)
#define FILE_OPENING_ERROR (-1)
#define MAX_BUFFER_SIZE (1024)
#define MAX_FILE_NAME (128)
#define MAX_LINE (128)
#define MAX_POLYNOMIAL (32)


struct _Polynomial;

typedef struct _Polynomial* Position;

//structure Person type structure _Person
typedef struct _Polynomial{
    int multiplier;
    int exp;
    Position next;

}Polynomial;


//function definitions
int insert_from_file(char*, Polynomial*);
int insert_sorted(Polynomial**);


int main(void)
{
    Polynomial** head_all;
    head_all = (Polynomial**)calloc(MAX_POLYNOMIAL, sizeof(Polynomial));

    while




    return SUCCESS;
}

int insert_from_file(char* fileName, Polynomial* head)
{
    int multiplier = 0;
    int exp = 0; 

    //opening the text file and setting it to a variable
    FILE *fp = NULL;
    fp = fopen(fileName, "r");

    char buffer[MAX_LINE] = { 0 };

  
    //checking if the file opened correctly, if not returning error
    if (fp == NULL)
    {
        printf("The file %s didn't open!\r\n", fileName);
        return FILE_OPENING_ERROR;
    }
  
    //going through the file and finding info about members
    while(!feof(fp))
    {
        fgets(buffer, MAX_BUFFER_SIZE, fp);

        //skip empty row
        if ((strcmp("\n", buffer) != 0))
        {
            sscanf(buffer, "%s %s %d", name, surname, &birthYear);
            insert_end(&head, name, surname, birthYear);
        }
    }

    //closing the text file
    fclose(fp);

    return SUCCESS;
}

