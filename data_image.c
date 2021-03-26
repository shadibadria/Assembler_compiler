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
function free_data_table - create/reset the datatable
@param none
@return void 
*/
void free_data_table() {
  int i = 0;
  for (i = 0; i < index_of_datatable; i++) {
    data_table[i].Adress[0] = '\0';
    data_table[i].adress_method[0] = '\0';
    data_table[i].funct[0] = '\0';
    data_table[i].label_name[0] = '\0';
    data_table[i].opcode[0] = '\0';
    data_table[i].TAG[0] = '\0';
  }
  index_of_datatable = 0;
}
/*
function append_size_to_file - add the first line of object file 
@param filename - the file name we want to write to
@param instruct_size - instruction table size
@param data_size  - the data count size
@return void 
*/
void append_size_to_file(char * filename, int instruct_size, int data_size) {
  char number[5];
  file_pointer = fopen(filename, "a");
  if (file_pointer == NULL) {
    printf("error creating file %s \n", filename);
    exit(0);
  }
  fputs("      ", file_pointer);
  sprintf(number, "%d", instruct_size);
  fputs(number, file_pointer);
  fputs("   ", file_pointer);
  sprintf(number, "%d", data_size);
  fputs(number, file_pointer);
  fputs("\n", file_pointer);
  fclose(file_pointer);
}
/*
function append_size_to_file - add 1 row of data_image
@param filename - the file name we want to write to
@param data  - its 1 instruction command
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