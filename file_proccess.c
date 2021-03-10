#include "file_proccess.h"

/*
function :
check file if it ends with .as
*/
int check_file(char * file_name) {

  char * file_ending = strrchr(file_name, '.');
  /**/

  if (file_ending == NULL) {

    printf("\n*** ERROR : File Does Not Have *.as Extention.. ***\n\n");
    return 0;
  }
  if ((!strcmp(file_ending + 1, "as"))) {
    /*if file does end with .c*/

    return 1;
  } else {
    printf("\n\n*** ERROR : File Does Not Have *.as Extention.. ***\n\n");
    return 0;
  }

}