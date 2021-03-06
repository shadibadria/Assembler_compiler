/*
 * File Name : file_proccess.c
 * This file provide all the functions for file creating /writing/creating files.
 * Author : Shadi Badria <shadibadria@gmail.com>
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "file_proccess.h"
#include "symbol_table.h"
#include "data_image.h"

FILE * file_pointer;
int extern symbol_table_size;
int extern DC;
int extern IC;
int extern index_of_datatable;

/*
function check_file - check if file has .as argument
@param file_name  - the file name we want to check
@return 1 - success , 0 - error
*/
int check_file(char * file_name) {
  char * file_ending = strrchr(file_name, '.');
  if (file_ending == NULL) {
    printf("\n*** ERROR : File Does Not Have *.as Extention.. ***\n\n");
    return 0;
  }
  /*if file does end with .as*/
  if ((!strcmp(file_ending + 1, "as"))) {
    return 1;
  } else {
    return 0;
  }
}
/*
function append_entry_tofile - create and add all entry labels to file(.ent)
@param file_name  - the file name we want to create
@return void
*/
void append_entry_tofile(char * filename) {
  int i = 0;
  file_pointer = fopen(filename, "a");
  if (file_pointer == NULL) {
    printf("error creating file %s \n", filename);
    exit(0);
  }
  if (symbol_table[i].attribute != NULL) {
    for (i = 0; i < symbol_table_size; i++) {
      if (strstr(symbol_table[i].attribute, "entry") != NULL) {
        fputs(symbol_table[i].symbol, file_pointer);
        fputs("      ", file_pointer);
        fputs(symbol_table[i].value, file_pointer);
        fputs("\n", file_pointer);
      }
    }
  }
  fclose(file_pointer);
}
/*
function append_extern_tofile - create and add all extern labels to file(.ext)
@param file_name  - the file name we want to create
@return void
*/
void append_extern_tofile(char * filename) {
  int i = 0;
  file_pointer = fopen(filename, "a");
  if (file_pointer == NULL) {
    printf("error creating file %s \n", filename);
    exit(0);
  }
  for (i = 0; i < index_of_datatable; i++) {
    if (strstr(data_table[i].TAG, "E") != NULL) {
      fputs(data_table[i].label_name, file_pointer);
      fputs("          ", file_pointer);
      fputs(data_table[i].Adress, file_pointer);
      fputs("\n", file_pointer);
    }
  }
  fclose(file_pointer);
}
/*
function append_datatable_tofile - create and add all datatable to file(.ob)
@param file_name  - the file name we want to create
@return void
*/
void append_datatable_tofile(char * filename, int instruct_size, int data_size) {
  int i = 0;
  append_size_to_file(filename, instruct_size, data_size);
  for (i = 0; i < index_of_datatable; i++) {
    if (strlen(data_table[i].Adress) >= 1) {
      append_command_to_file(filename, data_table[i]);
    }
  }
}
/*
function create_files - it create the output files of the program (.ob , .ext , .ent)
@param file name - the file name we want
@return void
*/
void create_files(char * filename) {
  filename[strlen(filename) - 3] = '\0';
  strcat(filename, ".ob");
  append_datatable_tofile(filename, (IC - DC - 100), DC);
  filename[strlen(filename) - 3] = '\0';
  strcat(filename, ".ext");
  append_extern_tofile(filename);
  filename[strlen(filename) - 3] = '\0';
  strcat(filename, "ent");
  append_entry_tofile(filename);
}