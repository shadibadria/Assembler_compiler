/*
filename : data.c
this file has the all the fucntion of parsing the data /string 
*/

#include"data.h"

#include"data_image.h"

#include"symbol_table.h"

int extern IC;
int extern index_of_datatable;
int extern program_line;
int extern first_pass_flag;
command mycommands[COMMANDS_AMOUNT];

/*
function init_commands - it init the commands of the program 
@param none
@return void
*/
void init_commands() {
  int i = 0;
  /*setting up commands*/
  strcpy(mycommands[i].command_name, "mov\0");
  strcpy(mycommands[i].opcode, "0000\0");
  strcpy(mycommands[i].funct, "0000\0");
  mycommands[i].allowed_operand = 2;
  strcpy(mycommands[i].source_operands, "0,1,3\0");
  strcpy(mycommands[i].dest_operands, "1,3\0");

  i++;
  strcpy(mycommands[i].command_name, "cmp\0");
  strcpy(mycommands[i].opcode, "0001\0");
  strcpy(mycommands[i].funct, "0000\0");
  mycommands[i].allowed_operand = 2;
  strcpy(mycommands[i].source_operands, "0,1,3\0");
  strcpy(mycommands[i].dest_operands, "0,1,3\0");

  i++;
  strcpy(mycommands[i].command_name, "add\0");
  strcpy(mycommands[i].opcode, "0010\0");
  strcpy(mycommands[i].funct, "1010\0");
  mycommands[i].allowed_operand = 2;
  strcpy(mycommands[i].source_operands, "0,1,3\0");
  strcpy(mycommands[i].dest_operands, "1,3\0");

  i++;
  strcpy(mycommands[i].command_name, "sub\0");
  strcpy(mycommands[i].opcode, "0010\0");
  strcpy(mycommands[i].funct, "1011\0");
  mycommands[i].allowed_operand = 2;
  strcpy(mycommands[i].source_operands, "0,1,3\0");
  strcpy(mycommands[i].dest_operands, "1,3\0");

  i++;
  strcpy(mycommands[i].command_name, "lea\0");
  strcpy(mycommands[i].opcode, "0100\0");
  strcpy(mycommands[i].funct, "0000\0");
  mycommands[i].allowed_operand = 2;
  strcpy(mycommands[i].source_operands, "1\0");
  strcpy(mycommands[i].dest_operands, "1,3\0");

  i++;

  strcpy(mycommands[i].command_name, "clr\0");
  strcpy(mycommands[i].opcode, "0101\0");
  strcpy(mycommands[i].funct, "1010\0");
  mycommands[i].allowed_operand = 1;
  strcpy(mycommands[i].source_operands, "0\0");
  strcpy(mycommands[i].dest_operands, "1,3\0");
  i++;

  strcpy(mycommands[i].command_name, "not\0");
  strcpy(mycommands[i].opcode, "0101\0");
  strcpy(mycommands[i].funct, "1011\0");
  mycommands[i].allowed_operand = 1;
  strcpy(mycommands[i].source_operands, "0\0");
  strcpy(mycommands[i].dest_operands, "1,3\0");

  i++;

  strcpy(mycommands[i].command_name, "inc\0");
  strcpy(mycommands[i].opcode, "0101\0");
  strcpy(mycommands[i].funct, "1100\0");
  mycommands[i].allowed_operand = 1;
  strcpy(mycommands[i].source_operands, "0\0");
  strcpy(mycommands[i].dest_operands, "1,3\0");
  i++;

  strcpy(mycommands[i].command_name, "dec\0");
  strcpy(mycommands[i].opcode, "0101\0");
  strcpy(mycommands[i].funct, "1101\0");
  mycommands[i].allowed_operand = 1;
  strcpy(mycommands[i].source_operands, "0\0");
  strcpy(mycommands[i].dest_operands, "1,3\0");

  i++;

  strcpy(mycommands[i].command_name, "jmp\0");
  strcpy(mycommands[i].opcode, "1001\0");
  strcpy(mycommands[i].funct, "1010\0");
  mycommands[i].allowed_operand = 1;
  strcpy(mycommands[i].source_operands, "0\0");
  strcpy(mycommands[i].dest_operands, "1,2\0");

  i++;

  strcpy(mycommands[i].command_name, "bne\0");
  strcpy(mycommands[i].opcode, "1001\0");
  strcpy(mycommands[i].funct, "1011\0");
  mycommands[i].allowed_operand = 1;
  strcpy(mycommands[i].source_operands, "0\0");
  strcpy(mycommands[i].dest_operands, "1,2\0");
  i++;

  strcpy(mycommands[i].command_name, "jsr\0");
  strcpy(mycommands[i].opcode, "1001\0");
  strcpy(mycommands[i].funct, "1100\0");
  mycommands[i].allowed_operand = 1;
  strcpy(mycommands[i].source_operands, "0\0");
  strcpy(mycommands[i].dest_operands, "1,2\0");

  i++;

  strcpy(mycommands[i].command_name, "red\0");
  strcpy(mycommands[i].opcode, "1100\0");
  strcpy(mycommands[i].funct, "0000\0");
  mycommands[i].allowed_operand = 1;
  strcpy(mycommands[i].source_operands, "0\0");
  strcpy(mycommands[i].dest_operands, "1,3\0");

  i++;

  strcpy(mycommands[i].command_name, "prn\0");
  strcpy(mycommands[i].opcode, "1101\0");
  strcpy(mycommands[i].funct, "0000\0");
  mycommands[i].allowed_operand = 1;
  strcpy(mycommands[i].source_operands, "0\0");
  strcpy(mycommands[i].dest_operands, "0,1,3\0");

  i++;

  strcpy(mycommands[i].command_name, "rts\0");
  strcpy(mycommands[i].opcode, "1110\0");
  strcpy(mycommands[i].funct, "0000\0");
  mycommands[i].allowed_operand = 1;
  strcpy(mycommands[i].source_operands, "0\0");
  strcpy(mycommands[i].dest_operands, "1,2\0");
  i++;

  strcpy(mycommands[i].command_name, "stop\0");
  strcpy(mycommands[i].opcode, "1111\0");
  strcpy(mycommands[i].funct, "0000\0");
  mycommands[i].allowed_operand = 0;
  strcpy(mycommands[i].source_operands, "0\0");
  strcpy(mycommands[i].dest_operands, "0\0");
}

