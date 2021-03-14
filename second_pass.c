#include "second_pass.h"

#include<stdio.h>

#include<string.h>

#include<stdlib.h>

#include"firstpass.h"

#include "symbol_table.h"

#include"data_image.h"

FILE * filePointer;
char buffer[bufferLength];

int secondpass(char * filename) {
  filePointer = fopen(filename, "r");
  if (filePointer == NULL) {
    printf("\ncant open file \n");
    return 0;
  }
  while (fgets(buffer, bufferLength, filePointer)) {

    secondpass_pasrsing(buffer);
  }
  fill_table();

  fclose(filePointer);
  append_entry_tofile("ps.ent");
  append_extern_tofile("ps.ext");

  return 0;

}

int secondpass_pasrsing(char * line) {
  char temp[80];
  int i = 0, j = 0;
  if (line[0] == '\n' || line[0] == '\0') {
    return 0;
  }

  while (line[i] != '\0' && line[i] != '\n') {
    if (line[i] != ' ' && line[i] != '\t') {

      if (line[i] == ';') {
        printf("comment\n");
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

          if (check_if_its_string(line, 1) == 1 || check_if_its_data(line, 1) == 1 || check_if_extern(line, 1) == 1) {
            return 1;
          }
          check_if_entry(line, 1);
        }

        j = 0;
        temp[j] = '\0';

      }
    }
    i++;

  }
  return 1;
}

void fill_table() {

  int i = 0, j, number_temp, k = 0, flag = 0, current_adress = 0;
  char tempstring[15];
  for (i = 0; i < 100; i++) {

    if (strcmp(arr[i].opcode, "?") == 0) {

      for (j = 0; j < 100; j++) {
        flag = 0;

        if (arr[i].label_name[0] == '%') {
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
          printf("is:%s\n", tempstring);
        }
        if (flag == 1 && strcmp(array[j].symbol, tempstring) == 0) {

          number_temp = strtol(array[j].value, NULL, 10);
          current_adress = strtol(arr[i].Adress, NULL, 10);

          printf("befVAL:%d\n", number_temp);
          printf("currnet-Adress=%d\n", number_temp - current_adress);

          sprintf(arr[i].opcode, "%03X", number_temp - current_adress);
          if (number_temp - current_adress < 0) {
            memmove(arr[i].opcode, arr[i].opcode + 5, strlen(arr[i].opcode));

          }
          strcpy(arr[i].TAG, "A");

          printf("VAL:%s\n", arr[i].opcode);
          break;

        }
        if (strcmp(arr[i].label_name, array[j].symbol) == 0) {
          number_temp = strtol(array[j].value, NULL, 10);
          sprintf(arr[i].opcode, "%03X", number_temp);

          if (strcmp(array[j].attribute, "external") == 0) {

            strcpy(arr[i].TAG, "E");
            printf("extern:%s\n", array[j].value);
            break;
          } else {
            if (strstr(array[j].attribute, "entry")) {
              strcpy(arr[i].TAG, "R");
              printf("entry:%s\n", array[j].value);
              break;

            } else {
              if (strcmp(array[j].attribute, "code") == 0 || strcmp(array[j].attribute, "data") == 0) {

                strcpy(arr[i].TAG, "R");
                break;
              }

            }
          }

        }
      }
    }

  }
}
