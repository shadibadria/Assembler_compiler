#include<stdio.h>

#include<string.h>

#include"firstpass.h"

#include"file_proccess.h"


#include"symbol_table.h"

#include"data.h"


#include"data_image.h"

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
        firstpass(argv[i]);
    for(i=0;i<100;i++){
        if(strlen(arr[i].Adress)>=1){
    append_command_to_file("ps.ob",arr[i]);
    close_file();

        }
    }
      }

      fclose(fp);
    }
  }
  display();

  return 0;
}
