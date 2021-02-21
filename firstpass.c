
#include"firstpass.h"
#include"data.h"
#include "symbol_table.h"

int i = 0;
int IC = 100;
int DC = 0;
int count = 0;
FILE * filePointer;
char buffer[bufferLength];


int firstpass(char * filename) {

  filePointer = fopen(filename, "r");

  if (filePointer == NULL) {
    printf("\ncant open file \n");
    return 0;
  }

  while (fgets(buffer, bufferLength, filePointer)) {

    assemble_parsing(buffer);

  }
  printf("\n\\\\\\\\\\COUNTER: %d\n\n", count);

  return 0;
}

void assemble_parsing(char * line) {
  printf("\n******************************\n");
  printf("\n%s\n", line);
  check_if_extern(line);

  /*
  	parse_line(line);

  	printf("\n\n");*/


  

}
int check_if_extern(char * line) {
  int i = 0;

  if (strlen(line) < 7) {
    printf("ERROR \n");
    return 0;
  }
  line=remove_spaces_from_index(line,i);
  /*check if its .extern */
  if (line[i] != '.' || line[i + 1] != 'e' || line[i + 2] != 'x' || line[i + 3] != 't' || line[i + 4] != 'e' || line[i + 5] != 'r' || line[i + 6] != 'n' ||(line[i+7]!=' '&&line[i+7]!='\t')) {
    printf("Not extern : %s \n",line);
    return 0;
  }
    i = i + 7;
 line=remove_spaces_from_index(line,i);
 i=0;
 while(line[i]!='\n'&&line[i]!='\0'){
   if(line[i]==' '|| line[i]=='\t'||line[i]=='\n'){
     break;
   }
   i++;
 }
  while(line[i]!='\n'&&line[i]!='\0'){
    if(line[i]!=' '&&line[i]!='\t'&&line[i]!='\n'){
     printf("\n must be 1 parameter :%c:\n",line[i]);
  return 0;
break;
    }
    i++;
  }
  count++;
  line[strlen(line)] = '\0';
remove_space_tabs(line);
 
  printf("\next:%s\n",line);
  if (checkforduplicate(line) == 0) {
    printf("ERROR duplicate found \n");
    return 0;
  }
return 1;
}
char *remove_spaces_from_index(char * string,int i){
  
  char * newstring;
  int j = 0;
  newstring = (char * ) malloc(strlen(string) * sizeof(char));
  if (newstring == NULL) {
    printf("Something Went Wrong no memory\n");
    return "bad";
  }
  while (string[i] != '\n') {
    if (string[i] != ' ' && string[i] != '\t') {

     break;
    }
    i++;
  }
  while(string[i]!='\n'){
     newstring[j++] = string[i];
  i++;
  }
  newstring[j] = '\0';
  strcpy(string, newstring);
  free(newstring);
  return string;
}


char * remove_space_tabs(char * string) {
  char * newstring;
  int j = 0, i = 0;

  newstring = (char * ) malloc(strlen(string) * sizeof(char));
  if (newstring == NULL) {
    printf("Something Went Wrong no memory\n");
    return "bad";
  }
  while (string[i] != '\n') {
    if (string[i] != ' ' && string[i] != '\t') {
      newstring[j++] = string[i];
    }
    i++;
  }
  newstring[j] = '\0';
  strcpy(string, newstring);
  free(newstring);
  return string;
}

int parse_line(char * line) {

  int line_length = strlen(line);
  int i = 0;
  char temp[80];
  char number[10];
  int j = 0, k = 0;
  for (i = 0; i < line_length; i++) {
    if (line[i] != ' ' && line[i] != '\t' && line[i] != '\0' && line[i] != '\n') {

      if (line[i] == ';') {
        printf("comment\n");
        return 1;
      }

      if (line[i] == '.') {
        if (line[i + 1] == 'd' && line[i + 4] == 'a') {
          while (line[i] != '\n') {

            if (isdigit(line[i])) {
              /*CHECK IF VALUE IS MORE THAN 1 DIGIT AND SUM THE NUMBER*/
              number[k++] = line[i];

            }
            if (line[i] == ',' || line[i + 1] == '\n') {
              number[k] = '\0';

              printf("\n**IC = %d**\n", IC);
              printf("\nvaluex=%s\n", number);
              k = 0;

              IC++;

            }
            i++;
          }
        }
      }
      if (line[i] == '\"') {

        i++;

        while (line[i] != '\"') {
          printf("\n**ICX = %d**\n", IC);

          IC++;
          i++;

        }
        printf("\n**IC = %d**\n", IC);

        IC++;

      }
      temp[j++] = line[i];
      if (line[i] == ':') {
        temp[j - 1] = '\0';
        printf("[label]>%s\n", temp);
        /*add it to symbol table*/

        insert(IC, IC, temp, "code");

        j = 0;
      }

      if (line[i + 1] == ' ' && j != 0 && temp[0] != '.') {

        temp[j] = '\0';
        /*printf("[xcommand]>%s\n", temp);*/
        j = 0;
        printf("\n**IC = %d**\n", IC);
        IC++;

      }
      if (line[i] == ',') {
        temp[j - 1] = '\0';

        /*printf("[xarg1]>%s\n", temp);*/
        j = 0;
        printf("\n**IC = %d**\n", IC);
        IC++;

      }

    }
    if (line[i + 1] == '\n' && temp[0] != '.') {
      temp[j] = '\0';

      /*printf("[xarg2]>%s\n", temp);*/
      printf("\n**IC = %d**\n", IC);
      IC++;

    }

  }
  return 1;
}


