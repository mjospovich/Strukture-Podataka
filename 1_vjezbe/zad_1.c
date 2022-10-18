#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//defininig constant values
#define MAX_BUFFER_SIZE (1024)
#define MAX_FILE_NAME (128)
#define MAX_NAME_SIZE (128)
#define MAX_LINE (128)
#define FILE_OPENING_ERROR (-1)
#define GET_INFO_SUCCESS (0)
#define MAX_NUM_POINTS (60)

//student structure
struct _Student;

typedef struct _Student
{
  char name[MAX_NAME_SIZE];
  char surname[MAX_NAME_SIZE];
  int points;

}Student;


//funtion definitions
int countStudentsFromFile(char*);
int getStudentInfo(char*, int, Student*);
void printStudentInfo(int, Student*);


int main(void)
{
  //variables for get_student_info
  Student *studenti;
  int i = 0;
  int show = -1;

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
  show = getStudentInfo(fileName, numOfStudents, studenti);

  //printing num of students on screen
  if (numOfStudents >= 0)
    printf("Broj studenata u datoteci %s je %d\n", fileName, numOfStudents);

  //printing student info on screen
  if (show == 0)
  {
    printStudentInfo(numOfStudents, studenti);
  }
  else
  {
    printf("Error when getting student info from the file!\n");
  }

  return 0;
}


//function that opens the textfile reads all student info from it,
//stores it in a structure and closes the file
int getStudentInfo(char* fileName, int numOfStudents, Student *studenti)
{
  int i = 0;
  int count = 0;
  char buffer[MAX_LINE] = { 0 };

  FILE *fp = NULL;
  fp = fopen(fileName, "r");

  
  //check if file has opened successfully (if not return error)
  if (fp == NULL)
  {
    printf("The file %s didn't open!\r\n", fileName);
    return FILE_OPENING_ERROR;
  }


  for (i = 0; i < numOfStudents; i++)
  { 
    char nameInp[MAX_NAME_SIZE] = "";
    char surnameInp[MAX_NAME_SIZE] = "";
    int pointsInp = 0;

    while(1)
    {
      fgets(buffer, MAX_BUFFER_SIZE, fp);

      if (strcmp("\n", buffer) != 0)
      {
        break;
      }
    }

    sscanf(buffer, "%s %s %d", nameInp, surnameInp, &pointsInp);


    Student *currentStudent = studenti + i;

    strcpy(currentStudent->name, nameInp);
    strcpy(currentStudent->surname, surnameInp);
    currentStudent->points = pointsInp;

  }
  
  fclose(fp);

  return GET_INFO_SUCCESS;
}


//function that takes in num of students and structure pointer
//it prints all student info on screen
void printStudentInfo(int numOfStudents, Student *studenti)
{
    int i = 0;
    float rel_points = 0.0;
    printf("\nPrinting student info:\n");

    for (i = 0; i<numOfStudents; i++)
    {
      Student stud = *(studenti + i);
      rel_points = (((float)stud.points / MAX_NUM_POINTS) * 100);

      printf("Student %s %s ima %d apsolutnih odnosno %.2f%% bodova!\n",stud.name, stud.surname, stud.points, rel_points);
    } 
  
}


//function that opens the textfile reads how many students there are
//then it returns the value that it got
int countStudentsFromFile(char* fileName)
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