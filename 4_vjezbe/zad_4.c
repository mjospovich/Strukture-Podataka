#pragma warning (disable: 4047)
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
#define EMPTY_POLYNOMIAL (-1)
#define END_OF_LIST (0)
#define NOT_END_OF_LIST (1)
#define MAX_EXPONENT (32)
#define SUM_ERROR (-1)


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
int insert_end2(Polynomial** head, int, int);
int insert_sorted(Polynomial** head, int, int);
int print_list(Polynomial* head);
void test_array(Polynomial** head_arr);
int insert_before(Polynomial** head, int, int, int);
Polynomial* find_exp(Polynomial*, int);
int check_polynominal(Polynomial* head);
int delete_member(Polynomial* head, int exp);
int delete_list(Polynomial* head);
Polynomial* sum_polynomial(Polynomial** head_arr);
int count_polynomial(Polynomial** head_arr);
int count_members(Polynomial*);
Polynomial* multiply_two_poly(Polynomial* head1, Polynomial* head2);
Polynomial* multiply_one_poly(Polynomial** result_head, Polynomial* head2, int, int);
Polynomial* multiply(Polynomial** head_arr);


int main(void)
{
    Polynomial** sum_head_arr;
    Polynomial** multi_head_arr;
    Polynomial* result_sum;
    Polynomial* result_multi;
    char fileName[MAX_FILE_NAME] = {"\0"};
    int check_msg = 0;
    int i = 0;
    
    //allocating an array of heads
    sum_head_arr = (Polynomial**)calloc(MAX_POLYNOMIAL, sizeof(Polynomial*));
    multi_head_arr = (Polynomial**)calloc(MAX_POLYNOMIAL, sizeof(Polynomial*));
    result_sum = (Polynomial*)calloc(1, sizeof(Polynomial));
    result_multi = (Polynomial*)calloc(1, sizeof(Polynomial));

    //checking if memory has allocated correctly
    if (multi_head_arr == NULL ||sum_head_arr == NULL || result_sum == NULL || result_multi == NULL)
    {
        printf("Memory not allocated, exiting the program!\n");
        return MEM_ALLOC_ERROR;
    }

    printf("Enter file name!\n");
    scanf("%s", fileName);

    check_msg = insert_from_file(fileName, sum_head_arr);
    check_msg = insert_from_file(fileName, multi_head_arr);
    
    printf("Number of polynomials: %d\n", count_polynomial(sum_head_arr));

    //sum of all polynomials
    result_sum = sum_polynomial(sum_head_arr);

    printf("Result sum of all polynomials is: \n");
    print_list(result_sum);

    //multiplication of all polynomials
    result_multi = multiply(multi_head_arr);

    printf("Result multiplication of all polynomials is: \n");
    print_list(result_multi);
    

    return SUCCESS;
}




int count_members(Polynomial* head)
{
    int i = 0;
    Polynomial* temp = head->next;

    do{
        
        i++;
        temp = temp->next;

    }while(temp != NULL);


    return i;
}


Polynomial* multiply(Polynomial** head_arr)
{
    Polynomial* result_head = (Polynomial*)calloc(1, sizeof(Polynomial));
    int num_pol = 0;
    int i = 0;

    if(result_head == NULL){
        return MEM_ALLOC_ERROR;
    }

    result_head = head_arr[1];

    num_pol = count_polynomial(head_arr);
    for (i = 2; i<=num_pol; i++)
    {
        result_head = multiply_two_poly(result_head, head_arr[i]);

    }

    return result_head;
}


Polynomial* multiply_two_poly(Polynomial* head1, Polynomial* head2)
{
    Polynomial* result_head = (Polynomial*)calloc(1, sizeof(Polynomial));
    Polynomial* tmp_head1 = head1->next;
    Polynomial* tmp_head2 = head2->next;

    if(result_head == NULL){
        return MEM_ALLOC_ERROR;
    }

    do{

        result_head = multiply_one_poly(&result_head, head2, tmp_head1->multiplier, tmp_head1->exp);

        tmp_head1 = tmp_head1->next;
    }while((tmp_head1) != NULL);

   //print_list(result_head);

    return result_head;
}


