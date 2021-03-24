/*
filename: firstpass.c
first iteration of the assembly program
its porpuse is to add all the labels and data to the symbol table 
and to the datatable
*/
#include"firstpass.h"

#include"data.h"

#include "symbol_table.h"

#include"data_image.h"


int IC = 100;
int DC = 0;
int count = 0;
int program_line = 1; /*to count program lines*/
FILE * filePointer=NULL;
char buffer[bufferLength]={0};
int extern index_of_datatable;
int label_flag = 0;
int arguments_counter = 0;
int command_exist_flag = 0;
int first_pass_flag = 1;
/*
function firstpass - open file for reading line by line and sending it to parse
@param  filename  file name of the assembler file
@return  int
*/
int firstpass(char * filename) {
  filePointer = fopen(filename, "r");
  if (filePointer == NULL) {
    printf("*** ERROR: Cant open file name :%s *** \n", filename);
    exit(0);
  }
     
  while (fgets(buffer, bufferLength, filePointer)) {
    if (strlen(buffer) > MAX_LINE) {
      printf("*** ERROR File is to big must contain max %d \n ***",bufferLength);
      exit(0);
    } else {
      if (IC > bufferLength) {
        printf("*** ERROR at line %d line is  to long, max length is  %d *** \n", bufferLength, program_line);
        exit(0);
      }
    }
    assemble_parsing(buffer); /*send the line to parsing */
  } /*while ends*/
  fclose(filePointer);
  
  return 0;
}

