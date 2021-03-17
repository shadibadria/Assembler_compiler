
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
    printf("\ncant open file \n");
    return 0;
  }
  while (fgets(buffer, bufferLength, filePointer)) {
    if(strlen(buffer)>=80){
      printf("ERROR: line to long must be be 80 \n");

    }else{
    assemble_parsing(buffer);

    }

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
  if (line[0] == '\n' || line[0] == '\0') {
    return 0;
  }
  printf("\n******************************\n");
  printf("\nCommand :%s\n", line);
  label_flag = 0;
  check_line_arguments(line);
 parse_line(line);

  

  return 1;
}
/*
param: line from file
functionality: parse the line to data we needby calling functions
*/
int parse_line(char * line) {
  int i = 0, j = 0;
  char temp[500];
 
  if (line[i] == ';') {
    printf("comment\n");
    return 0;
  }
   
  if (check_if_extern(line,0) == 1) {
    return 0;
  }
 if (check_if_entry(line,0) == 1) {
    return 0;
  }
   if (check_if_label(line,0) == 1) {
          label_flag = 1;
        }

      
  while (line[i] != '\0' && line[i] != '\n') {
    if (line[i] != ' ' && line[i] != '\t') {
   
      
      temp[j++] = line[i];
    } else {
      temp[j] = '\0';
      if (j != 0) {
       
       

       
        if (check_if_command(temp,line) == 1) {
          find_adressing_method(line, label_flag);

        }
       
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


  if (line[i] == '\n' || line[i] == '\0') {
    temp[j] = '\0';
    if (strlen(temp)) {
      if(check_if_its_data(temp,0)!=1||check_if_its_string(temp,0))
      if (check_if_command(temp,line) == 0)
        check_line(temp);

    }

  }

  return 1;
}
void check_comma(char *line){
int i=0,counter=0;
while(line[i]!='\0'){
if(line[i]==',') counter++;
  i++;
}
if(counter>1) printf("ERROR : to many comma\n");
}
/*
find adress method and create the bits of it 

*/
int find_adressing_method(char * string, int label_flag) {

  int i = 0;
  char temp[80];
  char * tempstring;
  char last_bits[5] = "0000\n";
  int j = 0, k = 0, commaflag = 0, number_temp = 0;

  tempstring = (char * ) malloc(strlen(string) * sizeof(char));
  if (tempstring == NULL) {
    printf("Something Went Wrong no memory\n");
    return 0;

  }
  strcpy(tempstring, string);
  tempstring[strlen(tempstring)] = '\0';
  if (label_flag == 1) {
    while (tempstring[i] != '\0') {
      if (tempstring[i] == ':') {

        break;
      }
      i++;
    }
    i++;
  }
  remove_spaces_from_index(tempstring, i);
  tempstring[strlen(tempstring)] = '\0';

  i = 0;
  while (tempstring[i] != '\0') {
    if (tempstring[i] == ' ' || tempstring[i] == '\t') {
      break;
    }
    i++;
  }
  remove_spaces_from_index(tempstring, i);
  i = 0;
  tempstring[strlen(tempstring)] = '\0';

  while (tempstring[i] != '\0') {

    temp[j++] = tempstring[i];
    if (tempstring[i] == ',') {
      temp[j - 1] = '\0';
      j = 0;
      commaflag = 1;
      if (check_for_reg(temp, 0) == 1) {
        last_bits[k++] = '1';
        last_bits[k++] = '1';
      } else {
        last_bits[k++] = '0';
        last_bits[k++] = '1';
      }

    }
    i++;

  }
  free(tempstring);
  temp[j] = '\0';

  if (commaflag == 1) {
    if (check_for_reg(temp, 0) == 1) {

      last_bits[k++] = '1';
      last_bits[k++] = '1';
    } else
    if (temp[0] == '#') {
      last_bits[k++] = '0';
      last_bits[k++] = '0';
    } else
    if (temp[0] == '%') {

      last_bits[k++] = '1';
      last_bits[k++] = '0';
    } else {
      last_bits[k++] = '0';
      last_bits[k++] = '1';
    }

  }
  if (commaflag == 0) {
    if (check_for_reg(temp, 0) == 1) {
      last_bits[k++] = '0';
      last_bits[k++] = '0';
      last_bits[k++] = '1';
      last_bits[k++] = '1';
    } else
    if (temp[0] == '#') {
      last_bits[k++] = '0';
      last_bits[k++] = '0';
      last_bits[k++] = '0';
      last_bits[k++] = '0';

    } else
    if (temp[0] == '%') {
      last_bits[k++] = '0';
      last_bits[k++] = '0';
      last_bits[k++] = '1';
      last_bits[k++] = '0';
    } else {
      last_bits[k++] = '0';
      last_bits[k++] = '0';
      last_bits[k++] = '0';
      last_bits[k++] = '1';
    }

  }
  last_bits[5] = '\0';
  number_temp = strtol(last_bits, NULL, 2);
  printf("Lastbits:%s\n", last_bits);
  sprintf(arr[index_of_datatable].adress_method, "%X", number_temp);
  index_of_datatable++;
  return 1;
}
/*
param: line from file
functionality: check if the line is .extern 
*/

int check_if_extern(char * line,int test) {
  int i = 0;
  line[strlen(line)] = '\n';
 
   
  /*check if its .extern */
  if (line[i] != '.' || line[i + 1] != 'e' || line[i + 2] != 'x' || line[i + 3] != 't' || line[i + 4] != 'e' || line[i + 5] != 'r' || line[i + 6] != 'n' || (line[i + 7] != ' ' && line[i + 7] != '\t')) {
    return 0;
  }
  if(test==1){
    return 1;
  }
 
  i = i + 7;
  line = remove_spaces_from_index(line, i);
  i = 0;

  count++;
  line[strlen(line)] = '\0';
  remove_space_tabs(line);
if (checkforduplicate(line) == 0) {
    printf("ERROR extern duplicate found \n");
    return 0;
  }
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
  if (strlen(line) < 7) {
    printf("ERROR \n");
    return 0;
  }
  line = remove_spaces_from_index(line, i);
  /*check if its .extern */
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
  if(test==0){
    return 1;
  }
   if (checkforduplicate(line) == 0) {
        insert_entry(line);

   
  } else {
 printf("ERROR: entry not found in symbol table \n");
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
    printf("Something Went Wrong no memory\n");
    return "bad";
  }

  while (string[i] != '\n' && string[i] != '\0') {
    if (string[i] != ' ' && string[i] != '\t' && !isspace(string[i])) {

      break;
    }
    i++;
  }
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
    printf("Something Went Wrong no memory\n");
      free(newstring);

    return "bad";
  }
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
    printf("Something Went Wrong no memory\n");
    return 0;

  }
  while (line[i] != '\n' && line[i] != '\0') {
   
 
      temp[j++] = line[i];
      
    if (line[i] == ':') {
          temp[j] = '\n';
          printf("[%d]\n",j);
          j=0;
          while(temp[j]!=':'){
           if(temp[j]==' '||temp[j]=='\t'){
            printf("\nERROR:Label has space/tab in it\n");
            break;
          }
          j++;
          }
         
        if(isdigit(temp[0])){
            printf("ERROR:label must start with letter\n");           
        }
        if(strlen(temp)>31){
                      printf("\nERROR:label is to long must be 31 char\n");           

        }
          while(temp[j]!=':'){
            j++;
          }
          if(temp[j]==':'){
            j++;
          }

      if(test==1){
        free(temp);
        return 1;
      }

      temp[j] = '\n';
      printf("label:%s\n", remove_space_tabs(temp));
      if(temp[i]==','){
          free(temp);
        return 0;
      }
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
  
  while (line[i] != '\n' && line[i] != '\0') {
    if (line[i] == '.') {
      if (line[i + 1] == 'd' && line[i + 2] == 'a' && line[i + 3] == 't' && line[i + 4] == 'a') {
        if(test==0){
                  printf("its data :%s\n",line);

        data_parsing(line,i+4);
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
void data_parsing(char * line,int i) {
  char * p = line;
  int val,comma_counter=0,number_counter=0,number_flag=0;
    printf("LINE:%s\n",line);
p+=i;
  line[strlen(line)] = '\0';

      printf("afLINE:%s\n",line);

  while(*p){
    if(*p==','){
      if(number_flag==0){
            printf("ERROR: to many comma's missing numbers\n");

      }
      number_flag=0;
      comma_counter++;
    }else{
           if (isdigit( * p) || (( * p == '-' || * p == '+') && isdigit( * (p + 1)))) {
             number_flag=1;
           }else{
             if(*p!=' '&&*p!='\t'&&number_flag){

              printf("ERROR: to many argument on line :%c \n",*p);
             }
           }

    }
    p++;
  }
  p=line;
  p+=i;
  while ( * p) {

    if (isdigit( * p) || (( * p == '-' || * p == '+') && isdigit( * (p + 1)))) {
      number_counter++;
      val = strtol(p, & p, 10);
      printf("VAL[%d]\n",val);
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
  
  printf("************************%d > %d\n",number_counter,comma_counter);
  if(number_counter==0){
    printf("ERROR: data is missing please insert numbers\n");
  }
  if(number_counter<=comma_counter){
    printf("ERROR: to many comma's missing numbers\n");
  }
   if(number_counter>comma_counter+1){
         printf("ERROR: to many numbers missing comma's  \n");

   }

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
      printf("ERROR: string formating wrong : %c\n",line[index]);
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
    printf("ERROR: string must start with \" \"\n");
  }
  j++;
  while(line[j]!='\0'){
    if(line[j]!=' '&&line[j]!='\t'){
      printf("ERROR: string has char after end :%c\n",line[j]);
    }
    j++;
  }
  while (line[index] != '"' && line[index] != '\n' && line[index] != '\0') {
    string_flag=1;
    printf("\nstr:%c\n", line[index]);

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
    printf("ERROR : string has no values\n");
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
      if (line[i + 1] == 's' && line[i + 2] == 't' && line[i + 3] == 'r' && line[i + 4] == 'i' && line[i + 5] == 'n' && line[i + 6] == 'g') {
        printf("xxstring:%s\n",line);
        printf("its string\n");
          if(test==1){
          return 1;
        }
        string_parsing(line, i + 7);
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
int check_if_command(char * command,char *line) {

  printf("COMMANDbef:%s\n",command);

  
  if(label_flag==1){

  remove_label(command);
  }
 printf("COMMANDAFTER:%s\n",command);
  /*check command*/
  if (check_command(command,line,arguments_counter) == 0) {
    return 0;
  }

  return 1;
}
int check_line_arguments(char *line){
  int i=0,j=0;
  int label_flag=0;
  char *temp_string=NULL;
  int comma_counter=0;
  arguments_counter=0;
  
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
  
  while(line[i]!='\0'){
    if(line[i]!=' '&&line[i]!='\t'){
      break;
    }
    i++;
  }

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
 
 
 arguments_counter=count_word(temp_string);
 if(arguments_counter==0){
   printf("ERROR: missing arguments\n");
 }
 if(comma_counter==1&&count_word(temp_string)>2){
   printf("ERROR: to many arguments x\n");
 }
 if(comma_counter==0&&count_word(temp_string)>1){
   printf("ERROR: to many arguments x\n");

 }
 if(comma_counter>2){
      printf("ERROR: to many comma's\n");

 }

free(temp_string);
  return arguments_counter;
}

int count_word( char *s) {          
    int count = 0, hassep = 1;
    
    if(s==NULL){
return 0;
 }
    while (*s) {
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

void remove_label(char *line){
int i=0,j=0;
char *newstring;
int flag=0;
if(label_flag==1){

  newstring=(char*)malloc(strlen(line)*sizeof(char));
  if(newstring==NULL){
    printf("ERROR: zekron\n");
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