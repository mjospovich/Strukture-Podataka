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
#define BAD_INPUT (-1)
#define DEL_ERROR (-1)
#define FILE_OPENING_ERROR (-1)
#define MAX_BUFFER_SIZE (1024)
#define MAX_FILE_NAME (128)
#define MAX_NAME_SIZE (64)
#define MAX_LINE (128)
#define INSERTION_ERROR (-1)
#define OPERATE_ERROR (-1)
#define STACK_ERROR (-1)
#define PRINT_ERROR (-1)

// Tree structure
struct _Tree;
typedef struct _Tree* Tree_Pos; // pointer to Tree structure member
typedef struct _Tree
{
  Tree_Pos child;
  Tree_Pos sibbling;
  char name[MAX_NAME_SIZE];

} Tree;

// Stack structure
struct _Stack;
typedef struct _Stack* Position; // pointer to Stack structure member
typedef struct _Stack
{
  Position next;
  Tree_Pos address;

} Stack;

Tree_Pos create_tree_root();
Position create_stack_head();
Tree_Pos insert_sorted(Tree_Pos current, Tree_Pos new_dir);
int make_dir(Tree_Pos current);
int print_dir(Tree_Pos current);

int main()
{

  int check_msg_1 = 0, check_msg_2 = 0;
  Tree_Pos root = create_tree_root(); // allocates and names the root to C
  Position head = create_stack_head(); // allocates space for stack head and checks

  // checking if both functions above worked fine
  if ((head && root) == NULL)
  {
    return MEM_ALLOC_ERROR;
  }

  make_dir(root);
  make_dir(root);
  make_dir(root);
  make_dir(root);
  //make_dir(root);

  print_dir(root);

  return SUCCESS;
}

int print_dir(Tree_Pos current)
{
  Tree_Pos temp = current->child;

  if(temp == NULL){
    printf("%s has no children!\n", current->name);
    return SUCCESS;
  }

  printf("%s:\n", current->name);
  do{
    printf("\t%s\n", temp->name);
    temp = temp->sibbling;

  }while(temp != NULL);

  return SUCCESS;
}


int make_dir(Tree_Pos current)
{
  Tree_Pos new_dir = NULL;
  char name[MAX_NAME_SIZE] = {'\0'};
  new_dir = (Tree*)calloc(1, sizeof(Tree));
  new_dir->sibbling = NULL;

  if (NULL == new_dir)
  {
    return MEM_ALLOC_ERROR;
  }

  printf("Name: ");
  scanf(" %s", name);

  strcpy(new_dir->name, name);

  //if current has no children just insert it front
  if (current->child == NULL){
    current->child = new_dir;
    return SUCCESS;
  }

  current->child = insert_sorted(current->child, new_dir);

  return SUCCESS;
}

Tree_Pos insert_sorted(Tree_Pos current, Tree_Pos new_dir)
{
  if(NULL == current){
    return new_dir;
  }

  if(strcmp(current->name, new_dir->name) > 0){
    new_dir->sibbling = current;
    return new_dir;
  }

  current->sibbling = insert_sorted(current->sibbling, new_dir);

  return current;
}

Tree_Pos create_tree_root()
{
  Tree_Pos root = (Tree*)calloc(1, sizeof(Tree));

  if (NULL == root)
  {
    return root; //same as memory alloc error
  }
  strcpy(root->name, "C"); // adds name to root

  return root;
}

Position create_stack_head()
{
  Position head = (Stack*)calloc(1, sizeof(Stack));

  if (NULL == head)
  {
    return head; //same as memory alloc error
  }

  return head;
}