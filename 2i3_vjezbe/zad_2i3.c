#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//defining constant values
#define MAX_BUFFER_SIZE (1024)
#define MAX_FILE_NAME (128)
#define MAX_NAME_SIZE (128)
#define FILE_OPENING_ERROR (-1)
#define SUCCESS (0)
#define MEM_ALLOC_ERROR (-1)
#define EMPTY_LIST_WARNING (-1)
#define MEMBER_NOT_FOUND (-1)
#define DEL_ERROR (-1)
#define MAX_LINE (128)
#define INSERT_ERROR (-1)
#define MENU_ERROR (-1)


struct _Person;

typedef struct _Person* Position;

//structure Person type structure _Person
typedef struct _Person {
    char name[MAX_NAME_SIZE];
    char surname[MAX_NAME_SIZE];
    int birthYear;
    Position next;

}Person;


//function definitions
int insert_from_file(char*, Person*);
int export_to_file(char*, Person*);
int insert_end(Person**, char*, char*, int);
int insert_front(Person**, char*, char*, int);
Person* find_next_surname(Person*, char*); 
int print_list(Person*);
int delete_member(Person*, char*);
int print_member(Person*, char*);
int delete_list(Person*);
int insert_next(Person**, char*, char*, int);
int insert_before(Person**, char*, char*, int);
int bubble_sort(Person*);
int print_menu();
int freeing_memory(Person*);
Person* create_person();


int main(void)
{
    //variables for input
    int choice = 0;
    char name[MAX_NAME_SIZE] = { "/0" };
    char surname[MAX_NAME_SIZE] = { "/0" };
    int birthYear = 0;
    int catch_msg = 0;
    char fileName[MAX_FILE_NAME] = { 0 };

    //the head of linked list
    Person* head = create_person();
    if (head == NULL){
        return MEM_ALLOC_ERROR;
    }

    //mainloop
    do
    {
        choice = 0;
        catch_msg = 0;

        catch_msg = print_menu();
        if (catch_msg != SUCCESS){
            return MENU_ERROR;
        }

        scanf("%d", &choice);

        //asking needed input
        if (choice == 2 || choice == 3 || choice == 4 || choice ==5)
        {
            printf("You need to enter info for new member!\n");
            printf("NAME SURNAME BIRTHYEAR\n");
            scanf(" %s %s %d", name, surname, &birthYear);
        }

        if (choice == 7 || choice == 8)
        {
            printf("You need to enter info for member you display/remove\n");
            printf("SURNAME\n");
            scanf(" %s", surname);
        }

        if (choice == 1 || choice == 10)
        {
           printf("Insert filename > ");
           scanf(" %s", fileName);
        }

        switch (choice)
        {
            case 1:
                //insert from file
                catch_msg = insert_from_file(fileName, head);
                if (catch_msg == SUCCESS) {
                    printf("Inserted list successfully!\n");
                }
                else {
                    printf("Error has occured!\n");
                }

                break;

            case 2:
                //insert_front
                catch_msg = insert_front(&head, name, surname, birthYear);
                if (catch_msg == SUCCESS) {
                    printf("Inserted member successfully!\n");
                }
                else {
                    printf("Error has occured!\n");
                }

                break;

            case 3:
                //insert_end
                catch_msg = insert_end(&head, name, surname, birthYear);
                if (catch_msg == SUCCESS) {
                    printf("Inserted member successfully!\n");
                }
                else {
                    printf("Error has occured!\n");
                }
                break;
            
            case 4:
                //insert_next
                catch_msg = insert_next(&head, name, surname, birthYear);
                if (catch_msg == SUCCESS) {
                    printf("Inserted member successfully!\n");
                }
                else {
                    printf("Error has occured!\n");
                }
                break;

            case 5:
                //insert_before
                catch_msg = insert_before(&head, name, surname, birthYear);
                if (catch_msg == SUCCESS) {
                    printf("Inserted member successfully!\n");
                }
                else {
                    printf("Error has occured!\n");
                }
                break;

            case 6:
                //print_list
                catch_msg = print_list(head);
                if (catch_msg != SUCCESS) {
                    printf("Error has occured!\n");
                }
                break;

            case 7:
                //print_member
                catch_msg = print_member(head, surname);
                if (catch_msg != SUCCESS) {
                    printf("Error has occured!\n");
                }
                break;

            case 8:
                //delete_member
                catch_msg = delete_member(head, surname);
                if (catch_msg == SUCCESS) {
                    printf("Deleted member %s!\n", surname);
                }
                else {
                    printf("Error has occured!\n");
                }
                break;
            
            case 9:
                //sort list
                catch_msg = bubble_sort(head);
                if (catch_msg == SUCCESS) {
                    printf("Sorted the list!\n");
                }
                else {
                    printf("Error has occured!\n");
                }
            
                break;

            case 10:
                //export to file
                catch_msg = export_to_file(fileName, head);
                if (catch_msg == SUCCESS) {
                    printf("Inserted list successfully!\n");
                }
                else {
                    printf("Error has occured!\n");
                }

                break;

            default:
                break;
            }

        printf("\n");

    } while (choice != 0);


    //free memory and check if it did that
    if (!freeing_memory(head)){
        return DEL_ERROR;
    }

    return SUCCESS;
}

