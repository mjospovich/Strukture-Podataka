#pragma warning(disable : 4047)
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
#define STACK_ERROR (-1)
#define PRINT_ERROR (-1)

// Tree structure
struct _Tree;
typedef struct _Tree *Tree_Pos; // pointer to Tree structure member
typedef struct _Tree
{
  Tree_Pos child;
  Tree_Pos sibbling;
  char name[MAX_NAME_SIZE];

} Tree;

// Stack structure
struct _Stack;
typedef struct _Stack *Position; // pointer to Stack structure member
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
int pop_from_stack(Position* head);
int push_on_stack(Position* head, Tree_Pos current);
int change_dir(Position head, Tree_Pos *current);
Tree_Pos delete_tree(Tree_Pos current);
int delete_stack(Position head);
int exit_program(Tree_Pos root, Position head);

int main()
{

  int check_msg_1 = 0, check_msg_2 = 0;
  Tree_Pos root = create_tree_root();  // allocates and names the root to C
  Position head = create_stack_head(); // allocates space for stack head and checks
  Tree_Pos current = root;

  // checking if both functions above worked fine
  if ((head && root) == NULL)
  {
    return MEM_ALLOC_ERROR;
  }

  make_dir(current);
  make_dir(current);
  print_dir(current);
  change_dir(head, &current);
  make_dir(current);
  make_dir(current);
  print_dir(current);
  change_dir(head, &current);
  print_dir(current);

  exit_program(root, head); 
  // ne radi delete stack napuni se nekin random values
  // al to nije glavni problem
  // stack neradi kako triva probably isa san minjat al odusta u pola pa to triba nastavit
  //dodat pointer svaki put kad se minja a ne onako kako je bilo
  print_dir(root);

  return SUCCESS;
}


int exit_program(Tree_Pos root, Position head){
  int check_msg_1 = 0, check_msg_2 = 0;

  check_msg_1 = delete_stack(head);
  if(check_msg_1 != SUCCESS){
    return DEL_ERROR;
  }

  root->child = delete_tree(root->child);

  if((root->child) != NULL){
    printf("Delete error!\n");
    return DEL_ERROR;
  }
  free(root);

  return SUCCESS;
}


Tree_Pos delete_tree(Tree_Pos current)
{
  if(current == NULL)
  {
    return NULL;
  }

  current->child = delete_tree(current->child);
  current->sibbling = delete_tree(current->sibbling);

  free(current);
  return NULL;
}


int delete_stack(Position head)
{
  Position temp = NULL;

  do
  {
    temp = head->next;
    head->next = head->next->next;
    temp->next = NULL;
    free(temp);

  } while (head->next != NULL);
    free(head);

  return SUCCESS;
}

int change_dir(Position head, Tree_Pos *current)
{
  char name[MAX_NAME_SIZE] = {'\0'};
  printf("Name: ");
  scanf(" %s", name);

  if (strcmp(name, "..") == 0)
  {
    (*current) = head->next->address;
    pop_from_stack(&head);

    return SUCCESS;
  }

  Tree_Pos temp = (*current)->child;

  do
  {
    if (strcmp(temp->name, name) == 0)
    {
      push_on_stack(&head, *current);
      (*current) = temp;
      return SUCCESS;
    }
    temp = temp->sibbling;

  } while (temp != NULL);

  printf("We didn't find %s!\n", name);

  return BAD_INPUT;
}

int pop_from_stack(Position* head)
{
  if (NULL == (*head)->next)
  {
    printf("Stack already empty\n");
    return SUCCESS;
  }

  Position temp = (*head)->next;

  (*head)->next = ((*head)->next)->next;
  temp->next = NULL;
  free(temp);

  return SUCCESS;
}

int push_on_stack(Position* head, Tree_Pos current)
{
  Position new_member = (Stack *)calloc(1, sizeof(Stack));
  if (NULL == new_member)
  {
    return MEM_ALLOC_ERROR;
  }

  new_member->address = current;
  new_member->next = (*head)->next;
  (*head)->next = new_member;

  return SUCCESS;
}

int print_dir(Tree_Pos current)
{
  Tree_Pos temp = current->child;

  if (temp == NULL)
  {
    printf("%s has no children!\n", current->name);
    return SUCCESS;
  }

  printf("%s:\n", current->name);
  do
  {
    printf("\t%s\n", temp->name);
    temp = temp->sibbling;

  } while (temp != NULL);

  return SUCCESS;
}

int make_dir(Tree_Pos current)
{
  Tree_Pos new_dir = NULL;
  char name[MAX_NAME_SIZE] = {'\0'};
  new_dir = (Tree *)calloc(1, sizeof(Tree));
  new_dir->sibbling = NULL;

  if (NULL == new_dir)
  {
    return MEM_ALLOC_ERROR;
  }

  printf("Name: ");
  scanf(" %s", name);

  strcpy(new_dir->name, name);

  // if current has no children just insert it front
  if (current->child == NULL)
  {
    current->child = new_dir;
    return SUCCESS;
  }

  current->child = insert_sorted(current->child, new_dir);

  return SUCCESS;
}

Tree_Pos insert_sorted(Tree_Pos current, Tree_Pos new_dir)
{
  if (NULL == current)
  {
    return new_dir;
  }

  if (strcmp(current->name, new_dir->name) > 0)
  {
    new_dir->sibbling = current;
    return new_dir;
  }

  current->sibbling = insert_sorted(current->sibbling, new_dir);

  return current;
}

Tree_Pos create_tree_root()
{
  Tree_Pos root = (Tree *)calloc(1, sizeof(Tree));

  if (NULL == root)
  {
    return root; // same as memory alloc error
  }
  strcpy(root->name, "C"); // adds name to root

  return root;
}

Position create_stack_head()
{
  Position head = (Stack *)calloc(1, sizeof(Stack));

  if (NULL == head)
  {
    return head; // same as memory alloc error
  }

  return head;
}