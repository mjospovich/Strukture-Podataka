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
#define INSERTION_ERROR (-1)
#define OPERATE_ERROR (-1)
#define STACK_ERROR (-1)
#define PRINT_ERROR (-1)


struct _Stack;

typedef struct _Stack* Position;

typedef struct _Stack{

    int value;
    Position next;

}Stack;

int operate(Stack*, char);
int insert_from_file(char*, char*);
int give_next(char*, int*, char*, int*);
int insert_end(Stack**, int);
int print_stack(Stack*);
int count_members(Stack*);
Stack* find_behind_last(Stack*);
int delete_member_after(Stack*);
int check_stack(Stack*);


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

      current_step = give_next(line, &line_len, &operator, &operand);
      //printf("\tstep %d/%d => ", current_step, line_len);

      if (current_step == BAD_INPUT){
        printf("Wrong input detected, exiting the program!\n");
        return BAD_INPUT;
      }

      if(operand == 0 && operator != '\0')
      {
        //OPERATE
        //can't operate if less than 2 members in list
        if((count_members(head))>=2)
        {
          //poziv za operate()

          chk_msg = operate(head, operator);
          if (chk_msg){
            return OPERATE_ERROR;
          }
          printf("Current stack:\n");
          print_stack(head);
          printf("\n");
          //printf("\tmoze ic operacija\n");
        }
        else
        {
          printf("list is not valid\n");
          return INSERTION_ERROR;
        }
        //printf("%c\n", operator);
      }

      else if (operand != 0)
      {
        //ADD TO LIST
        //printf("%d\n", operand);
        chk_msg = insert_end(&head, operand);
        if (chk_msg != SUCCESS){
          return INSERTION_ERROR;
        }
      } 

      else
      {
        printf("whoops\n");
      }
      

    }while (current_step <= line_len - 1);
    

    //checking if the final stack is ok
    chk_msg = check_stack(head);
    if (chk_msg != SUCCESS){
      printf("\nFinal stack looks like this:\n");
      print_stack(head);
      printf("Final stack doesn't have one int like it should!\n");
      return STACK_ERROR;
    }


    printf("Final stack looks like this:\n");
  
    chk_msg = print_stack(head); //printing the final stack
    if (chk_msg != SUCCESS){
      printf("Error while printing!\n");
      return PRINT_ERROR;
    }

    //freeing memory
    chk_msg = delete_stack(head);
    if (chk_msg != SUCCESS){
      printf("Error while clearing memory!\n");
      return DEL_ERROR;
    }
    printf("\nMemory freed!\n\n");


    return SUCCESS;
}


//checking if final stack is right
int check_stack(Stack* head)
{
  if (head->next == NULL || head->next->next != NULL){
    return STACK_ERROR; //in the end stack needs to contain only one int
  }

  //final stack is ok
  return SUCCESS;
}

//operates with 2 last operands in the list(stack)
int operate(Stack* head, char operator)
{
  int chk_msg = 0;
  int last_value = 0;
  int behind_last_value = 0;
  int result_value = 0;
  //printf("operand: %c\n", operator);

  Stack* behind_last_member = find_behind_last(head);

  behind_last_value = behind_last_member->value;
  last_value = (behind_last_member->next)->value;

  //deleting last member
  chk_msg = delete_member_after(behind_last_member);
  if (chk_msg != SUCCESS){
    //printf("iz delete_member");
    return OPERATE_ERROR;
  }

  //deleting one more member
  behind_last_member = find_behind_last(head);
  chk_msg = delete_member_after(behind_last_member);
  if (chk_msg != SUCCESS){
    return OPERATE_ERROR;
  }

  //finding operator
  switch(operator)
  {
      case '+':
        result_value = behind_last_value + last_value;
        break;

      case '-':
        result_value = behind_last_value - last_value;
        break;

      case '*':
        result_value = behind_last_value * last_value;
        break;

      case '/':
        //stacemo s ovin
        result_value = behind_last_value / last_value;
        break;

      // operator doesn't match any case constant +, -, *, /
      default:
       return OPERATE_ERROR;     
  }


  //insertig the result back to the list
  chk_msg = insert_end(&head, result_value);
  if (chk_msg != SUCCESS){
    return INSERTION_ERROR;
  }

  return SUCCESS;
}

//going through string and returning the next operator/operand
int give_next(char* line, int* line_len, char* operator, int* operand)
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

  //this would return an error if an operator is on the last place
  if ((*(line_len)-steps)!=1){
    sscanf_msg1 = sscanf(temp, "%d %n", &temp_operand, &n);
  }
  sscanf_msg2 = sscanf(temp, "%c", &temp_operator);

  if(sscanf_msg1 == 1){
    //returning operand
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
    //returning operator
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

//insert content from a file to string
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

//adding a member at the last place in the list
int insert_end(Stack** head, int value)
{
    Stack* new_member = (Stack*)calloc(1, sizeof(Stack));
    Stack* current = *head;

    //checking if memory has allocated or not
    if (new_member == NULL)
    {
        printf("Memory hasn't allocated properly!\n");
        return MEM_ALLOC_ERROR;
    }

    //last member points to NULL
    new_member->next = NULL;

    //assigning values to the new member
    new_member->value = value;
    
    //looping until we reach the previuos last member
    while (current->next != NULL) 
    {
        current = current->next;
    }
    current->next = new_member;

    return SUCCESS;
}

//prints all members of list
int print_stack(Stack* head)
{
    //chacking if list is empty before printing
    if (head->next == NULL)
    {
        printf("List is empty, nothing to print!");
        return EMPTY_LIST_WARNING;
    }

    //temp variable on stack for looping through the list
    Stack* temp = head->next;

    do {
        //printing values from the list
        printf("\t|%4d  |\n", temp->value);

        temp = temp->next;
    } while (temp != NULL);


    return SUCCESS;
}

//function that counts members of a linked list
int count_members(Stack* head)
{
    int i = 0;
    Stack* temp = head->next;

    do{
        
        i++;
        temp = temp->next;

    }while(temp != NULL);


    return i; //returns the number of members in a linked list
}

//finds list member behind the last member
Stack* find_behind_last(Stack* head)
{
    Stack* temp = NULL;

    //check if list is empty
    if (head->next == NULL)
    {
        printf("List is empty, nothing to find!");
        return temp;
    }

    temp = head;

    while ((temp->next)->next != NULL)
    {
        temp = temp->next;
    } 

    return temp;
}

//deletes whole list
int delete_stack(Stack* head)
{
    Stack* temp = head->next;
    int chk_msg = 0;

    do
    {
        chk_msg = delete_member_after(head);
        if (chk_msg != SUCCESS){
          return DEL_ERROR;
        }

        temp = head->next;
      
    }while (temp != NULL);

    free(head);

    return SUCCESS;
}

//deletes next list member for the one given
int delete_member_after(Stack* head)
{
    Stack* temp = NULL;

    //check if we can find right member
    if (head == NULL)
    {
        return DEL_ERROR;
    }

    //if we found the member proceed in deleting
    temp = head->next;
    head->next = NULL;

    //free memory from deatached member
    free(temp);


    return SUCCESS;
}

