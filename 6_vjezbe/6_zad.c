//library imports
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//constants
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
#define MAX_DATE_LENGTH (8)
#define INSERTION_ERROR (-1)

//file imports
//#include "bill.c"
//#include "items.c"

struct _Bill;
typedef struct _Bill* Bill_Pos;

typedef struct _Bill
{
  char bill_name[MAX_DATE_LENGTH];
  Bill_Pos next;
  
}Bill;

//for bill.h
int create_bill_list(char* fileName);
int insert_sorted(Bill_Pos head, char* name);
int insert_after(Bill_Pos head, char* name);
int date_compare(char* date1, char* date2);

//for items.h


int main(void)
{

  
  return SUCCESS;
}


int date_compare(char* date1, char* date2)//complete this
{
  // char str[50] = "2021-01-05";
  //   int y1, d1, m1;
    
  //   sscanf(str, "%d-%d-%d", &y1, &d1, &m1);
  //   printf("%d-%d-%d", y1, d1, m1);
}


int insert_sorted(Bill_Pos head, char* name)
{
  Bill_Pos temp = head;
  int compare = 0;
  int chk_msg = 0;

  do{
    temp = temp->next;

    compare = date_compare(temp->next->bill_name, name); //if left<right:1, right>left:-1, right=left:0
    if (compare == 1){
      break;
    }

  }while(temp->next != NULL);

  chk_msg = insert_after(head, temp->bill_name, name);

  if(chk_msg != SUCCESS){
    return INSERTION_ERROR;
  }

  return SUCCESS;
}


insert_after(Bill_Pos head, char* prev_name, char* name)
{
  Bill_Pos new_bill = (Bill*)calloc(1, sizeof(Bill));
  Bill_Pos temp = head;

  if (new_bill == NULL){
    return MEM_ALLOC_ERROR;
  }

  while(strcmp(temp->next->bill_name, prev_name) != 0)
  {
    temp = temp->next;
  }

  //connecting new members to list
  new_bill->next = temp->next;
  temp->next = new_bill;

  //copying value to new member
  strcpy(new_bill->bill_name, name);

  return SUCCESS;
}


int create_bill_list(char fileName[MAX_DATE_LENGTH])
{
  FILE* fp = NULL; //file pointer
  char buffer[MAX_BUFFER_SIZE] = {'\0'}; //buffer for reading

  //opening the text file
  fp = fopen(fileName, "r");

  //checking if it opened correctly
  if (fp == NULL)
  {
    printf("The file '%s' didn't open!\r\n", fileName);
    return FILE_OPENING_ERROR;
  }

  //looping thorugh the file and reading
  while(!feof(fp))
  {
    fgets(buffer, MAX_BUFFER_SIZE, fp);

    if (strcmp("\n", buffer) != 0)
    {
      continue;
    }

    //insert sorted
  }


  return SUCCESS;
}