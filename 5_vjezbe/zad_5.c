
// #pragma warning (disable: 4047)
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SUCCESS (0)
#define MEM_ALLOC_ERROR (-1)
#define FILE_READ_ERROR (-1)
#define EMPTY_LIST_WARNING (-1)
#define MEMBER_NOT_FOUND (-1)
#define DEL_ERROR (-1)
#define FILE_OPENING_ERROR (-1)
#define MAX_BUFFER_SIZE (1024)
#define MAX_FILE_NAME (128)
#define MAX_LINE (128)


struct _Stack;

typedef struct _Stack* Position;

//structure Person type structure _Person
typedef struct _Stack{

    int value;
    Position* next;

}Stack;



int main()
{
    int n = 0;
    Stack* head = NULL;
    head->value = 0;
		char line[MAX_LINE] = {"\0"};
    
    printf("Scanf je vratio: ", sscanf(" ", "%d", &n));



    return SUCCESS;
}

int insert_from_file(char* fileName, char* line)
{
  int i = 0;
  char buffer[MAX_LINE] = { 0 };

  //opening the text file and setting it to a variable
  FILE *fp = NULL;
  fp = fopen(fileName, "r");

  //check if file has opened successfully (if not return error)
  if (fp == NULL)
  {
    printf("The file '%s' didn't open!\r\n", fileName);
    return FILE_OPENING_ERROR;
  }


  //skipping rows which are blank and don't contain student info
	fgets(buffer, MAX_BUFFER_SIZE, fp);


  //copying data from the buffer to the variables 
  sscanf(buffer, "%s", line);


  //copying data from variables to the structure via pointer
}
