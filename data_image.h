/*
filename : data_image.h
this file is is header file that responsible for declre the function and the data image sruct
*/

#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#define SIZEOFCODE 5
#define SIZEOFADRESS 5
#define MAX_Data 4095
#define TAG_SIZE 2
/*
struct of the data image
@val adress - has the adress of the program IC
@val opcode - has the first 4 bits of the memory
@val funct - has the second 4 bits of the memory
@val TAG    - has the Tag name of the type (A,R,E)
@val adress_method  - has the adress method 
@val label_name     - has the label name (helps with second pass)
*/
typedef struct data_image {
  char Adress[SIZEOFADRESS];
  char opcode[SIZEOFCODE];
  char funct[SIZEOFCODE];
  char TAG[TAG_SIZE];
  char adress_method[SIZEOFCODE];
  char label_name[SIZEOFCODE];
}
data_image;

data_image arr[MAX_Data];
void append_command_to_file(char * filename, data_image data);
void append_register_to_file(char * filename, char * register_number);