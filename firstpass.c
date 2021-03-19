
/*
file name: firstpass.c
explain: this file has all functions of firstpass of the compiler

first iteration of the assembly program
its porpuse is to add all the labels and data to the symbol table 
and to the RAM

*/
#include"firstpass.h"

#include"data.h"

#include "symbol_table.h"

#include"data_image.h"



int IC = 100;
int DC = 0;
int count = 0;
int program_line=1;/*to count program lines*/
FILE * filePointer;
char buffer[bufferLength];
int extern index_of_datatable;
int label_flag = 0;
int arguments_counter=0;
/*
param: filename of the assembly 
functionality: function take file name and scan it and sent line to parsing
*/
int firstpass(char * filename) {
  filePointer = fopen(filename, "r");
  if (filePointer == NULL) {
    printf("*** ERROR: Cant open file name :%s ***\n",filename);
    exit(0);
  }
  while (fgets(buffer, bufferLength, filePointer)) {
    if(strlen(buffer)>MAX_LINE){
      printf("*** ERROR File is to big must contain max 4095 \n ***");
        exit(0);
    }
    else{
      if(IC>bufferLength){
         printf("*** ERROR at line %d line is  to long, max length is  80 \n ***",program_line);
        return 0;
      }
    }
    
    assemble_parsing(buffer);/*send the line to parsing */
   
  }   
  fclose(filePointer);
  return 0;
}

/*
param: gets line from file
functionality: send the line to function parse_line after removing spaces and tabs
at the beginning , and checks if line empty or EOF
*/
int assemble_parsing(char * line) {
  if (line[0] == '\n' || line[0] == '\0') {/*if line is empty */
    return 0;
  }
  printf("\n******************************\n");
  printf("\nCommand :%s\n", line);
  label_flag = 0;
  check_line_arguments(line);/*check if arguments for error*/
 parse_line(line);/*send line to proccess it */
    program_line++;/*count line*/
  
  return 1;
}
/*
param: line from file
functionality: parse the line to data we needby calling functions
*/
int parse_line(char * line) {
  int i = 0, j = 0;
  char temp[500];
 /*if line is comment*/
  if (line[i] == ';') {
   
    return 1;
  }
   if (check_if_extern(line,0) == 1) {
    return 0;
  }
 if (check_if_entry(line,0) == 1) {
    return 0;
  }
  
  /*if line is label*/
   if (check_if_label(line,0) == 1) {
          label_flag = 1;
        }
      /*get word by word*/
  while (line[i] != '\0' && line[i] != '\n') {
    if (line[i] != ' ' && line[i] != '\t') {
   
      temp[j++] = line[i];
    } else {

      temp[j] = '\0';
      if (j != 0) {

            /*check for command*/
         check_if_command(temp,line,label_flag);
        
          /*check if line is data or string and check comma (',') correction*/
        if (check_if_its_data(line,0) != 1&&check_if_its_string(line,0) != 1) {
          
          check_comma(line);
        }else{
                    return 0;
        }
      
      }
      j = 0;
      temp[j] = '\0';
    }

    i++;
  } /*end while*/

    /*check if its end of line and then check the word if its string/data/command*/
  if (line[i] == '\n' || line[i] == '\0') {
    temp[j] = '\0';
    if (strlen(temp)) {
      if(check_if_its_data(temp,0)!=1||check_if_its_string(temp,0))
      if (check_if_command(temp,line,label_flag) == 0)
        check_line(temp);
    }
  }
  return 1;
}
/*
check if line comma's are correct 
*/
void check_comma(char *line){
int i=0,counter=0;
while(line[i]!='\0'){
if(line[i]==',') counter++;
  i++;
}
if(counter>1){
 printf("*** ERROR at line %d to many comma's ***\n",program_line);

}
}

/*
param: line from file
functionality: check if the line is .extern 
*/

int check_if_extern(char * line,int test) {
  int i = 0;
  remove_spaces_from_index(line,0);
   
  /*check if its .extern */
  if (line[i] != '.' || line[i + 1] != 'e' || line[i + 2] != 'x' || line[i + 3] != 't' || line[i + 4] != 'e' || line[i + 5] != 'r' || line[i + 6] != 'n' || (line[i + 7] != ' ' && line[i + 7] != '\t')) {
    return 0;
  }
  if(test==1){/*if we just want to know its extern*/
    return 1;
  }
 
  i = i + 7;
  line = remove_spaces_from_index(line, i);
  i = 0;

  count++;
  line[strlen(line)] = '\0';
  remove_space_tabs(line);
if (checkforduplicate(line) == 0) {
    printf("*** ERROR at line %d the Label %s is already in use *** \n",program_line,line);
    return 0;
  }
  /*insert external label*/
   insert(DC++,0, line,"external");
  printf("\n\nits extern !!!\n");
  return 1;
}

