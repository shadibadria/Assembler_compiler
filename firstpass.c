
#include"firstpass.h"
#include"data.h"
#include "symbol_table.h"


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
  

  return 0;
}

int assemble_parsing(char * line) {

 line=remove_spaces_from_index(line,0);

    if(line[0]=='\n'||line[0]=='\0'){
      return 0;
    } 
  printf("\n******************************\n");
  printf("\nCommand : %s\n", line);

    	parse_line(line);
return 1;

}
int parse_line(char * line) {

  int i=0;

    line[strlen(line)] = '\0';
     if (line[i] == ';') {
        printf("comment\n");
        return 1;
      }


    check_if_extern(line);
    check_if_entry(line);
    check_if_label(line);
check_if_its_data(line);
 check_if_its_string(line);
  return 1;
}

int check_if_extern(char * line) {
  int i = 0;

  line[strlen(line)]='\n';
  if (strlen(line) < 7) {
    printf("ERROR \n");
    return 0;
  }


  /*check if its .extern */
  if (line[i] != '.' || line[i + 1] != 'e' || line[i + 2] != 'x' || line[i + 3] != 't' || line[i + 4] != 'e' || line[i + 5] != 'r' || line[i + 6] != 'n' ||(line[i+7]!=' '&&line[i+7]!='\t')) {
    return 0;
  }

    i = i + 7;
 line=remove_spaces_from_index(line,i);
 i=0;
 while(line[i]!='\n'&&line[i]!='\0'){
   if(line[i]==' '|| line[i]=='\t'||line[i]=='\n'){
     break;
   }
   else if(!isalpha(line[i])){
  printf("paramerter wrong\n");
    return 0;
   }
   i++;
 }
  while(line[i]!='\n'&&line[i]!='\0'){
    if(line[i]!=' '&&line[i]!='\t'&&line[i]!='\n'&&isalpha(line[i])){
     printf("\n extern : must be 1 parameter :%c:\n",line[i]);
  return 0;
break;
    }
    i++;
  }
  count++;
  line[strlen(line)] = '\0';
remove_space_tabs(line);
 
  if (checkforduplicate(line) == 0) {
    printf("ERROR duplicate found \n");
    return 0;
  }
  printf("\n\nits extern !!!\n");

return 1;
}
/*check if entry statment*/
int check_if_entry(char * line) {
  int i = 0;

  line[strlen(line)]='\n';
  if (strlen(line) < 7) {
    printf("ERROR \n");
    return 0;
  }
  line=remove_spaces_from_index(line,i);
  /*check if its .extern */
  if (line[i] != '.' || line[i + 1] != 'e' || line[i + 2] != 'n' || line[i + 3] != 't' || line[i + 4] != 'r' || line[i + 5] != 'y'  ||(line[i+6]!=' '&&line[i+6]!='\t')) {
    return 0;
  }

    i = i + 6;
 line=remove_spaces_from_index(line,i);
 i=0;
 while(line[i]!='\n'&&line[i]!='\0'){
   if(line[i]==' '|| line[i]=='\t'||line[i]=='\n'){
     break;
   }
   i++;
 }
while(line[i]!='\n'&&line[i]!='\0'){
    if(line[i]!=' '&&line[i]!='\t'&&line[i]!='\n'&&isalpha(line[i])){
     printf("\n entry : must be 1 parameter :%c:\n",line[i]);
  return 0;
break;
    }
    i++;
  }
  count++;
remove_space_tabs(line);
 
  if (checkforduplicate(line) == 0) {
    printf("ERROR duplicate found \n");
    return 0;
  }
    printf("\n\nits entry !!!\n");

return 1;
}

char *remove_spaces_from_index(char * string,int i){
  
  char * newstring;
  int j = 0;
  if(string[i]!='\t'&&string[i]!=' '&&string[i]=='\n'){
    return 0;
  }
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


int check_if_label(char * line){
int i=0,j=0;
char temp[80];
while(line[i]!='\n'&&line[i]!='\0'){
  temp[j++]=line[i];
  if(line[i]==':'){
    temp[i]='\n';

    printf("label:%s\n",remove_space_tabs(temp));
    return 0;
  }
i++;
}

return 0;
}
int check_if_its_data(char *line){
  int i=0;

  while(line[i]!='\n'&&line[i]!='\0'){

  if(line[i]=='.'){

    if(line[i+1]=='d'&&line[i+2]=='a'&&line[i+3]=='t'&&line[i+4]=='a'){
      printf("its data\n");
      return 0;
    }
  }
  i++;
  }
return 1;

}
int check_if_its_string(char *line){
  int i=0;

  while(line[i]!='\n'&&line[i]!='\0'){

  if(line[i]=='.'){

    if(line[i+1]=='s'&&line[i+2]=='t'&&line[i+3]=='r'&&line[i+4]=='i'&&line[i+5]=='n'&&line[i+6]=='g'){
      printf("its string\n");
      return 0;
    }
  }
  i++;
  }
return 1;

}