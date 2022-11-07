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
#define MAX_POLYNOMIAL (16)
#define INSERTION_ERROR (-1)


struct _Polynomial;

typedef struct _Polynomial* Position;

//structure Person type structure _Person
typedef struct _Polynomial{
    int multiplier;
    int exp;
    Position next;

}Polynomial;


//function definitions
int insert_from_file(char*, Polynomial**);
int insert_end(Polynomial** head, int, int);
int insert_sorted(Polynomial** head, int, int);
int print_list(Polynomial* head);
void test_array(Polynomial** head_arr);
int insert_before(Polynomial** head, int, int, int);
Polynomial* find_exp(Polynomial*, int);


int main(void)
{
    Polynomial** head_arr;
    char fileName[MAX_FILE_NAME] = {"\0"};
    int check_msg = 0;
    int i = 0;
    
    //allocating an array of heads
    head_arr = (Polynomial**)calloc(MAX_POLYNOMIAL, sizeof(Polynomial*));
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

int insert_from_file(char* fileName, Polynomial** head_arr)
{
    int multiplier = 0;
    int exp = 0;
    int count_read = 0;
    int steps = 0;
    int i = 0, j = 0;
    int buffer_len;
    Polynomial *head = NULL, *temp_linked;

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
        steps = 0;
        count_read = 0;

        fgets(buffer, MAX_BUFFER_SIZE, fp);
        buffer_len = strlen(buffer);
        //printf("Buffer size: %d\n", buffer_len);
        strcpy(temp, buffer);

        //skip empty row
        if ((strcmp("\n", buffer) != 0))
        {
            head = NULL;
            i = i + 1;
            *(head_arr + i) = (Polynomial*)calloc(1, sizeof(Polynomial));
             head = *(head_arr + i);

            do
            {
                sscanf(temp, "%d %d %n", &multiplier, &exp, &count_read);
                steps = steps + count_read;

                //storing values read from file
                insert_sorted(&head, multiplier, exp);
                //insert_end(&head, multiplier, exp);
                
                //printf("Multiplier: %d Exp: %d CountRead: %d I: %d\n",multiplier, exp, count_read, i);
                if(steps > buffer_len){
                    printf("Wrong input, error with reading from file!\n");
                    return FILE_READ_ERROR;
                }
                else{
                    strcpy(temp, buffer + steps);
                }
                

            }while(steps != buffer_len);
            //funkcija provjera

            //adding 
            *(head_arr + i) = head;
        }
        
    }
    //head arr prazan gg triba vidit to mozda pokusat stavit da head_arr drzi adrese od headova a ne bas headove
    
    //test if its stored corretly
    test_array(head_arr);


    //closing the text file
    fclose(fp);

    return SUCCESS;
}

//adding a member at the last place in the list
int insert_end(Polynomial** head, int multiplier, int exp)
{
    Polynomial* new_member = (Polynomial*)calloc(1, sizeof(Polynomial));
    Polynomial* current = *head;

    //checking if memory has allocated or not
    if (new_member == NULL)
    {
        printf("Memory hasn't allocated properly!\n");
        return MEM_ALLOC_ERROR;
    }

    //last member points to NULL
    new_member->next = NULL;

    //assigning values to the new member
    new_member->multiplier = multiplier;
    new_member->exp = exp;
    
    //looping until we reach the previuos last member
    while (current->next != NULL) 
    {
        current = current->next;
    }
    current->next = new_member;

    return SUCCESS;
}


//print all member info in the list
int print_list(Polynomial* head)
{
    //chacking if list is empty before printing
    if (head->next == NULL)
    {
        printf("List is empty, nothing to print!");
        return EMPTY_LIST_WARNING;
    }

    //temp variable on stack for looping through the list
    Polynomial* temp = head->next;

    do {
        //printing values from the list
        printf("\tMultiplier: %d Exponent: %d\n",temp->multiplier, temp->exp);
        temp = temp->next;

    } while (temp != NULL);


    return SUCCESS;
}


