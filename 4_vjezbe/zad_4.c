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
int print_list(Polynomial* head);

int main(void)
{
    Polynomial** head_arr;
    char fileName[MAX_FILE_NAME] = {"\0"};
    int check_msg = 0;
    
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
    int i = 0;
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
            i = i + 1;
            *(head_arr + i) = (Polynomial*)calloc(1, sizeof(Polynomial));
             head = *(head_arr + i);

            do
            {
                sscanf(temp, "%d %d %n", &multiplier, &exp, &count_read);
                steps = steps + count_read;

                //storing values read from file
                insert_end(&head, multiplier, exp);
                
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
            *(head_arr + i) = head;
        }
        //head arr prazan gg triba vidit to mozda pokusat stavit da head_arr drzi adrese od headova a ne bas headove
        for(i = 0; i < 2; i++){
            print_list(*(head_arr+i));
            printf("....\n");
        }
    }

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