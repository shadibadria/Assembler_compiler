/*
filename: second_pass.c

second iteration of the assembly program
its porpuse is to rewrite  all the unknown labels and data to the data table 


*/
#include "second_pass.h"

#include<stdio.h>

#include<string.h>

#include<stdlib.h>

#include"firstpass.h"

#include "symbol_table.h"

#include"data_image.h"

FILE * filePointer;
char buffer[bufferLength];
int extern size_table;
int second_pass_flag = 1;
/*
function secondpass -  it take the file name and start to read it line by line
and send it to parsing
@param filename  - file name of the assembler file
@return int
*/
int secondpass(char * filename) {
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
  char temp[80];
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
  char tempstring[15];
  for (i = 0; i < 100; i++) {
    if (strcmp(arr[i].opcode, "?") == 0) {
      /*if unknown value at symbol table*/
      for (j = 0; j < size_table; j++) {
        flag = 0;
        if (arr[i].label_name[0] == '%') {
          /*if value is adress*/
          memmove(tempstring, arr[i].label_name + 1, strlen(arr[i].label_name));
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
        if (flag == 1 && strcmp(array[j].symbol, tempstring) == 0) {
          /*if symbol is the same add it*/
          number_temp = strtol(array[j].value, NULL, 10);
          current_adress = strtol(arr[i].Adress, NULL, 10);
          sprintf(arr[i].opcode, "%03X", number_temp - current_adress);
          if (number_temp - current_adress < 0) {
            memmove(arr[i].opcode, arr[i].opcode + 5, strlen(arr[i].opcode));
          }
          strcpy(arr[i].TAG, "A");
          break;
        }
        printf("arr=%s\n", arr[i].label_name);
        if (strcmp(arr[i].label_name, array[j].symbol) == 0) {
          number_temp = strtol(array[j].value, NULL, 10);
          sprintf(arr[i].opcode, "%03X", number_temp);
          if (strcmp(array[j].attribute, "external") == 0) {
            /*if external*/
            strcpy(arr[i].TAG, "E");
            break;
          } else {
            if (strstr(array[j].attribute, "entry")) {
              strcpy(arr[i].TAG, "R");
              break;
            } else {
              strcpy(arr[i].TAG, "R");
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
  for (i = 0; i < 100; i++) {
    if (strcmp(arr[i].opcode, "?") == 0) {
      printf("ERROR LABEL %s is not found in symbol table \n", arr[i].label_name);
      second_pass_flag = 0;
      break;
    }
  }
}