/*
function check_command - check if the command is correct 
@param command - its the command we want to check
@param line    - its the full line we get
@param argument_counter  - its the count of arguments for command 
@param label_flag     - flag for checking if the line is label 
@return  1-success 0-Error
*/
int check_command(char * command, char * line, int argument_counter, int label_flag) {
  int i = 0;
  if (command[strlen(command) - 1] == ',') {
    /*check for comma*/
    command[strlen(command) - 1] = '\0';

  }
  i = strlen(command);
  while (line[i] == ' ' || line[i] == '\t') {
    /*remove the space/tab*/
    i++;
  }
  command[strlen(command)] = '\0';
  for (i = 0; i < COMMANDS_AMOUNT; i++) {
    /*check the arguments if correct*/
    if (strcmp(mycommands[i].command_name, command) == 0) {

      if (mycommands[i].allowed_operand > argument_counter) {
        
          printf("***ERROR at line %d missing operand ***\n", program_line);
          first_pass_flag = 0;
      }else{
              if (mycommands[i].allowed_operand < argument_counter) {
                printf("***ERROR at line %d to many operands ***\n", program_line);
               first_pass_flag = 0;
              }

      }

      sprintf(arr[index_of_datatable].Adress, "%04d", IC); /*insert to data table*/
      IC++;
      code_opcode_parsing(mycommands[i].opcode, mycommands[i].funct);
      find_adressing_method(line, label_flag, command);
      return 1;
    }
  } /*End of for*/
  return 0;
}
/*
@function  find adress method and create the bits of it 
@param string - has line of the file
@param label_flag - if the line with label or not
@param command   - has the command name
@return 1 -success 0 -Error
*/
int find_adressing_method(char * string, int label_flag, char * command) {
  int i = 0;
  char word[80]={0};
  char *tempstring = NULL;
  int dest=0, source=0;
  char last_bits[5] = "0000\n";
  int j = 0, k = 0, commaflag = 0, number_temp = 0;
  tempstring = (char * ) malloc((strlen(string) + 2) * sizeof(char));
  if (tempstring == NULL) {
    printf("*** ERROR Something Went Wrong no memory ***\n");
    exit(0);
  }
  memset(tempstring, 0, (strlen(string) + 2) * sizeof(char));

  strcpy(tempstring, string);
  tempstring[strlen(tempstring)] = '\0';
  if (label_flag == 1) {
    /*if there is label in the string remove it*/
    while (tempstring[i] != '\0') {
      if (tempstring[i] == ':') {
        /*if label*/
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
    /*remove space/tabs*/
    if (tempstring[i] == ' ' || tempstring[i] == '\t') {
      break;
    }
    i++;
  }
  remove_spaces_from_index(tempstring, i);
  i = 0;
  tempstring[strlen(tempstring)] = '\0';
  while (tempstring[i] != '\0') {
    /*find comma*/
    word[j++] = tempstring[i];
    if (tempstring[i] == ',') {
      commaflag = 1;

      break;
    }
    i++;
  }
  i++;
  if (commaflag == 0) {
    /*if no comma present in the line*/
    if (check_for_reg(tempstring, 0) == 1) {
      /*if the string is register*/
      last_bits[k++] = '0';
      last_bits[k++] = '0';
      last_bits[k++] = '1';
      last_bits[k++] = '1';
    } else
    if (tempstring[0] == '#') {
      /*if the string is number*/
      last_bits[k++] = '0';
      last_bits[k++] = '0';
      last_bits[k++] = '0';
      last_bits[k++] = '0';
    } else
    if (tempstring[0] == '%') {
      /*if the string is adress*/
      last_bits[k++] = '0';
      last_bits[k++] = '0';
      last_bits[k++] = '1';
      last_bits[k++] = '0';
    } else
    if (strstr(command, "stop") != NULL) {
      /*if the command stop*/
      last_bits[k++] = '0';
      last_bits[k++] = '0';
      last_bits[k++] = '0';
      last_bits[k++] = '0';
    } else {
      /*if label*/
      last_bits[k++] = '0';
      last_bits[k++] = '0';
      last_bits[k++] = '0';
      last_bits[k++] = '1';
    }
  } else {
    /* comma present*/
    word[j - 1] = '\0';
    j = 0;
    if (check_for_reg(word, 0) == 1) {
      /*if string register*/
      last_bits[k++] = '1';
      last_bits[k++] = '1';
    } else
    if (word[0] == '#') {
      /*if string number*/
      last_bits[k++] = '0';
      last_bits[k++] = '0';
    } else
    if (word[0] == '%') {
      /*if string adress*/
      last_bits[k++] = '1';
      last_bits[k++] = '0';
    } else {
      /*if string label*/
      last_bits[k++] = '0';
      last_bits[k++] = '1';
    }
    j = 0;
    while (tempstring[i] != '\0') {
      /*cpy string to temp*/
      word[j++] = tempstring[i];
      i++;
    }
    word[j] = '\0';
    remove_space_tabs(word);
    if (check_for_reg(word, 0) == 1) {
      /*second argument if register*/
      last_bits[k++] = '1';
      last_bits[k++] = '1';
    } else
    if (word[0] == '#') {
      /*second argument if number*/
      last_bits[k++] = '0';
      last_bits[k++] = '0';
      last_bits[5] = '\0';
    } else
    if (word[0] == '%') {
      /*second argument if adress*/
      last_bits[k++] = '1';
      last_bits[k++] = '0';
    } else {
      /*second argument if label*/
      last_bits[k++] = '0';
      last_bits[k++] = '1';
    }
  }
  last_bits[5] = '\0';
  free(tempstring); /*free temp string*/

  /*create last 4 bits*/
  if (word != NULL) {
    number_temp = strtol(last_bits, NULL, 2);
    word[0] = last_bits[0];
    word[1] = last_bits[1];
    word[3] = '\0';
    source = strtol(word, NULL, 2);
    word[0] = last_bits[2];
    word[1] = last_bits[3];
    word[2] = '\0';
    dest = strtol(word, NULL, 2);
  }
  sprintf(arr[index_of_datatable].adress_method, "%X", number_temp); /*insert bits*/
  index_of_datatable++;
  check_command_corrections(source, dest, command); /*check if argument is correct*/
  return 1;
}
/*
@function check_command_corrections - checks if command dest and source is correct or not by comparing them to command
@params source - source operand number
@param  dest   - destination operand number 
@return 1 - success , 0 - error
*/
int check_command_corrections(int source, int dest, char * command) {
  int i = 0, j = 0;
  int source_flag = 0;
  int dest_flag = 0;

  for (i = 0; i < COMMANDS_AMOUNT; i++) {
    /*loop commands*/
    if (strcmp(mycommands[i].command_name, command) == 0) {
      /*check if the command dest is the same as the params we got*/
      while (mycommands[i].dest_operands[j] != '\0') {
        if ((mycommands[i].dest_operands[j] - '0') == dest) {
          /*check dest*/
          dest_flag = 1;
        }
        j++;
      }
      j = 0;

      /*check if the command source is the same as the params we got*/
      while (mycommands[i].source_operands[j] != '\0') {
        if ((mycommands[i].source_operands[j] - '0') == source) {
          source_flag = 1;
        }
        j++;
      }
      if (!source_flag) {
        printf("*** ERRORs at line %d source operand addressing error ***\n", program_line);
        first_pass_flag = 0;
      }
      if (!dest_flag) {
        printf("*** ERRORs at line %d destination operand addressing error ***\n", program_line);
        first_pass_flag = 0;
      }
      return 1;
    }
  }
  return 1;
}

/*
function code_opcode_parsing  create hex value for command bits and insert them
@param command_code - command opcode bits 
@param command_func - command func bits
@return 1 - error , 0 -success
*/
int code_opcode_parsing(char * command_opcode, char * command_func) {

  int number_temp = 0;

  if (strcmp(command_opcode, "1111") == 0) {
    number_temp = strtol(command_opcode, NULL, 2);
    sprintf(arr[index_of_datatable].opcode, "%01X", number_temp);
    number_temp = strtol(command_func, NULL, 2);
    sprintf(arr[index_of_datatable].funct, "%02X", number_temp);
    sprintf(arr[index_of_datatable].TAG, "%c", 'A');
    printf("%s\n", command_func);
    index_of_datatable++;
    return 0;
  }
  number_temp = strtol(command_opcode, NULL, 2);
  sprintf(arr[index_of_datatable].opcode, "%X", number_temp);
  number_temp = strtol(command_func, NULL, 2);
  sprintf(arr[index_of_datatable].funct, "%X", number_temp);
  sprintf(arr[index_of_datatable].TAG, "%c", 'A');
  return 0;
}

/*
function check_if_number - check if the string/line we got is number
@param string - its a line of the file
@return 1-success , 0 - error
*/
int check_if_number(char * string) {
  int i = 0;
  int number_temp=0,isnumberflag=0;
  while (string[i] != '\0') {
    if(string[i]=='#'){
        isnumberflag=1;
        break;
      }
       i++;
    }
      if(isnumberflag==1){
          while (string[i] != '\0') {
    if ((string[i] == '#' && isdigit(string[i + 1]) != 0) || (string[i] == '#' && string[i + 1] == '-' && isdigit(string[i + 2]) != 0)) {
      sprintf(arr[index_of_datatable].Adress, "%04d", IC);
      memmove(string, string + 1, strlen(string));
      sprintf(arr[index_of_datatable].TAG, "%c", 'A');
      number_temp = strtol(string, NULL, 10);
      if (number_temp > MAX_DATA || number_temp < MIN_DATA) {
        printf("*** ERROR at line %d  number must be between %d to %d ***\n", program_line, MIN_DATA, MAX_DATA);
        first_pass_flag = 0;
      }
      sprintf(arr[index_of_datatable].opcode, "%03X", number_temp);
      if (number_temp < 0) {
        arr[index_of_datatable].opcode[0] = '\0';
        arr[index_of_datatable].funct[4] = '\0';
      }
      index_of_datatable++;
      IC++;
      return 1;
    }else{
      printf("*** ERROR at line %d invalid characters *** \n ",program_line);
      first_pass_flag=0;
      break;
    }
            i++;
          }

      }

    
  
  return 0;
}
/*
function check_line - check command if register / label / number
@param line - one line of file 
@return 1- error , 0- success
*/
int check_line(char * line) {
  int i = 0, j = 0;
  char temp[80];
  int comma_flag = 0;

  if (strcmp("stop", line) == 0) {
    /*if line is stop word return */
    return 1;
  }
  while (line[i] != '\n' && line[i] != '\0') {
    /*check if number is register or number*/
    temp[j++] = line[i];
    if (line[i] == ',') {
      comma_flag = 1;
      temp[j - 1] = '\0';
      if (check_if_number(temp) == 1) {
        break;
      }
      if (check_for_reg(temp, 1) == 1) {
        break;
      }
      sprintf(arr[index_of_datatable].Adress, "%04d", IC);
      if (strcmp(find_label(temp), "?") == 0) {
        sprintf(arr[index_of_datatable].label_name, "%s", temp);
        sprintf(arr[index_of_datatable].opcode, "%s", "?");
      }
      index_of_datatable++;
      IC++;
      break;
    }
    i++;
  } /*end while*/
  if (comma_flag == 0) {
    /*if line does not have comma*/
    line[strlen(line)] = '\0';
    if(isdigit(line[0])!=0){
      printf("*** ERROR at line %d invalid operand***\n",program_line);
      first_pass_flag=0;
    }
    if (check_if_number(line) == 1) return 1;
    if (check_for_reg(line, 1)) return 1;
    sprintf(arr[index_of_datatable].Adress, "%04d", IC);
    if (strcmp(find_label(line), "?") == 0) {
      sprintf(arr[index_of_datatable].label_name, "%s", line);
      sprintf(arr[index_of_datatable].opcode, "%s", "?");
    }
    index_of_datatable++;
    IC++;
    return 0;
  }
  i++;
  temp[0] = '\0';
  j = 0;
  while (line[i] != '\0') {
    /*copy to newstring*/
    temp[j++] = line[i];
    i++;
  }
  temp[j] = '\0';
  if (check_if_number(temp) == 1) /*check if its number*/
    return 1;
  if (check_for_reg(temp, 1) == 1){
  return 1;
  } /*check if its register*/
  
  sprintf(arr[index_of_datatable].Adress, "%04d", IC);
  if (strcmp(find_label(temp), "?") == 0) {
    sprintf(arr[index_of_datatable].label_name, "%s", temp);
    sprintf(arr[index_of_datatable].opcode, "%s", "?");
  }
  index_of_datatable++;
  IC++;
  return 0;
}
/*
function check_for_reg - check if the line/string is register value
@param string - 1 line of file
@param add_to_table_flag - flag for testing the function if 1 we insert value if not we dont 
@return 1 - success , 0 - error
*/
int check_for_reg(char * string, int add_to_table_flag) {
  int i = 0;
  char register_maker[13] = {
    "000000000000\n"
  };
  int number_temp = 0;
  register_maker[13] = '\0';
  for (i = 0; i < REGISTERS_COUNT; i++) {
    if (!strcmp(reg[i], string)) {
      register_maker[11 - i] = '1';
      /*insert values of the register*/
      if (add_to_table_flag == 1) {
        sprintf(arr[index_of_datatable].Adress, "%04d", IC);
        IC++;
        strncpy(arr[index_of_datatable].opcode, register_maker, 4);
        number_temp = strtol(arr[index_of_datatable].opcode, NULL, 2);
        sprintf(arr[index_of_datatable].opcode, "%X", number_temp);
        strncpy(arr[index_of_datatable].funct, register_maker + 4, 4);
        number_temp = strtol(arr[index_of_datatable].funct, NULL, 2);
        sprintf(arr[index_of_datatable].funct, "%X", number_temp);
        strncpy(arr[index_of_datatable].adress_method, register_maker + 8, 12);
        number_temp = strtol(arr[index_of_datatable].adress_method, NULL, 2);
        sprintf(arr[index_of_datatable].adress_method, "%X", number_temp);
        sprintf(arr[index_of_datatable].TAG, "%c", 'A');
        index_of_datatable++;
        return 1;
      }
      return 1;
    }
  }
  return 0;
}
/*
function init_registers  -create register of the program
@param none
@return void
*/
void init_registers() {
  reg[0] = "r0";
  reg[1] = "r1";
  reg[2] = "r2";
  reg[3] = "r3";
  reg[4] = "r4";
  reg[5] = "r5";
  reg[6] = "r6";
  reg[7] = "r7";
}