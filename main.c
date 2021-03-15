
/*
file name : main function
explain: this file has the main function that control all the program
the main function call the firstpass function and then the second pass function 
then it create files 
*/
#include<stdio.h>

#include<string.h>

#include"firstpass.h"

#include"second_pass.h"

#include"file_proccess.h"

#include"symbol_table.h"

#include"data.h"

#include"data_image.h"

/*
Main function 
role:
call for first pass 
call for second pass
open/close file
*/
int main(int argc, char * argv[]) {

  int i = 0;
  FILE * fp;
  char filename[bufferLength];
  init_array();
  init_registers();
  init_commands();
  if (argc <= 1) {
    printf("\n**Error : Missing Arguments \n\n");
    return 1;
  }

  for (i = 1; i < argc; i++) {
    if ((fp = fopen(argv[i], "r")) == NULL) {
      printf("\nError :  could not open file named %s\n\n", argv[i]);

    } else {
      strcpy(filename, argv[i]);

      if (check_file(filename)) {

        firstpass(argv[i]);/*First Pass*/
         display();
                 printf("DONExxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");

                          secondpass(argv[i]);/*second Pass*/
    for (i = 0; i < 100; i++) {
          if (strlen(arr[i].Adress) >= 1) {        
            append_command_to_file("ps.ob", arr[i]);           
          }

        }
     

      }

      fclose(fp);
    }
  }
            display();

  free_symbol_table_memory();


  return 0;
}