Person* create_person()
{
     //declaring head and setting everything to NULL
    Person* head = (Person*)calloc(1, sizeof(Person));
    //checking if memory has allocated or not
    if (head == NULL)
    {
        printf("Memory hasn't allocated properly!\n");
        return head; //head = NULL here
    }

    //initialization
    head->birthYear = 0;
    head->next = NULL;
    strcpy(head->name, "");
    strcpy(head->surname, "");

    return head;
}

//freeing memory at the end
int freeing_memory(Person* head)
{
    printf("Freeing memory...\n");
    int deleted = 0;
    deleted = delete_list(head);
    if (deleted == 0)
        printf("Memory freed!\n");
    else{
        printf("Couldn't free the memory!");
        return DEL_ERROR;
    }

    printf("Exiting the program...\n");

    return SUCCESS;
}

//printing the main menu
int print_menu()
{
    printf("Choose:\n \t=> 0  EXIT\n\t=> 1  INSERT FROM FILE\n\t=> 2  INSERT FRONT\n\t=> 3  INSERT BACK\n\t=> 4  INSERT AFTER MEMBER\n\t=> 5  INSERT BEFORE MEMBER\n");
    printf("\t=> 6  PRINT LIST\n\t=> 7  PRINT MEMBER\n\t=> 8  REMOVE MEMBER\n\t=> 9  SORT LIST\n\t=> 10 EXPORT TO FILE\n\n");
    return SUCCESS;
}

//bubble sort for linked list
int bubble_sort(Person* head)
{
    //variables for swapping
    Person *p = NULL, *end = NULL, *q = NULL, *temp = NULL, *r = temp;
    
    //checking if list is empty
    if (head->next == NULL)
    {
        printf("List is empty!\n");
        return EMPTY_LIST_WARNING;
    }

    for (end = NULL; end != head->next; end = p)
    {
        for (p = r = head; p->next != end; r = p, p = p->next)
        {
            //setting it to member after p for comparing
            q = p->next;

            //comparing surnames
            if(strcmp(p->surname, q->surname) > 0)
            {
               //swapping members
               p->next = q->next;
               q->next = p;

               if (p != head){
                r->next = q;
               }
               else{
                head = q;
               }

               temp = p;
               p = q;
               q = temp;
            }

        }

    }

    return SUCCESS;
}


//breaking the list apart and freeing memory from members 1 by 1
int delete_list(Person* head)
{
    Person* temp = head->next;

    do
    {
        delete_member(head, temp->surname);
        temp = head->next;
      
    }while (temp != NULL);

    free(head);

    return SUCCESS;
}


