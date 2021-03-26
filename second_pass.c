/*
* File Name : second_pass.c
* This file provide all the parsing functions of second pass .
* Author : Shadi Badria <shadibadria@gmail.com>
*/

#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

#include"firstpass.h"
#include "second_pass.h"
#include "symbol_table.h"
#include"data_image.h"
#include"file_proccess.h"

FILE * filePointer;
char buffer[bufferLength];
int extern symbol_table_size;
int second_pass_flag = 1;
int extern index_of_datatable;
/*
function secondpass -  it take the file name and start to read it line by line
and send it to parsing
@param filename  - file name of the assembler file
@return int
*/
int secondpass(char * filename) {
  second_pass_flag=1;
  filePointer = fopen(filename, "r");
  if (filePointer == NULL) {
    printf("***ERROR cant open file named %s ***\n", filename);
    exit(0);
  }
  while (fgets(buffer, bufferLength, filePointer)) {
    secondpass_pasrsing(buffer); /*parse line by line*/
  }
  fill_table(); /*fill table where the adress is not found*/
  check_for_label_error();
  fclose(filePointer);
  return 0;
}
/*
function secondpass_pasrsing - takes lline and parse it to write the missing labels at the data table 
@param line - file line
@return int
*/
int secondpass_pasrsing(char * line) {
  char temp[MAX_LINE];
  int i = 0, j = 0;
  if (line[0] == '\n' || line[0] == '\0') {
    return 0;
  }
  while (line[i] != '\0' && line[i] != '\n') {
    if (line[i] != ' ' && line[i] != '\t') {
      if (line[i] == ';') {
        /*if comment found*/
        return 0;
      }
      temp[j++] = line[i];
    } else {
      temp[j] = '\0';
      if (j != 0) {
        if (check_if_its_string(line, 1) == 1 || check_if_its_data(line, 1) == 1 || check_if_extern(line, 1) == 1) {
          return 1;
        }
        if (check_if_label(temp, 1) != 1) {
          check_if_entry(line, 1);
        }
        j = 0;
        temp[j] = '\0';
      }
    }
    i++;
  } /*while end*/
  return 1;
}
/*
function fill_table -  fill the data table where is labels are missing
@param none
@return void
*/
void fill_table() {
  int i = 0, j, number_temp, k = 0, flag = 0, current_adress = 0;
  char tempstring[MAX_LINE];
  for (i = 0; i < index_of_datatable; i++) {
    if (strcmp(data_table[i].opcode, "?") == 0) {
      /*if unknown value at symbol table*/
      for (j = 0; j < symbol_table_size; j++) {
        flag = 0;
        if (data_table[i].label_name[0] == '%') {
          /*if value is adress*/
          memmove(tempstring, data_table[i].label_name + 1, strlen(data_table[i].label_name));
          k = 0;
          while (k < strlen(tempstring)) {
            if (isdigit(tempstring[k])) {
              tempstring[k] = '\0';
              break;
            }
            k++;
          }
          flag = 1;
        }
        if (flag == 1 && strcmp(symbol_table[j].symbol, tempstring) == 0) {
          /*if symbol is the same add it*/
          number_temp = strtol(symbol_table[j].value, NULL, 10);
          current_adress = strtol(data_table[i].Adress, NULL, 10);
          sprintf(data_table[i].opcode, "%03X", number_temp - current_adress);

          if (number_temp - current_adress < 0) {
            memmove(data_table[i].opcode, data_table[i].opcode + 5, strlen(data_table[i].opcode));
          }
          strcpy(data_table[i].TAG, "A");
          break;
        }

        if (strcmp(data_table[i].label_name, symbol_table[j].symbol) == 0) {
          number_temp = strtol(symbol_table[j].value, NULL, 10);
          sprintf(data_table[i].opcode, "%03X", number_temp);
                     sprintf(data_table[i].funct, "%s", "\0");


          if (strcmp(symbol_table[j].attribute, "external") == 0) {
            /*if external*/
            strcpy(data_table[i].TAG, "E");
            break;
          } else {
            
            if (strstr(symbol_table[j].attribute, "entry")) {
             
              strcpy(data_table[i].TAG, "R");
              break;
            } else {
              strcpy(data_table[i].TAG, "R");
            }
          }

        }
      }
    }

  }
}
/*
function check_for_label_error - check if there is error in labels
@params none
@return void
*/
void check_for_label_error() {
  int i = 0;

  for (i = 0; i < index_of_datatable; i++) {
    if (strcmp(data_table[i].opcode, "?") == 0) {
      printf("*** Second Pass ERROR label %s is not found in symbol table *** \n", data_table[i].label_name);
      second_pass_flag = 0;
      break;
    }
  }
}