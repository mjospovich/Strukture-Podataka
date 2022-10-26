#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//defining constant values
#define MAX_NAME_SIZE (128)
#define SUCCESS (0)
#define MEM_ALLOC_ERROR (-1)
#define EMPTY_LIST_WARNING (-1)
#define MEMBER_NOT_FOUND (-1)
#define DEL_ERROR (-1)


struct _Person;

typedef struct _Person* Position;

//structure Person type structure _Person
typedef struct _Person{
  char name[MAX_NAME_SIZE];
  char surname[MAX_NAME_SIZE];
  int birthYear;
  Position next;

}Person;


//function definitions
int insert_end(Person** , char[MAX_NAME_SIZE], char[MAX_NAME_SIZE], int);
int insert_front(Person**, char[MAX_NAME_SIZE], char[MAX_NAME_SIZE], int);
Person* find_next_surname(Person*, char[MAX_NAME_SIZE]); //this function is used in print/delete member
int print_list(Person*);
int delete_member(Person*, char[MAX_NAME_SIZE]);
int print_member(Person*, char[MAX_NAME_SIZE]);
int delete_list(Person*);


int main(void)
{
  //declaring head and setting everything to NULL
  Person* head = (Person*)calloc(1, sizeof(Person));
  //checking if memory has allocated or not
  if(head == NULL)
  {
    printf("Memory hasn't allocated properly!\n");
    return MEM_ALLOC_ERROR;
  }

  //initialization
  head->birthYear = 0;
  head->next = NULL;
  //strcpy(head->name, NULL);
  //strcpy(head->surname, NULL);

  //variables for input
  int choice = 0;
  char name[MAX_NAME_SIZE] = {"/0"};
  char surname[MAX_NAME_SIZE] = {"/0"};
  int birthYear = 0;
  int catch_msg = 0;

  //mainloop
  do
  {
    choice = 0;
    catch_msg = 0;

    printf("Choose: 0-EXIT | 1-INSERT_FRONT | 2-INSERT_BACK | 3-PRINT LIST | 4-PRINT MEMBER | 5-REMOVE MEMBER\n");
    scanf("%d", &choice);

    //asking needed input
    if (choice == 1 || choice == 2)
    {
      printf("You need to enter info for new member!\n");
      printf("NAME SURNAME BIRTHYEAR\n");
      scanf(" %s %s %d", name, surname, &birthYear);
    }

    if (choice == 4 || choice == 5)
    {
      printf("You need to enter info for member you display/remove\n");
      printf("SURNAME\n");
      scanf(" %s", surname);
    }

    switch (choice)
    {
    case 1:
      //insert_front
      catch_msg = insert_front(&head, name, surname, birthYear);
      if (catch_msg == SUCCESS){
        printf("Inserted member successfully!\n");
      }
      else{
        printf("Error has occured!\n");
      }

      break;
    
    case 2:
      //insert_end
      catch_msg = insert_end(&head, name, surname, birthYear);
      if (catch_msg == SUCCESS){
        printf("Inserted member successfully!\n");
      }
      else{
        printf("Error has occured!\n");
      }
      break;
    
    case 3:
      //print_list
      catch_msg = print_list(head);
      if (catch_msg != SUCCESS){
        printf("Error has occured!\n");
      }
      break;
    
    case 4:
      //print_member
      catch_msg = print_member(head, surname);
      if (catch_msg != SUCCESS){
        printf("Error has occured!\n");
      }
      break;
    
    case 5:
      //delete_member
      catch_msg = delete_member(head, surname);
      if (catch_msg == SUCCESS){
        printf("Deleted member %s!\n", surname);
      }
      else{
        printf("Error has occured!\n");
      }
      break;
    
    default:
      break;
    }

  printf("\n");

  }while(choice != 0);


  //freeing memory
  printf("Freeing memory...\n");
  int deleted = 0;
  deleted = delete_list(head);
  if (deleted == 0)
    printf("Memory freed!\n");

  printf("Exiting the program...\n");
  
  return SUCCESS;
}


