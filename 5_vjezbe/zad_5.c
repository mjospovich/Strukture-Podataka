
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
#define BAD_INPUT (-1)
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


int insert_from_file(char*, char*);
int give_next(char*, char*, int*);


int main(void)
{
    Stack* head = calloc(1, sizeof(Stack));
    if(head == NULL){
      return MEM_ALLOC_ERROR;
    }
    head->value = 0;

    //variables
    int current_step = 0;
    int line_len = 0;
    int chk_msg = 0;
		char line[MAX_LINE] = {'\0'};
    char fileName[MAX_LINE] = {'\0'};

    //values for stack
    int operand = 0;
    char operator = '\0';

    //getting file name form user
    printf("Enter file name:\n");
    scanf("%s", fileName);

    //getting the line from text file
    chk_msg = insert_from_file(fileName, line);
    if (chk_msg){
      return FILE_READ_ERROR;
    }
    line_len = strlen(line);  //getting the length of the line read from file

    do{

      current_step = give_next(line, &operator, &operand);
      if (current_step == BAD_INPUT){
        printf("Wrong input detected, exiting the program!\n");
        return BAD_INPUT;
      }

      if(operand == 0 && operator != '\0')
      {
        printf("%c\n", operator);
      }
      else if (operand != 0)
      {
        printf("%d\n", operand);
      }
      else{
        printf("Kurac\n");
      }
      

    }while (current_step <= line_len - 1);
    


    return SUCCESS;
}


int give_next(char* line, char* operator, int* operand)
{
  static int steps = 0;
  int step = 2;
  int n = 0;
  char temp_operator = '\0';
  int temp_operand = 0;
  int sscanf_msg1 = 0;
  int sscanf_msg2 = 0;
  char temp[MAX_LINE] = {'\0'};

  strcpy(temp, line + steps);

  sscanf_msg1 = sscanf(temp, "%d %n", &temp_operand, &n);
  sscanf_msg2 = sscanf(temp, "%c", &temp_operator);

  if(sscanf_msg1 == 1){
    *(operand) = temp_operand;
    step = n;
  }
  else if(sscanf_msg1 == -1){
    return BAD_INPUT;
  }
  else{
    *(operand) = 0;
  }

  if(sscanf_msg2 == 1){
    *(operator) = temp_operator;
  }
  else if(sscanf_msg2 == -1){
    return BAD_INPUT;
  }
  else{
    *(operator) = '\0';
  }

  steps = steps + step;

  return steps;
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
  strcpy(line, buffer);


  return SUCCESS;
}



/*
    printf("Scanf je vratio: %d", sscanf("+", "%d", &b));

    printf("\nb: %d", b);
    printf("Scanf je vratio: %d", sscanf("+", "%c", &n));

    printf("\nn: %c", n);
    */