Polynomial* multiply_one_poly(Polynomial** result_head, Polynomial* head2, int multi1, int exp1)
{
    Polynomial* tmp_head2 = head2->next;

    int multi_temp = 0;
    int exp_temp = 0;
   
    do{
        multi_temp = multi1 * tmp_head2->multiplier;
        exp_temp = exp1 + tmp_head2->exp;
        insert_sorted(result_head, multi_temp, exp_temp);

            
        tmp_head2 = tmp_head2->next;
    }while((tmp_head2) != NULL);

    return *result_head;
}

int insert_from_file(char* fileName, Polynomial** head_arr)
{
    int multiplier = 0;
    int exp = 0;
    int count_read = 0;
    int steps = 0;
    int i = 0, j = 0, chk_msg = 0;
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

            //only do this if the polynomial before this one was entered into the list
            //if not new one will take its place so no need to allocate new memory
            if (chk_msg != EMPTY_POLYNOMIAL)
            {
                i = i + 1;
                *(head_arr + i) = (Polynomial*)calloc(1, sizeof(Polynomial));
                head = *(head_arr + i);
            }

            do
            {
                sscanf(temp, "%d %d %n", &multiplier, &exp, &count_read);
                steps = steps + count_read;

                //storing values read from file
                if (multiplier != 0){
                    insert_sorted(&head, multiplier, exp);
                }
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
            //checking the polynominal
            chk_msg = check_polynominal(head);

            //if check is successful then add onto the array if not skip
            if (chk_msg == EMPTY_POLYNOMIAL){
                //adding 
                *(head_arr + i) = head;
            }
        }
        
    }
    //head arr prazan gg triba vidit to mozda pokusat stavit da head_arr drzi adrese od headova a ne bas headove
    
    //test if its stored corretly
    //test_array(head_arr);


    //closing the text file
    fclose(fp);

    return SUCCESS;
}




Polynomial* sum_polynomial(Polynomial** head_arr)
{
    Polynomial** tmp_head_arr = head_arr;
    test_array(tmp_head_arr);

    Polynomial* result_head = (Polynomial*)calloc(1, sizeof(Polynomial));
    if(result_head == NULL){
        return MEM_ALLOC_ERROR;
    
    }
    result_head->exp = 0;
    result_head->multiplier = 0;
    result_head->next = NULL;

    int temp = NOT_END_OF_LIST;
    int i = 0;
    int result_exp = 0;
    int result_multiplier = 0;
    int curr_exp = 0;
    int curr_multiplier = 0;
    int chk_msg = 0;
    int prev_result_exp = MAX_EXPONENT;
    //getting the num of members in head arr array
    int num_of_polynomials = count_polynomial(tmp_head_arr);

    do{
        result_exp = -MAX_EXPONENT;
        result_multiplier = 0;

        for(i = 1; i<=num_of_polynomials; i++)
        {
            curr_exp = ((*(tmp_head_arr+i))->next)->exp;

            if((curr_exp > result_exp) && (curr_exp < prev_result_exp)){
                result_exp = curr_exp;
            }
        }
        prev_result_exp = result_exp;


        for(i = 1; i<=num_of_polynomials; i++)
        {
            curr_exp = ((*(tmp_head_arr+i))->next)->exp;
            curr_multiplier = ((*(tmp_head_arr+i))->next)->multiplier;

            if(curr_exp == result_exp)
            {
                result_multiplier = result_multiplier + curr_multiplier;

                //moving the ones that we sum to the right
                //((*(tmp_head_arr+i))->next) = ((*(tmp_head_arr+i))->next)->next;
            }
        }

        chk_msg = insert_end(&result_head, result_multiplier, result_exp);
        if (chk_msg != SUCCESS){
            printf("Error while summing!\n");
            return SUM_ERROR;
        }

        //checking if all lists have reached the end
        for(i = 1; i<=num_of_polynomials; i++)
        {
            if((((*(tmp_head_arr+i))->next)->next) == NULL && (((*(tmp_head_arr+i))->next)->exp >= result_exp)){
                temp = END_OF_LIST;
            }
            else{
                temp = NOT_END_OF_LIST;
                break;
            }

        }

        for(i = 1; i<=num_of_polynomials; i++)
        {
            curr_exp = ((*(tmp_head_arr+i))->next)->exp;
            curr_multiplier = ((*(tmp_head_arr+i))->next)->multiplier;

            if((curr_exp == result_exp) && ((((*(tmp_head_arr+i))->next)->next) != NULL))
            {
                //moving the ones that we sum to the right
                ((*(tmp_head_arr+i))->next) = ((*(tmp_head_arr+i))->next)->next;
            }
        }

    }while(temp != END_OF_LIST);


    //checking the polynomial and shortening it
    chk_msg = check_polynominal(result_head);
    if (chk_msg == EMPTY_POLYNOMIAL){
        return EMPTY_POLYNOMIAL;
    }

    return result_head;
}


