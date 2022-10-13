#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_BUFFER_SIZE (1024)
#define MAX_FILE_NAME (128)
#define MAX_LINE (128)
#define FILE_OPENING_ERROR (-1)


int countStudentsFromFile(char*);


int main(void)
{
  char fileName[MAX_FILE_NAME] = { 0 };
  int count = 0;

  printf("Insert filename > ");
  scanf(" %s", fileName);

  count = countStudentsFromFile(fileName);
  if (count >= 0)
    printf("Broj studenata u datoteci %s je %d", fileName, count);

  return 0;
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