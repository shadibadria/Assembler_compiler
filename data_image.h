#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#define SIZEOFCODE 13
#define SIZEOFADRESS 5

typedef struct data_image {

  char Adress[SIZEOFADRESS]; 
  char code[SIZEOFCODE];
  char TAG;
}data_image;


data_image arr[100];
void append_to_file(char *filename,data_image data);
