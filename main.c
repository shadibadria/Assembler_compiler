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

  /*init the data */
  init_symbol_table();
  init_registers();
  init_command_database();
          init_data_table();

  /*check arguments counter */
  if (argc <= 1) {
    printf("*** Error  Missing Arguments ***\n");
    return 1;
  }
  /*loop files */
  for (i = 1; i < argc; i++) {
     newfile = (char * ) malloc((strlen(argv[i]) + 5) * sizeof(char));
      if (newfile == NULL) {
        printf("ERROR cant alocate memory\n");
        exit(0);
      }
      memset(newfile, 0, (strlen(argv[i]) + 5) * sizeof(char));
   strcpy(newfile, argv[i]);

    if ((fp = fopen(argv[i], "r")) == NULL) {
      /*if file not found*/
      file_flag = 1;
      strcat(newfile, ".as\0");
    }

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
     

        create_files(newfile);
      }

    } else {
      /*file has .as ending*/
      if (check_file(newfile) == 1) {
        firstpass(newfile); /*First Pass*/
        if (first_pass_flag == 0) {
          return 1;
        }
        secondpass(newfile); /*second Pass*/
        if (second_pass_flag == 0) {
          return 1;
        }
            create_files(newfile);

        
      }
        fclose(fp);

    }
      free_symbol_table_memory(); /*free the symbol table*/
        free(newfile);
          init_symbol_table();
          free_data_table();
          init_data_table();
          fflush(stdout);
      
  } /*end loop*/
  return 0;
}