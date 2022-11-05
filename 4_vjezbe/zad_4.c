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
#define MAX_POLYNOMIAL (16)


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


int main(void)
{
    Polynomial* head_arr;
    char fileName[MAX_FILE_NAME] = {"\0"};
    int check_msg = 0;
    
    //allocating an array of heads
    head_arr = (Polynomial*)calloc(MAX_POLYNOMIAL, sizeof(Polynomial));
    //checking if memory has allocated correctly
    if (head_arr == NULL)
    {
        printf("Memory not allocated, exiting the program!\n");
        return MEM_ALLOC_ERROR;
    }

    printf("Enter file name!\n");
    scanf("%s", fileName);

    check_msg = insert_from_file(fileName, head_arr);






    return SUCCESS;
}

int insert_from_file(char* fileName, Polynomial* head_arr)
{
    int multiplier = 0;
    int exp = 0;
    int count_read = 0;
    int i = 0;
    int buffer_len;

    //opening the text file and setting it to a variable
    FILE *fp = NULL;
    fp = fopen(fileName, "r");

    char buffer[MAX_LINE] = { 0 };
    char temp[MAX_LINE] = { 0 };

  
    //checking if the file opened correctly, if not returning error
    if (fp == NULL)
    {
        printf("The file %s didn't open!\r\n", fileName);
        return FILE_OPENING_ERROR;
    }
  
    //going through the file and finding info about members
    while(!feof(fp))
    {
        i = 0;
        count_read = 0;

        fgets(buffer, MAX_BUFFER_SIZE, fp);
        buffer_len = strlen(buffer);
        

        //skip empty row
        if ((strcmp("\n", buffer) != 0))
        {
            do
            {
                sscanf(temp, "%d %d %n", &multiplier, &exp, &count_read);
                i = i + count_read;
                

                

            }while(i != buffer_len);
        }
    }

    //closing the text file
    fclose(fp);

    return SUCCESS;
}

