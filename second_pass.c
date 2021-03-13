#include "second_pass.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"firstpass.h"

#include "symbol_table.h"

#include"data_image.h"
FILE * filePointer;
char buffer[bufferLength];

int secondpass(char *filename){
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

  return 0;

}

int secondpass_pasrsing(char *line){
char temp[80];
int i=0,j=0;
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
          if(check_if_its_string(line,1)==1 ||check_if_its_data(line,1)==1 ||check_if_extern(line,1)==1){
              return 1;
            }
          if(check_if_label(temp,1)!=1)
          {

            if(check_if_its_string(line,1)==1 ||check_if_its_data(line,1)==1 ||check_if_extern(line,1)==1){
              return 1;
            }
            check_if_entry(line,1);
          }

   
j=0;
      temp[j] = '\0';

}
    }
i++;


    }
    return 1;
}

void fill_table(){

int i=0,j,number_temp;
for(i=0;i<100;i++){

if(strcmp(arr[i].opcode,"?")==0){

  for(j=0;j<100;j++){

    if(strstr(arr[i].label_name,array[j].symbol)){
                    printf("table[%s] , symboltable[%s]\n",arr[i].label_name,array[j].symbol);
                    number_temp = strtol(array[j].value, NULL, 10);
                    printf("NUMBER:%d\n",number_temp);
            sprintf(arr[i].opcode,"%X",number_temp);
        printf("value[%s]\n",array[i].value);
        break;
    }
  }
}

}
}