//inserting list from a file
int insert_from_file(char* fileName, Person* head)
{
    char name[MAX_NAME_SIZE] = { "\0" };
    char surname[MAX_NAME_SIZE] = { "\0" };
    int birthYear = 0;
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


//export list to a file
int export_to_file(char* fileName, Person* head)
{
    FILE *fp = NULL;
    fp = fopen(fileName, "w");
  
    //checking if the file opened correctly, if not returning error
    if (fp == NULL)
    {
        printf("The file %s didn't open!\r\n", fileName);
        return FILE_OPENING_ERROR;
    }
  
    //chacking if list is empty before printing
    if (head->next == NULL)
    {
        printf("List is empty, nothing to print!");
        return EMPTY_LIST_WARNING;
    }

    //temp variable on stack for looping through the list
    Person* temp = head->next;

    do {
        //printing values from the list
        fprintf(fp,"Name: %s, Surname: %s, Birth Year: %d\n",
            temp->name, temp->surname, temp->birthYear);

        temp = temp->next;
    } while (temp != NULL);

    //closing the text file
    fclose(fp);

    return SUCCESS;
}


//adding a member after another member in the list
int insert_next(Person** head, char* name , char* surname, int birthYear)
{
    char surname_prev[MAX_NAME_SIZE] = "";
    printf("Enter surname of the member you want to insert after:\n");
    scanf("%s", surname_prev);

    //new member
    Person* new_person = (Person*)calloc(1, sizeof(Person));
    new_person->next = NULL;

    //checking if memory has allocated or not
    if (new_person == NULL)
    {
        printf("Memory hasn't allocated properly!\n");
        return MEM_ALLOC_ERROR;
    }

    //getting the member who is before the one after whoom we want to insert
    Person* prev_prev = find_next_surname(*head, surname_prev);
    if (prev_prev == NULL)
    {
        return MEMBER_NOT_FOUND;
    }

    //the member after whoom we want to insert
    Person* prev = prev_prev->next;
    //the member after the one we insert
    Person* temp = prev->next;

    prev->next = new_person;
    new_person->next = temp;
    
    //assigning values to the new member
    strcpy(new_person->name, name);
    strcpy(new_person->surname, surname);
    new_person->birthYear = birthYear;


    return SUCCESS;
}


//adding a member before another member in the list
int insert_before(Person** head, char* name , char* surname, int birthYear)
{
    //member before whoom we will insert new one
    char surname_after[MAX_NAME_SIZE] = "";

    printf("Enter surname of the member you want to insert before:\n");
    scanf("%s", surname_after);

    //new member
    Person* new_person = (Person*)calloc(1, sizeof(Person));
    new_person->next = NULL;

    //checking if memory has allocated or not
    if (new_person == NULL)
    {
        printf("Memory hasn't allocated properly!\n");
        return MEM_ALLOC_ERROR;
    }

    //getting the member who is before the one after whoom we want to insert
    Person* prev = find_next_surname(*head, surname_after);
    if (prev == NULL)
    {
        return MEMBER_NOT_FOUND;
    }

    //new member now points to the one after and prev points to new member
    new_person->next = prev->next;
    prev->next = new_person;
    
    //assigning values to the new member
    strcpy(new_person->name, name);
    strcpy(new_person->surname, surname);
    new_person->birthYear = birthYear;


    return SUCCESS;
}


//adding a member at the last place in the list
int insert_end(Person** head, char* name, char *surname, int birthYear)
{
    Person* new_person = (Person*)calloc(1, sizeof(Person));
    //checking if memory has allocated or not
    if (new_person == NULL)
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
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_person;

    return SUCCESS;
}


//adding a member after head in the list
int insert_front(Person** head, char* name, char* surname, int birthYear)
{
    Person* new_person = (Person*)calloc(1, sizeof(Person));
    //checking if memory has allocated or not
    if (new_person == NULL)
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
int delete_member(Person* head, char* surname)
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
int print_member(Person* head, char* surname)
{
    Person* wanted = find_next_surname(head, surname)->next;

    //check if we got the data needed
    if (wanted == NULL)
        return MEMBER_NOT_FOUND;

    printf("Person's name is %s %s, they were born in %d!\n", wanted->name, wanted->surname, wanted->birthYear);


    return SUCCESS;
}


//find the first member with given surname and return the member behind
Person* find_next_surname(Person* head, char* surname)
{
    Person* temp = NULL;

    //check if list is empty
    if (head->next == NULL)
    {
        printf("List is empty, nothing to find!");
        return temp;
    }

    temp = head;

    do {
        //finding the right surname and looping through
        if (strcmp((temp->next)->surname, surname) == 0) {
            //if its the right one then break and return it
            return temp; //returning the one before one we wanted to find
        }
        temp = temp->next;
    } while (temp != NULL);

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

    do {
        //printing values from the list
        printf("\tName: %s, Surname: %s, Birth Year: %d\n",
            temp->name, temp->surname, temp->birthYear);

        temp = temp->next;
    } while (temp != NULL);


    return SUCCESS;
}