/*
param: line from file
functionality: check if its entry line
*/
int check_if_entry(char * line,int test) {
  int i = 0;
  line[strlen(line)] = '\n';

  line = remove_spaces_from_index(line, i);
  /*check if its .entry */
  if (line[i] != '.' || line[i + 1] != 'e' || line[i + 2] != 'n' || line[i + 3] != 't' || line[i + 4] != 'r' || line[i + 5] != 'y' || (line[i + 6] != ' ' && line[i + 6] != '\t')) {
    return 0;
  }
  i = i + 6;
  line = remove_spaces_from_index(line, i);
  i = 0;
  while (line[i] != '\n' && line[i] != '\0') {
    if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n') {
      break;
    }
    i++;
  }
  while (line[i] != '\n' && line[i] != '\0') {
    if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && isalpha(line[i])) {
      printf("\n entry : must be 1 parameter :%c:\n", line[i]);
      return 0;
      break;
    }
    i++;
  }
  count++;
  remove_space_tabs(line);
  if(test==0){/*if test exit and if its pass1*/
    return 1;
  }
  /*check for label duplicate and insert*/
   if (checkforduplicate(line) == 0) {
        insert_entry(line);
  } else {
 printf("*** ERROR at line %d entry label %s is  not found on symbol table \n",program_line,line);/*second pass error*/
    return 0;
  }
  printf("\n\nits entry !!!\n");
  return 1;
}
/*
param: line from file and index of line
functionality: remove space/tab from index till first non tab/space
*/
char * remove_spaces_from_index(char * string, int i) {
  char * newstring;
  int j = 0;
  if (string[i]!='\0'&&string[i] != '\t' && string[i] != ' ' && string[i] == '\n' && isspace(string[i])) {
    return 0;
  }
  newstring = (char * ) malloc(strlen(string) * sizeof(char));
  if (newstring == NULL) {
    printf("*** ERROR  Something Went Wrong no memory ***\n");
    exit(0);
  }

  while (string[i] != '\n' && string[i] != '\0') {/*find first appering of word*/
    if (string[i] != ' ' && string[i] != '\t' && !isspace(string[i])) {
      break;
    }
    i++;
  }
  /*add values to string*/
  while (string[i] != '\n' && string[i] != '\0') {
    newstring[j++] = string[i];
    i++;
  }
  newstring[j] = '\0';
  strcpy(string, newstring);
  free(newstring);
  return string;
}
/*
param: line from file
functionality: remove all space/tabs from line/string
*/
char * remove_space_tabs(char * string) {
  char * newstring;
  int j = 0, i = 0;
  int string_len=(strlen(string)+1);
  newstring = (char * )malloc( string_len * sizeof(char));
  if (newstring == NULL) {
    printf("*** ERROR Something Went Wrong no memory ***\n");
    exit(0);
  }
  /*create new string without spaces/tabs*/
  while (string[i] != '\n' && string[i] != '\0') {
    if (string[i] != ' ' && string[i] != '\t') {
      newstring[j++] = string[i];
    }
    i++;
  }
  newstring[j] = '\0';
  if(strlen(newstring)<=1){
    free(newstring);
    return 0;
  }
  strcpy(string, newstring);
  free(newstring);
  return string;
}

