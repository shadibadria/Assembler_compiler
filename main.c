
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
  int extern first_pass_flag;
  int extern second_pass_flag;
  char *newfile;
  int file_flag=0;

  char filename[bufferLength];
  init_array();
  init_registers();
  init_commands();
  if (argc <= 1) {
    printf("*** Error  Missing Arguments ***\n");
    return 1;
  }

  for (i = 1; i < argc; i++) {
    if ((fp = fopen(argv[i], "r")) == NULL) {
            strcpy(filename, argv[i]);
      file_flag=1;

  newfile=(char*)malloc((sizeof(filename)+4)*sizeof(char));
  if(newfile==NULL){
    printf("ERROR cant alocate memory\n");
    exit(0);
  }
    memset(newfile, 0, strlen(filename)*sizeof(char));

  strcpy(newfile,filename);
  strcat(newfile,".as\0");
  
  
         
    }            

      strcpy(filename, argv[i]);
      if(file_flag==1){

        if(check_file(newfile)==1){
   firstpass(newfile);/*First Pass*/
          if(first_pass_flag==0){
              return 0;
          }
                      display();

            printf("DONExxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");

            secondpass(newfile);/*second Pass*/
           if(second_pass_flag==0){
             return 0;
           }
         

  append_datatable_tofile("ps.ob");        
  append_entry_tofile("ps.ent");
  append_extern_tofile("ps.ext");

       free(newfile);

        }

      }else{
          if(check_file(filename)==1){
   firstpass(argv[i]);/*First Pass*/
    
          if(first_pass_flag==0){
              return 0;
          }
            printf("DONExxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");

            secondpass(argv[i]);/*second Pass*/
           if(second_pass_flag==0){
             return 0;
           }
         

  append_entry_tofile("ps.ent");
  append_extern_tofile("ps.ext");
     append_datatable_tofile("ps.ob");        

        }
      }

    
  }
  /* fclose(fp);*/
            display();

  free_symbol_table_memory();


  return 0;
}