
/*
file name: file_proccess.c 
explain: this file has all function of file creating /writing/creating files 
*/
#include "file_proccess.h"
#include "symbol_table.h"
#include "data_image.h"
FILE * file_pointer;
int extern size_table;




/*
function :
check file if it ends with .as
*/
int check_file(char * file_name) {


  char * file_ending = strrchr(file_name, '.');
  /**/

    printf("filename:%s\n",file_name);
  if (file_ending == NULL) {

    printf("\n*** ERROR : File Does Not Have *.as Extention.. ***\n\n");
    return 0;
  }

  if ((!strcmp(file_ending + 1, "as"))) {
    /*if file does end with .as*/

    return 1;
  } else {
   
    return 0;
  }

}
void append_entry_tofile(char * filename) {
  int i=0;


  file_pointer = fopen(filename, "a");

  if (file_pointer == NULL) {
    printf("error creating file %s \n", filename);
    exit(0);
  }

    if(array[i].attribute!=NULL){
      
    
    for(i=0;i<size_table;i++){
        if(strstr(array[i].attribute,"entry")!=NULL){
      fputs(array[i].symbol, file_pointer);
      fputs("      ", file_pointer);
       fputs(array[i].value, file_pointer);

  fputs("\n", file_pointer);

        }
    }
    }
fclose(file_pointer);
}
/*create and add extern labels to file*/
void append_extern_tofile(char * filename) {
  int i = 0;
  file_pointer = fopen(filename, "a");
  if (file_pointer == NULL) {
    printf("error creating file %s \n", filename);
    exit(0);
  }

  for (i = 0; i < MAX_Data; i++) {
    if (strstr(arr[i].TAG, "E") != NULL) {
      fputs(arr[i].label_name, file_pointer);
      fputs("          ", file_pointer);
      fputs(arr[i].Adress, file_pointer);
      fputs("\n", file_pointer);
    }
  }
  fclose(file_pointer);

}
void append_datatable_tofile(char *filename){
int i=0;
for (i = 0; i < 100; i++) {
          if (strlen(arr[i].Adress) >= 1) {        
            append_command_to_file("ps.ob", arr[i]);           
          }
        }

}
  