//breaking the list apart and freeing memory from members 1 by 1
int delete_list(Person* head)
{
  Person* temp = head; 

  while(temp != NULL)
  {
    temp = temp->next;
    free(head);
    head = temp;
  }

  return SUCCESS;
}


//adding a member at the last place in the list
int insert_end(Person** head, char name[MAX_NAME_SIZE],
              char surname[MAX_NAME_SIZE], int birthYear)
{
  Person* new_person = (Person*)calloc(1, sizeof(Person));
  //checking if memory has allocated or not
  if(new_person == NULL)
  {
    printf("Memory hasn't allocated properly!\n");
    return MEM_ALLOC_ERROR;
  }

  //last member points to NULL
  new_person->next = NULL;
  //assigning values to the new member
  strcpy(new_person->name, name);
  strcpy(new_person->surname, surname);
  new_person->birthYear = birthYear;

  //setting the previous last member to now point to the new one
  Person* current = *head;
  //looping until we reach the previuos last member
  while (current->next != NULL){
    current = current->next;
  }
  current->next = new_person;

  return SUCCESS;
}


//adding a member after head in the list
int insert_front(Person** head, char name[MAX_NAME_SIZE], char surname[MAX_NAME_SIZE], int birthYear)
{
  Person* new_person = (Person*)calloc(1, sizeof(Person));
  //checking if memory has allocated or not
  if(new_person == NULL)
  {
    printf("Memory hasn't allocated properly!\n");
    return MEM_ALLOC_ERROR;
  }
  //new_member now points to the member head used to point
  new_person->next = (*head)->next;

  //head now point to the new member
  (*head)->next = new_person;

  //assigning values to the new member
  strcpy(new_person->name, name);
  strcpy(new_person->surname, surname);
  new_person->birthYear = birthYear;

  return SUCCESS;
}


//removing 1 member from the list
int delete_member(Person* head, char surname[MAX_NAME_SIZE])
{
  //calling function to get previous member
  Person* prev = find_next_surname(head, surname);
  Person* temp = NULL;

  //check if we can find right member
  if (prev == NULL)
  {
    printf("Couldn't find the person with surname %s!\n", surname);
    return DEL_ERROR;
  }

  //if we found the member proceed in deleting
  temp = prev->next;
  prev->next = (prev->next)->next;
  temp->next = NULL;

  //free memory from deatached member
  free(temp);


  return SUCCESS;
}

//print given member info
int print_member(Person* head, char surname[MAX_NAME_SIZE])
{
  Person* wanted = find_next_surname(head, surname)->next;
  
  //check if we got the data needed
  if (wanted == NULL)
    return MEMBER_NOT_FOUND;

  printf("Person's name is %s %s, they were born in %d!\n", wanted->name, wanted->surname, wanted->birthYear);


  return SUCCESS;
}

//find the first member with given surname and return the member behind
Person* find_next_surname(Person* head, char surname[MAX_NAME_SIZE])
{
  Person* temp = NULL;

  //check if list is empty
  if (head->next == NULL)
  {
    printf("List is empty, nothing to find!");
    return temp;
  }

  temp = head;
  
  do{
    //finding the right surname and looping through
    if (strcmp((temp->next)->surname, surname) == 0){
      //if its the right one then break and return it
      return temp; //returning the one before one we wanted to find
    }
    temp = temp->next;
  }while(temp != NULL);

  temp = NULL;

  //returning NULL if nothing is found
  return temp;
}


//print all member info in the list
int print_list(Person* head)
{
  //chacking if list is empty before printing
  if (head->next == NULL)
  {
    printf("List is empty, nothing to print!");
    return EMPTY_LIST_WARNING;
  }

  //temp variable on stack for looping through the list
  Person* temp = head->next;
  
  do{
    //printing values from the list
    printf("Name: %s, Surname: %s, Birth Year: %d\n",
          temp->name, temp->surname, temp->birthYear);

    temp = temp->next;
  }while(temp != NULL);
  

  return SUCCESS;
}