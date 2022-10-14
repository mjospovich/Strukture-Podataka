#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_BUFFER_SIZE (1024)
#define MAX_FILE_NAME (128)
#define MAX_NAME_SIZE (128)
#define MAX_LINE (128)
#define FILE_OPENING_ERROR (-1)

struct _Student;

typedef struct _Student
{
  char name[MAX_NAME_SIZE];
  char surname[MAX_NAME_SIZE];
  int points;

}Student;


int countStudentsFromFile(char*);
int getStudentInfo(char*, int, Student);

int main(void)
{
  Student *studenti;

  //variables for countStudent
  char fileName[MAX_FILE_NAME] = { 0 };
  int numOfStudents = 0;

  //ask user for file name
  printf("Insert filename > ");
  scanf(" %s", fileName);

  //get value from function thats reading the file
  numOfStudents = countStudentsFromFile(fileName);

  //dynamically allocate memory based on result
  studenti = (Student*)malloc(sizeof(Student) * numOfStudents);

  //get info from file and store it in the structure
  getStudentInfo(fileName, numOfStudents, *studenti);

  //printing results on screen
  if (numOfStudents >= 0)
    printf("Broj studenata u datoteci %s je %d", fileName, numOfStudents);

  return 0;
}


int getStudentInfo(char* fileName, int numOfStudents, Student studenti)
{
  FILE *fp = NULL;
  fp = fopen(fileName, "r");

  int count = 0;
  char buffer[MAX_LINE] = { 0 };

  //add stuff


  fclose(fp);
}



int countStudentsFromFile(char *fileName)
{
  FILE *fp = NULL;
  fp = fopen(fileName, "r");

  int count = 0;
  char buffer[MAX_LINE] = { 0 };

  

  if (fp == NULL)
  {
    printf("The file %s didn't open!\r\n", fileName);
    return FILE_OPENING_ERROR;
  }
  
  while(!feof(fp))
  {
    fgets(buffer, MAX_BUFFER_SIZE, fp);

    if (strcmp("\n", buffer) != 0)
    {
      count++;
    }
  }

  fclose(fp);

  return count;
}