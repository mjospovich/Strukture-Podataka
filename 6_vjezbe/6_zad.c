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
#define MAX_DATE_LENGTH (10)
#define INSERTION_ERROR (-1)
#define LEFT_BIGGER (1)
#define RIGHT_BIGGER (-1)
#define EQUAL_DATES (0)

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
int create_bill_list(Bill_Pos head, char* fileName);
int insert_sorted(Bill_Pos head, char* name);
int insert_after(Bill_Pos head, char* prev_name, char* name);
int date_compare(char* date1, char* date2);
int print_list(Bill_Pos head);
int insert_first(Bill_Pos head, char* name);

//for items.h


int main(void)
{
  Bill_Pos bill_head = (Bill*)calloc(1, sizeof(Bill));
  char fileName[MAX_FILE_NAME] = {'\0'};
  scanf("%s", fileName);

  int chk_msg = create_bill_list(bill_head, fileName);
  printf("Ulazin u print!\n");
  print_list(bill_head);

  return SUCCESS;
}


int date_compare(char* date1, char* date2)//complete this
{
  int y1 = 0, m1 = 0, d1 = 0;
  int y2 = 0, m2 = 0, d2 = 0;

  sscanf(date1, "%d-%d-%d", &y1, &d1, &m1);
  sscanf(date2, "%d-%d-%d", &y2, &d2, &m2);
  
  if(y1>y2)
  {
    return LEFT_BIGGER;
  }
  else if(y2>y1)
  {
    return RIGHT_BIGGER;
  }
  else
  {
    if(m1>m2)
    {
      return LEFT_BIGGER;
    }
    else if(m2>m1)
    {
      return RIGHT_BIGGER;
    }
    else
    {
      if(d1>d2)
      {
        return LEFT_BIGGER;
      }
      else if(d2>d1)
      {
        return RIGHT_BIGGER;
      }
      else
      {
        return EQUAL_DATES;
      }
    }

  }

  printf("%d %d %d, %d %d %d", y1, d1, m1, y2, d2, m2);
}


int insert_sorted(Bill_Pos head, char* name)
{
  Bill_Pos temp = head;
  int compare = 0;
  int chk_msg = 0;

  if(head->next == NULL){
    chk_msg = insert_first(head, name);
    if (chk_msg != SUCCESS){
      return INSERTION_ERROR;
    }
    else{
      return SUCCESS;
    }
  }

  do{
    compare = date_compare(temp->next->bill_name, name); //if left>right:1, right>left:-1, right=left:0
    if (compare == 1){
      temp = temp->next;
      break;
    }

    temp = temp->next;

  }while(temp->next->next != NULL);

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


int create_bill_list(Bill_Pos head, char* fileName)
{
  FILE* fp = NULL; //file pointer
  char buffer[MAX_BUFFER_SIZE] = {'\0'}; //buffer for reading
  char bill[MAX_DATE_LENGTH] = {'\0'}; //sent into insert sorted
  int chk_msg = 0; //for getting funcion return values
  char prefix[MAX_LINE] = "racuni/";
  int i = 0;
  
  //copying prefix to fileName
  strcat(prefix, fileName);

  //opening the text file
  fp = fopen(prefix, "r");

  //checking if it opened correctly
  if (fp == NULL)
  {
    printf("The file '%s' didn't open!\r\n", fileName);
    return FILE_OPENING_ERROR;
  }

  //looping thorugh the file and reading
  while(!feof(fp))
  {
    i = 0;
    fgets(buffer, MAX_BUFFER_SIZE, fp);

    if (strcmp("\n", buffer) == 0)
    {
      continue;
    }

    //remove the tail from the buffer
    while(buffer[i] != '\n' && buffer[i] != 'e'){
      bill[i] = buffer[i];
      i = i + 1;
    }

    //insert sorted
    chk_msg = insert_sorted(head, bill);
    strcpy(buffer, "\0");

    if(chk_msg != SUCCESS){
      return INSERTION_ERROR;
    }
  }


  return SUCCESS;
}

int print_list(Bill_Pos head)
{
    //chacking if list is empty before printing
    if (head->next == NULL)
    {
        printf("List is empty, nothing to print!");
        return EMPTY_LIST_WARNING;
    }

    //temp variable for looping through the list
    Bill_Pos temp = head->next;

    do {
        //printing values from the list
        printf("\tDate: %s\n", temp->bill_name);

        temp = temp->next;
    } while (temp != NULL);

    return SUCCESS;
}

int insert_first(Bill_Pos head, char* name)
{
  Bill_Pos new_bill = (Bill*)calloc(1, sizeof(Bill));

  if(new_bill == NULL){
    return MEM_ALLOC_ERROR;
  }

  head->next = new_bill;

  strcpy(new_bill->bill_name, name);

  new_bill->next = NULL;

  //NAPRAVIT LISTU ZA PRVI CLAN

  return SUCCESS;
}