/*
* File Name : main.c
* This file is the controler for all the program  .
* Author : Shadi Badria <shadibadria@gmail.com>
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"firstpass.h"
#include"second_pass.h"
#include"file_proccess.h"
#include"symbol_table.h"
#include"data.h"
#include"data_image.h"

/*
function main is the controller of the program
@param argc - count of arguments
@param argv - array of argumnets name
*/
  FILE * fp;

int main(int argc, char * argv[]) {

  int i = 0;
  int extern first_pass_flag;
  int extern second_pass_flag;
  char * newfile;
  int file_flag = 0;
  char filename[bufferLength];

  /*init the data */
  init_array();
  init_registers();
  init_command_database();

  /*check arguments counter */
  if (argc <= 1) {
    printf("*** Error  Missing Arguments ***\n");
    return 1;
  }
  /*loop files */
  for (i = 1; i < argc; i++) {
    if ((fp = fopen(argv[i], "r")) == NULL) {
      /*if file not found*/
      strcpy(filename, argv[i]);
      file_flag = 1;
      newfile = (char * ) malloc((strlen(filename) + 4) * sizeof(char));
      if (newfile == NULL) {
        printf("ERROR cant alocate memory\n");
        exit(0);
      }
      memset(newfile, 0, (strlen(filename) + 4) * sizeof(char));
      strcpy(newfile, filename);
      strcat(newfile, ".as\0");
    }
    strcpy(filename, argv[i]);
    if (file_flag == 1) {
      /*if file does not habe .as ending*/
      if (check_file(newfile) == 1) {
        firstpass(newfile); /*First Pass*/
        if (first_pass_flag == 0) {
          return 1;
        }

        secondpass(newfile); /*second Pass*/
        if (second_pass_flag == 0) {
          return 1;
        }
        /*create files*/
        append_datatable_tofile("ps.ob");
        append_entry_tofile("ps.ent");
        append_extern_tofile("ps.ext");
        free(newfile);
      }

    } else {
      /*file has .as ending*/
      if (check_file(filename) == 1) {
        firstpass(argv[i]); /*First Pass*/
        if (first_pass_flag == 0) {
          return 1;
        }
        secondpass(argv[i]); /*second Pass*/
        if (second_pass_flag == 0) {
          return 1;
        }
     append_datatable_tofile("ps.ob");
       append_entry_tofile("ps.ent");
        append_extern_tofile("ps.ext");
        
      }
        fclose(fp);

    }
  } /*end loop*/
  free_symbol_table_memory(); /*free the symbol table*/
  return 0;
}