/*
param: line from file
functionality: check if its label
*/
int check_if_label(char * line,int test) {
  int i = 0, j = 0;
  char *temp;
   temp = (char * ) malloc((strlen(line)+1) * sizeof(char));
  if (temp == NULL) {
    printf("*** ERROR Something Went Wrong no memory ***\n");
    exit(0);
  }
  /*search for end of the label char ':' */
  while (line[i] != '\n' && line[i] != '\0') {
      temp[j++] = line[i];
    if (line[i] == ':') {
          temp[j] = '\n';
          j=0;

          while(temp[j]!=':'){
           if(temp[j]==' '||temp[j]=='\t'){/*check if label has spaces/tabs in it*/
            printf("*** ERROR at line: %d: Label has space/tab in it ***\n",program_line);
            break;
          }
          j++;
          }

        if(isdigit(temp[0])){/*check if label start with letters*/
            printf("*** ERROR at line: %d: label must start with letters *** \n",program_line); 
        }
        if(strlen(temp)>MAX_LABEL){
                      printf("\n*** ERROR at line %d: label is to long must be 31 char ***\n",program_line);          
        }
          while(temp[j]!=':'){
            j++;
          }
                             printf("LINExx:%s\n",temp);


      if(test==1){/*if only testing if its label*/
        free(temp);
        return 1;
      }
      remove_space_tabs(temp);
        if(temp[j-1]==':'){/*remove the ':' if exsist*/
          temp[j-1]='\0';
        }
        if(checkforduplicate(remove_space_tabs(temp))==0){/*check for duplicate of the label*/
          printf("*** ERROR at line %d \"%s\" has already exsisted ***\n",program_line,temp);
        }
        printf("label:%s\n", remove_space_tabs(temp));
      if(temp[i]==','){
          free(temp);
        return 0;
      }
      /*insert label with info*/
      if(check_if_its_data(line,1)==1){
      insert(DC++, IC, remove_space_tabs(temp), "data");
      }else
      if(check_if_its_string(line,1)==1)
      {
      insert(DC++, IC, remove_space_tabs(temp), "data");
      }else{
        insert(DC++, IC, remove_space_tabs(temp), "code");
      }
  free(temp);
      return 1;
    }
    i++;
  }
    free(temp);

  return 0;
}
/*
param: line from file
functionality: check if its data
*/
int check_if_its_data(char * line,int test) {

  int i = 0;
  /*check if its data*/
  printf("HERE\n");
  while (line[i] != '\n' && line[i] != '\0') {
    if (line[i] == '.') {
      if (line[i + 1] == 'd' && line[i + 2] == 'a' && line[i + 3] == 't' && line[i + 4] == 'a') {
        if(test==0){/*if its not testing only*/
                  printf("xits data :%s\n",line);

        data_parsing(line,i+4);/*parse the data to numbers*/
        return 1;
        }
        
        printf("its data\n");
        return 1;
      }
    }
    i++;
  }
  return 0;
}
/*
param: data line
functionality: get data input to array
*/
int data_parsing(char * line,int i) {
  char * p = line;
  int val,comma_counter=0,number_counter=0,number_flag=0;
    p+=i;
  line[strlen(line)] = '\0';
  /*check data if correct*/
  while(*p){
    if(*p==','){
      if(number_flag==0){
            printf("*** ERROR at line %d to many comma's inserted missing numbers ***\n",program_line);
      }
      number_flag=0;
      comma_counter++;
    }else{
           if (isdigit( * p) || (( * p == '-' || * p == '+') && isdigit( * (p + 1)))) {
             number_flag=1;
           }else{
            
           }

    }
    p++;
  }
  p=line;
  p+=i;
  /*insert data*/
  while ( * p) {

    if (isdigit( * p) || (( * p == '-' || * p == '+') && isdigit( * (p + 1)))) {
      number_counter++;

      val = strtol(p, & p, 10);
      if(val>MAX_DATA){
        printf("*** ERROR at line %d data value is bigger than %d *** \n",program_line,MAX_DATA);
      }

      if(val<MIN_DATA){
        printf("*** ERROR at line %d data value is smaller than %d *** \n",program_line,MIN_DATA);
      }
          
      /*insert data values */
      sprintf(arr[index_of_datatable].Adress, "%04d", IC);
      sprintf(arr[index_of_datatable].opcode, "%03X", val);
      sprintf(arr[index_of_datatable].TAG, "%c", 'A');
      if (val < 0) {
        arr[index_of_datatable].opcode[0] = '\0';
        arr[index_of_datatable].funct[4] = '\0';
      }
      index_of_datatable++;
      IC++;
    } else {
      p++;
    }
  }
  
return 1;
}