//breaking the list apart and freeing memory from members 1 by 1
int delete_list(Polynomial* head)
{
    Polynomial* temp = head->next;

    do
    {
        delete_member(head, temp->exp);
        temp = head->next;
      
    }while (temp != NULL);

    free(head);

    return SUCCESS;
}



int count_polynomial(Polynomial** head_arr)
{
    int n_of_members = 0;
    int i = 1;

    do{
        if(*(head_arr + i) == NULL){
            break;
        }
        i ++;

    }while(1);

    n_of_members = i - 1;

    return n_of_members;
}



int check_polynominal(Polynomial* head)
{
    Polynomial* current = head;
    
    do{
        current = current->next;

        //checking if the multiplier with exponent x is 0 and deleting it if so
        if (current->multiplier == 0)
        {
            delete_member(head, current->exp);
        }

    }while(current->next != NULL);

    //if after shortening it its now empty then we dont need to insert it into the array
    if (head->next == NULL){
        return EMPTY_POLYNOMIAL;
    }


    return SUCCESS;
}


//removing 1 member from the list
int delete_member(Polynomial* head, int exp)
{
    //calling function to get previous member
    Polynomial* prev = find_exp(head, exp);
    Polynomial* temp = NULL;

    //check if we can find right member
    if (prev == NULL)
    {
        printf("Couldn't find the member with exponent %d!\n", exp);
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
        if(temp->next == NULL){
            if (temp->multiplier == 1)
            {

                if(temp->exp == 1){
                    printf("x\n");
                }
                else if (temp->exp == 0){
                    printf("1\n");
                }
                else{
                    printf("x^%d\n", temp->exp);
                }

            }
            else
            {
                if(temp->exp == 1){
                    printf("%dx\n", temp->multiplier);
                }
                else if (temp->exp == 0){
                    printf("%d\n", temp->multiplier);
                }
                else{
                    printf("%dx^%d\n",temp->multiplier, temp->exp);
                }
            }
        }
        
        else{
            if (temp->multiplier == 1)
            {

                if(temp->exp == 1){
                    printf("x + ");
                }
                else if (temp->exp == 0){
                    printf("1 + ");
                }
                else{
                    printf("x^%d + ", temp->exp);
                }

            }
            else
            {
                if(temp->exp == 1){
                    printf("%dx + ", temp->multiplier);
                }
                else if (temp->exp == 0){
                    printf("%d + ", temp->multiplier);
                }
                else{
                    printf("%dx^%d + ",temp->multiplier, temp->exp);
                }
            }
        }
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

