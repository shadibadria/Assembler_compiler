/*
* File name: data_image.c
* This file provide all the functions of the commands initializing .
* Author : Shadi Badria <shadibadria@gmail.com>
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"data_image.h"

FILE * file_pointer;
int index_of_datatable = 0;

/*
append the data table to file name *.ob
@param filename - name of the file 
@param data  -  struct of data image
@return void 
*/
void append_command_to_file(char * filename, data_image data) {
  file_pointer = fopen(filename, "a");
  if (file_pointer == NULL) {
    printf("error creating file %s \n", filename);
    exit(0);
  }
  fputs(data.Adress, file_pointer);
  fputs("      ", file_pointer);
  fputs(data.opcode, file_pointer);
  fputs(data.funct, file_pointer);
  fputs(data.adress_method, file_pointer);
  fputs("        ", file_pointer);
  fputs(data.TAG, file_pointer);
  fputs("\n", file_pointer);
  fclose(file_pointer);
}