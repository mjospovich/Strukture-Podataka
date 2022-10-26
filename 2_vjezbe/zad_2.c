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
Person* find_next_surname(Person*, char[MAX_NAME_SIZE]);
int print_list(Person*);


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
  head->birthYear = 0;
  head->next = NULL;
  //strcpy(head->name, NULL);
  //strcpy(head->surname, NULL);

  //
  insert_end(&head, "Martin", "Joso", 19);
  insert_end(&head, "Luka", "Fifa", 20);
  print_list(head);
  printf("\n\n");
  insert_front(&head, "Andrija", "Hebrang", 74);

  print_list(head);

  //finding member with surname 
  Person* find = NULL;
  Person* wanted = NULL;
  
  find = find_next_surname(head, "Fifa");
  wanted = find->next;
  printf("Found user: %s %s, age %d\n", wanted->name, wanted->surname, wanted->birthYear);

  return SUCCESS;
}


//add comment
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


//add comment
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


//add comment
Person* find_next_surname(Person* head, char surname[MAX_NAME_SIZE])
{
  Person* temp = NULL;

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
      return temp;
    }
    temp = temp->next;
  }while(temp != NULL);

  temp = NULL;

  return temp;
}


//add comment
int print_list(Person* head)
{
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