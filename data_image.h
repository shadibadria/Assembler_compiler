#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#define SIZEOFCODE 5
#define SIZEOFADRESS 5

/*
file name : data_image
explain: this file is is header file that responsible for declre the function and the data image sruct


*/
typedef struct data_image {

  char Adress[SIZEOFADRESS];
  char opcode[SIZEOFCODE];
  char funct[SIZEOFCODE];
  char TAG[2];
  char adress_method[SIZEOFCODE];
  char label_name[SIZEOFCODE];

}
data_image;

data_image arr[100];
void append_command_to_file(char * filename, data_image data);
void append_register_to_file(char * filename, char * register_number);
void append_extern_tofile(char * filename);