/*
param: string  line
functionality: get data input to array
*/
int  string_parsing(char * line, int index) {
  int ascii = 0,string_flag=0,j=0;
  int string_starting_flag=0;
  
  while (line[index] != '\n' && line[index] != '\0') {
    
    if (line[index] == '"') {
      string_starting_flag++;
      break;
    }
    if(line[index]!=' '&&line[index]!='\t'){
      printf("*** ERROR at line %d  string formating wrong ***\n",program_line);
    }
    index++;
  }
  index++;
  j=index;
  while (line[j] != '"' && line[j] != '\n' && line[j] != '\0') {
 j++;
  }
   if(line[j]=='\"'){
      string_starting_flag++;
  }
  if(string_starting_flag!=2){
    printf("*** ERROR at line %d string must start with \" and end with \" ***\n",program_line);
  }
  j++;
  while(line[j]!='\0'){
    if(line[j]!=' '&&line[j]!='\t'){
      printf("*** ERROR at line %d string has char %c after end ***\n",program_line,line[j]);
    }
    j++;
  }
  /*insert string to table by ascii code*/
  while (line[index] != '"' && line[index] != '\n' && line[index] != '\0') {
    string_flag=1;
    sprintf(arr[index_of_datatable].Adress, "%04d", IC);
    ascii = (int) line[index];
    printf("ascii:%d\n", ascii);
    sprintf(arr[index_of_datatable].opcode, "%X", 0);
    sprintf(arr[index_of_datatable].funct, "%X", ascii);
    sprintf(arr[index_of_datatable].TAG, "%c", 'A');
    index_of_datatable++;
    printf("str_IC      : %d\n", IC);
    IC++;
    index++;
  }
  if(string_flag==0){
    printf("*** ERROR at line %d  string has no values ***\n",program_line);
  }
  sprintf(arr[index_of_datatable].Adress, "%04d", IC);
  ascii = 0;
  sprintf(arr[index_of_datatable].opcode, "%03X", ascii);
  sprintf(arr[index_of_datatable].TAG, "%c", 'A');
  index_of_datatable++;
  printf("str_IC : %d\n", IC);
  IC++;
return 1;
}
/*
param: line from file
functionality: check if its string
*/
int check_if_its_string(char * line,int test) {
  int i = 0;

  while (line[i] != '\n' && line[i] != '\0') {
    if (line[i] == '.') {
      if (line[i + 1] == 's' && line[i + 2] == 't' && line[i + 3] == 'r' && line[i + 4] == 'i' && line[i + 5] == 'n' && line[i + 6] == 'g') {/*check if string*/
        printf("its string\n");
          if(test==1){
          return 1;
        }
        string_parsing(line, i + 7);/*parse string*/
        return 1;
      }
    }
    i++;
  }
  return 0;
}
/*
param : line from file
functionality : check if its command
*/
int check_if_command(char * command,char *line,int label_flag) {

  if(label_flag==1){

  remove_label(command);
  }
  /*check command*/
  if (check_command(command,line,arguments_counter,label_flag) == 0) {
    return 0;
  }
  return 1;
}
/*check arguments of line */
int check_line_arguments(char *line){
  int i=0,j=0;
  int label_flag=0;
  char *temp_string=NULL;
  int comma_counter=0;
  arguments_counter=0;
  /**/
  if(check_if_its_string(line,1)||check_if_its_data(line,1)){
    return 1;
  }
  /*remove label*/
  while(line[i]!='\0'){
    if(line[i]==':'){
      label_flag=1;
      break;
    } 
    i++;
  }
  if(label_flag==0){
  i=0;
}else{
  i++;
}
    /*find first word(command)*/
  while(line[i]!='\0'){
    if(line[i]!=' '&&line[i]!='\t'){
      break;
    }
    i++;
  }
/*find space to the argument list*/
while (line[i]!='\0')
{
  if(line[i]==' '||line[i]=='\t'){
    break;
  }
  i++;
}
while(line[i]!='\0'){
    if(line[i]!=' '&&line[i]!='\t'){
      break;
    }
    i++;
  }

if(line[i]!='\0'&&line[i]!='\n'){
  temp_string =(char*)malloc(strlen(line)*sizeof(char));
  if(temp_string==NULL){
    printf("ERROR: problem\n");
    exit(0);
  }
}
 while(line[i]!='\0'&&line[i]!='\n'){

            temp_string[j++]=line[i];
            
          if(line[i]==','){
            comma_counter+=1;
          }             

    i++;
 }
 
 
 arguments_counter=count_word(temp_string);/*count arguments*/
 
 if(comma_counter==1&&count_word(temp_string)>2){
   printf("*** ERROR at line %d to many arguments in the command ***\n",program_line);
 }
 if(comma_counter==0&&count_word(temp_string)>1){
   printf("*** ERROR at line %d to many arguments in the command ***\n",program_line);

 }
 if(comma_counter>2){
   printf("*** ERROR at line %d to many comma's in the command ***\n",program_line);

 }

free(temp_string);
  return arguments_counter;
}
/*function to count words in line*/
int count_word( char *s) {          
    int count = 0, hassep = 1;
    /*if line is empty*/
    if(s==NULL){
    return 0;
 }
    while (*s) {/*count words*/
        if (isspace((unsigned char)*s)||*s==',') {
            hassep = 1;
        } else {
            count += hassep;
            hassep = 0;
        }
      
        s++;
    }
    return count;
}
/*function to remove label from string end with : */
void remove_label(char *line){
int i=0,j=0;
char *newstring;
int flag=0;
if(label_flag==1){

  newstring=(char*)malloc(strlen(line)*sizeof(char));
  if(newstring==NULL){
    printf(" *** ERROR memory problem *** \n");
    exit(1);
  }
  while (line[i]!='\0')
  {

    if(line[i]==':'){
      flag=1;
      break;
    }
    i++;
  }
  if(flag==1){
      i++;

    while(line[i]!='\0'){
    
        newstring[j++]=line[i];
    i++;
  }

  strcpy(line,newstring);

  }
  
  free(newstring);
}
}