void test_array(Polynomial** head_arr)
{
    int i = 0;

    for (i = 1; i<=6; i++){
        if(*(head_arr + i) == NULL){
            printf("Prazno\n");
            continue;
        }
        print_list(*(head_arr + i));
        printf("next...\n");
    }

}

int insert_sorted(Polynomial** head, int multiplier, int exp)
{
    Polynomial* current = *head;
    int chk_msg = 0;

    if (current->next == NULL)
    {
        insert_front(head, multiplier, exp);
        return SUCCESS;
    }

    //sort it bro
    do
    {
        //moving the current member to the next one for testing
        current = current->next;

        //checking values
        if(exp > current->exp){
            chk_msg = insert_before(head, multiplier, exp, current->exp);
            if (chk_msg == SUCCESS){
                return SUCCESS;
            }
            else{
                return INSERTION_ERROR;
            }
        }

        else if (exp == current->exp){
            current->multiplier = current->multiplier + multiplier;
            return SUCCESS;
        }

        else{
            continue;
        }

    }while(current->next != NULL);

    //if we didn't insert before we insert now at the end
    chk_msg = insert_end(head, multiplier, exp);
    if (chk_msg == SUCCESS){
                return SUCCESS;
            }
            else{
                return INSERTION_ERROR;
            }


    return SUCCESS;
}


int insert_front(Polynomial** head, int multiplier, int exp)
{
    Polynomial* new_member = (Polynomial*)calloc(1, sizeof(Polynomial));
    //checking if memory has allocated or not
    if (new_member == NULL)
    {
        printf("Memory hasn't allocated properly!\n");
        return MEM_ALLOC_ERROR;
    }
    //new_member now points to the member head used to point
    new_member->next = (*head)->next;

    //head now point to the new member
    (*head)->next = new_member;

    //assigning values to the new member
    new_member->multiplier = multiplier;
    new_member->exp = exp;

    return SUCCESS;
}


int insert_before(Polynomial** head, int multiplier, int exp, int exp_after)
{
    //new member
    Polynomial* new_member = (Polynomial*)calloc(1, sizeof(Polynomial));
    //checking if memory has allocated or not
    if (new_member == NULL)
    {
        printf("Memory hasn't allocated properly!\n");
        return MEM_ALLOC_ERROR;
    }

    //getting the member who is before the one after whoom we want to insert
    Polynomial* prev = find_exp(*head, exp_after);
    if (prev == NULL)
    {
        return MEMBER_NOT_FOUND;
    }

    //new member now points to the one after and prev points to new member
    new_member->next = prev->next;
    prev->next = new_member;
    
    //assigning values to the new member
    new_member->multiplier = multiplier;
    new_member->exp = exp;


    return SUCCESS;
}


//find the first member with given surname and return the member behind
Polynomial* find_exp(Polynomial* head, int exp)
{
    Polynomial* temp = NULL;

    //check if list is empty
    if (head->next == NULL)
    {
        printf("List is empty, nothing to find!");
        return temp;
    }

    temp = head;

    do {
        //finding the right surname and looping through
        if (temp->next->exp == exp) {
            //if its the right one then break and return it
            return temp; //returning the one before one we wanted to find
        }
        temp = temp->next;
    } while (temp != NULL);

    temp = NULL;

    //returning NULL if nothing is found
    return temp;
}


/*toDO
-dodaj funkciju provjera koja provjerava je li polinom skroz skracen ako nije
-skracuje ga do kraja (ako bude nula ne dodaje ga u array)
-ako je skracen in nije nula vreaca 0 i mozemo ga dodat u array
-ako ne preskacemo i onda novi polinom ce ic na njegovo misto

-zbrajanje polinoma
-mnozenje polinoma

-dosta provjera i ciscenja koda

*/