/*
function assemble_parsing - (controller)get line from file and  send it to parsing 
@param line - get 1 line of file and parse it
@return int
*/
int assemble_parsing(char * line) {
  remove_spaces_from_index(line, 0);
  if (line[0] == '\n' || line[0] == '\0' || line[0] == ';') {
    /*if line is empty / if has comment */
    return 0;
  }
 /* printf("\n****************************\n");
  printf("COMMAND:%s\n", line);*/
  label_flag = 0;
   command_exist_flag = 0;

 check_line_arguments(line); /*check if arguments for error*/
  parse_line(line); /*send line to proccess it */
  if (command_exist_flag == 0) {
    printf("*** ERROR at line %d undefined instruction name *** \n", program_line);
    first_pass_flag = 0;
  } 
  program_line++; /*count line*/
  return 1;
}
/*
function  parse_line - parse line from assembler file
@param line  line of file we want to parse
@return int
*/
int parse_line(char * line) {
  int i = 0, j = 0;
  char temp[500];
  /*if line is comment*/
  while (line[i] != '\0') {
    if (line[i] == ';') {
      return 1;
    }
    i++;
  }
  i = 0;
  if (check_if_extern(line, 0) == 1) {
    /*if line is extern insert it */
    return 0;
  }
  if (check_if_entry(line, 0) == 1) {
    /*if line is entry insert it*/
    return 0;
  }

  if (check_if_label(line, 0) == 1) {
    /*if line is label insert it*/
    label_flag = 1;
  }
  /*get word by word*/
  while (line[i] != '\0' && line[i] != '\n') {
    if (line[i] != ' ' && line[i] != '\t') {
      temp[j++] = line[i];
    } else {
      temp[j] = '\0';
      if (j != 0) {
        check_if_command(temp, line, label_flag,0); /*check if word is command*/
        /*check if line is data or string and check comma (',') correction*/
        if (check_if_its_data(line, 0) != 1 && check_if_its_string(line, 0) != 1) {
          check_comma(line);
        } else {
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
      if (check_if_its_data(temp, 0) != 1 || check_if_its_string(temp, 0))
        if (check_if_command(temp, line, label_flag,0) == 0)
          check_line(temp);
    }
  }
  return 1;
}
/*
function check_comma - check if line has comma's and count it 
@parm line - 1 line of assembler file
@return void
*/
void check_comma(char * line) {
  int i = 0, counter = 0;
  while (line[i] != '\0') {
    if (line[i] == ',')
      counter++;
    i++;
  }
  if (counter > 1) {
    printf("*** ERROR at line %d to many comma's ***\n", program_line);
    first_pass_flag = 0;
  }
}
/*
function check_if_extern - check if line is extern label
@param line - 1 line from assembler file
@param test - if test is 1 only check without insert ,if 0 then add extern label to symbol table
@return int
*/
int check_if_extern(char * line, int test) {
  int i = 0;
  
  remove_spaces_from_index(line, 0);

    
  
  while(line[i] !='\0'){
      if(line[i]=='.'){
        break;
      }
    i++;
  }
  
  /*check if its .extern */
  if (line[i] != '.' || line[i + 1] != 'e' || line[i + 2] != 'x' || line[i + 3] != 't' || line[i + 4] != 'e' || line[i + 5] != 'r' || line[i + 6] != 'n' || (line[i + 7] != ' ' && line[i + 7] != '\t')) {
    return 0;
  }
    command_exist_flag = 1;
  if (test == 1) {
    /*if we just want to know its extern*/
    return 1;

  }

  i = i + 7;
  line = remove_spaces_from_index(line, i);
  i = 0;
  count++;
  line[strlen(line)] = '\0';
  remove_space_tabs(line);
  if (checkforduplicate(line) == 0) {
    printf("*** ERROR at line %d local label cannot be declared as external ***\n", program_line); /*second pass error*/
    return 0;
  }
  /*insert external label*/
  insert(DC++, 0, line, "external");
  return 1;
}

/*
function check_if_entry - check if line is entry label
@param line - 1 line from assembler file
@param test - if test is 1 only check without insert ,if 0 then add entry label to symbol table
@return int
*/
int check_if_entry(char * line, int test) {
  int i = 0;

  line[strlen(line)] = '\n';
  line = remove_spaces_from_index(line, i);

  
  while(line[i] !='\0'){
      if(line[i]=='.'){
        break;
      }
    i++;
  }
  /*check if its .entry */
  if (line[i] != '.' || line[i + 1] != 'e' || line[i + 2] != 'n' || line[i + 3] != 't' || line[i + 4] != 'r' || line[i + 5] != 'y' || (line[i + 6] != ' ' && line[i + 6] != '\t')) {
    return 0;
  }
  command_exist_flag = 1; /*the line is instruction is available*/

  i = i + 6;
  line = remove_spaces_from_index(line, i);
  i = 0;
  while (line[i] != '\n' && line[i] != '\0') {
    /*remove new line and tabs*/
    if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n') {
      break;
    }
    i++;
  }
  while (line[i] != '\n' && line[i] != '\0') {
    /*check if there is no values */
    if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && isalpha(line[i])) {
      printf("*** ERROR at line %d  entry must be 1 parameter ***\n", program_line);
      first_pass_flag = 0;
      break;
    }
    i++;
  }
  count++;
  remove_space_tabs(line);
  if (test == 0) {
    /*if the function called for testing only or its called for first pass */
    return 1;
  }
  /*SECOND PASS */
  /*check for label duplicate and insert*/
  if (checkforduplicate(line) == 0) {
    insert_entry(line);
  } else {
    printf("*** Second Pass ERROR  entry label %s is not found on symbol table ***\n", line); /*second pass error*/
    first_pass_flag = 0;
    return 0;
  }
  return 1;
}
/*
function remove_spaces_from_index - remove space/tab from index till first non tab/space
@param: string  - 1 line from file
@param: i       - index of the start (where we want to remove the space/tabs)
@return char*
*/
char * remove_spaces_from_index(char * string, int i) {
  char * newstring;
  int j = 0;
  if (string[i] != '\0' && string[i] != '\t' && string[i] != ' ' && string[i] == '\n' && isspace(string[i])) {
    return 0;
  }
  newstring = (char * ) malloc((strlen(string) + 1) * sizeof(char));
  if (newstring == NULL) {
    printf("*** ERROR  Something Went Wrong no memory ***\n");
    exit(0);
  }
  memset(newstring, 0, strlen(string) * sizeof(char));
  while (string[i] != '\n' && string[i] != '\0') {
    /*find first appering of word*/
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
  if (newstring == NULL) {
    return 0;
  }
  newstring[j] = '\0';
  strcpy(string, newstring);
  free(newstring);
  return string;
}
/*
function remove_space_tabs - remove all space/taps from string
@param string  - string we want to remove the tabs/space
@return char*
*/
char * remove_space_tabs(char * string) {
  char * newstring;
  int j = 0, i = 0;
  int string_len = (strlen(string) + 1);
  newstring = (char * ) malloc(string_len * sizeof(char));
  if (newstring == NULL) {
    printf("*** ERROR Something Went Wrong no memory ***\n");
    exit(0);
  }
  memset(newstring, 0, strlen(string) * sizeof(char));
  /*create new string without spaces/tabs*/
  while (string[i] != '\n' && string[i] != '\0') {
    if (string[i] != ' ' && string[i] != '\t') {
      newstring[j++] = string[i];
    }
    i++;
  }
  newstring[j] = '\0';
  if (strlen(newstring) <= 1) {
    free(newstring);
    return 0;
  }
  strcpy(string, newstring);
  free(newstring);
  return string;
}

/*
function check_if_label - check if line is label and insert it
@param line - line from file
@param test - if we only want to check (1 for testing , 0 for check&insert)
@return int 
*/
int check_if_label(char * line, int test) {
  int i = 0, j = 0;
  char * temp;
  temp = (char * ) malloc((strlen(line) + 2) * sizeof(char));
  if (temp == NULL) {
    printf("*** ERROR Something Went Wrong no memory ***\n");
    exit(0);
  }

  memset(temp, 0, (strlen(line)+2) * sizeof(char));
  /*search for end of the label char ':' */
  while (line[i] != '\n' && line[i] != '\0') {
    temp[j++] = line[i];
    if (line[i] == ':') {
      temp[j] = '\n';
      j = 0;
      while (temp[j] != ':') {
        if (temp[j] == ' ' || temp[j] == '\t') {
          /*check if label has spaces/tabs in it*/
          printf("*** ERROR at line %d Label has space/tab in it ***\n", program_line);
          first_pass_flag = 0;
          break;
        }
        j++;
      }

      if (isdigit(temp[0])) {
        /*check if label start with letters*/
        printf("*** ERROR at line %d label must start with letters ***\n", program_line);
        first_pass_flag = 0;
      }
      if (strlen(temp) > MAX_LABEL) {
        printf("*** ERROR at line %d label is to long must be 31 char ***\n", program_line);
        first_pass_flag = 0;
        return 0;
      }

      while (temp[j] != ':') {
        j++;
      }

      if (test == 1) {
        /*if only testing if its label*/
        free(temp);
                

        return 5;
      }
      remove_space_tabs(temp);

      if (temp[j] == ':') {
        /*remove the ':' if exsist*/
        temp[j] = '\0';

      }else{
        if(temp[j-1]==':'){
          temp[j-1]='\0';
        }
      }
      if(check_for_reg(temp,0)==1){
      printf("*** ERROR at line %d invalid  label \"%s\"  ***\n", program_line, temp);
              first_pass_flag = 0;
            return 0;
      }
       if(check_if_command(temp,line,0,1)==1){
      printf("*** ERROR at line %d invalid  label \"%s\"  ***\n", program_line, temp);
              first_pass_flag = 0;
            return 0;
      }
      if (checkforduplicate(temp) == 0) {

        /*check for duplicate of the label*/
        printf("*** ERROR at line %d label \"%s\" has already exsisted ***\n", program_line, temp);
        first_pass_flag = 0;
       
      }

      if (temp[i] == ',') {
        free(temp);
        return 0;
      } 


      /*insert label with info*/
      if (check_if_its_data(line, 1) == 1) {

        insert(DC++, IC, temp, "data");
      } else
      if (check_if_its_string(line, 1) == 1) {
        insert(DC++, IC, (temp), "data");
      } else {
        insert(DC++, IC, (temp), "code");
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
function check_if_its_data - check if line is .data 
@param line - line from file
@param test - if test=1 then we only testing without insert else insert
@return int
*/
int check_if_its_data(char * line, int test) {

  int i = 0;
 
  /*check if its data*/
  while (line[i] != '\n' && line[i] != '\0') {
    if (line[i] == '.') {
      if (line[i + 1] == 'd' && line[i + 2] == 'a' && line[i + 3] == 't' && line[i + 4] == 'a') {
          command_exist_flag = 1; /*the line is instruction is available*/

        if (test == 0) {
          /*if its not testing only*/
          data_parsing(line, i + 4); /*parse the data to numbers*/
          return 1;
        }
        return 1;
      }
    }
    i++;
  }
  return 0;
}
/*
function data_parsing - if its .data ,  find numbers 
@param line -get line from file
@param i    - index of where numbers start
@return int
*/
int data_parsing(char * line, int i) {
  char * p = line;
  int val, comma_counter = 0, number_counter = 0, number_flag = 0;
  p += i;

  line[strlen(line)] = '\0';
  /*check data format if correct */
   while ( * p) {	
    if ( * p == ',') {	
      if (number_flag == 0) {	
        printf("*** ERROR at line %d to many comma's inserted missing numbers ***\n", program_line);	
        first_pass_flag = 0;	
      }	
      number_flag = 0;	
      comma_counter++;	
    } else {	
      if (isdigit( * p) || (( * p == '-' || * p == '+') && isdigit( * (p + 1)))) {	
        number_flag = 1;	
      }	
    }	
    p++;	
  }	
  p = line;	
  p += i+1;

  /*parse line and insert data*/
  while ( * p) {
    if (isdigit( * p) || (( * p == '-' || * p == '+') && isdigit( * (p + 1)))) {
      number_counter++;
      val = strtol(p, & p, 10);
      if (val > MAX_DATA) {
        printf("*** ERROR at line %d data value is bigger than %d ***\n", program_line, MAX_DATA);
        first_pass_flag = 0;
      }
      if (val < MIN_DATA) {
        printf("*** ERROR at line %d data value is smaller than %d ***\n", program_line, MIN_DATA);
        first_pass_flag = 0;
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
        if(*p!=' '&&*p!='\t'&&*p!=','){
      printf("*** ERROR at line %d invalid character '%c' *** \n",program_line,*p);
              first_pass_flag = 0;
              break;
    
        }
      p++;
    }
  }
  /*Error checking*/
  if (number_counter == 0 || number_flag == 0) {
    printf("*** ERROR at line %d missing values ***\n", program_line);
    first_pass_flag = 0;
  } else {
    if (number_counter <= comma_counter) {
      printf("*** ERROR at line %d  to many numbers missing comma's ***\n", program_line);
      first_pass_flag = 0;
    }
  }
  if (number_counter > comma_counter + 1) {
    printf("*** ERROR at line %d  to many numbers missing comma's ***\n", program_line);
    first_pass_flag = 0;
  }
  return 1;
}

/*
function string_parsing -  get data from .string data array
@param line - line from file
@param index - where the string start
@return int
*/
int string_parsing(char * line, int index) {
  int ascii = 0, string_flag = 0, j = 0;
  int string_starting_flag = 0;

  while (line[index] != '\n' && line[index] != '\0') {
    /*check formate of string*/
    if (line[index] == '"') {
      string_starting_flag++;
      break;
    }
    if (line[index] != ' ' && line[index] != '\t') {
      printf("*** ERROR at line %d  string formating wrong ***\n", program_line);
      first_pass_flag = 0;
      break;
    }
    index++;
  }
  index++;
  j = index;
  while (line[j] != '"' && line[j] != '\n' && line[j] != '\0') {
    /*check for starting of string*/
    j++;
  }
  if (line[j] == '\"') {
    string_starting_flag++;
  }
  if (string_starting_flag != 2) {
    printf("*** ERROR at line %d string must start with \" and end with \" ***\n", program_line);
    first_pass_flag = 0;
  }
  j++;
  while (line[j] != '\0') {
    if (line[j] != ' ' && line[j] != '\t') {
      printf("*** ERROR at line %d invalid characters ***\n", program_line);
      first_pass_flag = 0;
        break;
    }
    j++;
  }
  /*insert string to table by ascii code*/
  while (line[index] != '"' && line[index] != '\n' && line[index] != '\0') {
    string_flag = 1;
    sprintf(arr[index_of_datatable].Adress, "%04d", IC);
    ascii = (int) line[index];
    sprintf(arr[index_of_datatable].opcode, "%X", 0);
    sprintf(arr[index_of_datatable].funct, "%X", ascii);
    sprintf(arr[index_of_datatable].TAG, "%c", 'A');
    index_of_datatable++;
    IC++;
    index++;
  }
  if (string_flag == 0) {
    printf("*** ERROR at line %d  string has no values ***\n", program_line);
    first_pass_flag = 0;
  }
  sprintf(arr[index_of_datatable].Adress, "%04d", IC);
  ascii = 0;
  sprintf(arr[index_of_datatable].opcode, "%03X", ascii);
  sprintf(arr[index_of_datatable].TAG, "%c", 'A');
  index_of_datatable++;
  IC++;
  return 1;
}
/*
function check_if_its_string - check if line is .string 
@param line - line from file
@param test - if test=1 then we only testing without insert else insert
@return int
*/
int check_if_its_string(char * line, int test) {
  int i = 0;

  while (line[i] != '\n' && line[i] != '\0') {
    if (line[i] == '.') {
      /*check if string*/
      if (line[i + 1] == 's' && line[i + 2] == 't' && line[i + 3] == 'r' && line[i + 4] == 'i' && line[i + 5] == 'n' && line[i + 6] == 'g') {
        if (test == 1) {
          /*if only for testing return*/
          return 1;
        }
        command_exist_flag = 1;
        string_parsing(line, i + 7); /*parse string*/
        return 1;
      }
    }
    i++;
  }
  return 0;
}
/*
function check_if_command  - check if line is command
@param command - string that we want to check if its command
@param line    - line from file that has the command
@param label_flag - if 1 there is label else no label
@return int
*/
int check_if_command(char * command, char * line, int label_flag,int test) {

  if (label_flag == 1) {
    /*if there is label*/
    remove_label(command);
  }

  if(test==1){
  if (check_command(command, line, arguments_counter, label_flag,0) == 1) {
return 1;
  }else{
    return 0;
  }
  }
  
  /*check command*/
  if (check_command(command, line, arguments_counter, label_flag,0) == 0) {
    return 0;
  } else {
    command_exist_flag = 1;

  }
  return 1;
}
/*
function check_line_arguments - check arguments of line  if correct
@param line - line from file that we want to check
@return int 
*/
int check_line_arguments(char * line) {
  int i = 0, j = 0;
  int label_flag = 0;
  char * temp_string = NULL;
  int comma_counter = 0;
  arguments_counter = 0;
  if (strlen(line) <= 0) return 0;
  temp_string = (char * ) malloc((strlen(line) + 1) * sizeof(char));
  if (temp_string == NULL) {
    printf("*** ERROR problem allocate memory ***\n");
    exit(0);
  }
  memset(temp_string, 0, (strlen(line) + 1) * sizeof(char));
  if (check_if_its_string(line, 1) || check_if_its_data(line, 1)) {
    free(temp_string);
    return 1;
  }
  /*remove label*/
  while (line[i] != '\0') {
    if (line[i] == ':') {
      label_flag = 1;
      break;
    }
    i++;
  }
  if (label_flag == 0) {
    i = 0;
  } else {
    i++;
  }
  /*find first word(command)*/
  while (line[i] != '\0') {
    if (line[i] != ' ' && line[i] != '\t') {
      break;
    }
    i++;
  }
  /*find space to the argument list*/
  while (line[i] != '\0') {
    if (line[i] == ' ' || line[i] == '\t') {
      break;
    }
    i++;
  }
  while (line[i] != '\0') {
    /*check for char*/
    if (line[i] != ' ' && line[i] != '\t') {
      break;
    }
    i++;
  }

  while (line[i] != '\0' && line[i] != '\n') {
    /*check for comma*/
    temp_string[j++] = line[i];
    if (line[i] == ',') {
      comma_counter += 1;
    }
    i++;
  }
  
  arguments_counter = count_word(temp_string); /*count arguments*/

  free(temp_string);
  return arguments_counter;
}
/*
function count_word -  to count words in line
@param string - string we want to check 
@return int 
*/
int count_word(char * string) {
  int count = 0, flag = 1;
  int i = 0;
  /*if line  is empty*/
  if (string == NULL) {
    return 0;
  }
  while (string[i] != '\0') {
    if (isspace((unsigned char) string[i]) || ((string[i] == ',') && check_for_char(string))) {
      flag = 1;
    } else {
      count += flag;
      flag = 0;
    }
    i++;
  }
  return count;
}
/*
function check_for_char - check for first char in line
@param string - string we want to check
@return int
*/
int check_for_char(char * string) {
  int i = 0;
  while (string[i] != '\0') {
    if (string[i] != ' ' && string[i] != '\t' && string[i] != ',') {
      return 1;
    }
    i++;
  }
  return 0;
}
/*
function remove_label - to remove label from string end with :
@param line - string we want to remove the label
@return void
 */
void remove_label(char * line) {
  int i = 0, j = 0;
  char * newstring;
  int flag = 0;
  if (label_flag == 1) {
    newstring = (char * ) malloc((strlen(line) + 1) * sizeof(char));
    if (newstring == NULL) {
      printf("*** ERROR memory problem *** \n");
      exit(0);
    }
    memset(newstring, 0, strlen(line) * sizeof(char));
    i = 0;
    while (line[i] != '\0') {
      if (line[i] == ':') {
        flag = 1;
        break;
      }
      i++;
    }
    if (flag == 1) {
      i++;
      while (line[i] != '\0') {/*new string*/
        newstring[j++] = line[i];
        i++;
      }
      strcpy(line, newstring);
    }
    free(newstring);
  }
}