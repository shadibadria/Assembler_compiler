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
void init_data_table(){
  int i=0;
  for(i=0;i<index_of_datatable;i++){
      sprintf(data_table[index_of_datatable].Adress,"%s","\0");
      sprintf(data_table[index_of_datatable].adress_method,"%s","\0");
      sprintf(data_table[index_of_datatable].funct,"%s","\0");
      sprintf(data_table[index_of_datatable].opcode,"%s","\0");
      sprintf(data_table[index_of_datatable].TAG,"%s","\0");

      sprintf(data_table[index_of_datatable].label_name,"%s","\0");

  }
  index_of_datatable=0;
}
void append_size_to_file(char * filename, int instruct_size,int data_size){
  char number[5];
   file_pointer = fopen(filename, "a");
  if (file_pointer == NULL) {
    printf("error creating file %s \n", filename);
    exit(0);
  }
    fputs("      ", file_pointer);

  sprintf(number,"%d",instruct_size);
  fputs(number, file_pointer);
  fputs("   ", file_pointer);
    sprintf(number,"%d",data_size);
  fputs(number, file_pointer);
  fputs("\n", file_pointer);
    fclose(file_pointer);

}
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