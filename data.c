/*
 * File Name : data.c
 * This file provide all the functions of the commands and register initializing and parsing.
 * Author : Shadi Badria <shadibadria@gmail.com>
 */
#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

#include"data.h"
#include"data_image.h"
#include"symbol_table.h"
#include"firstpass.h"

int extern IC;
int extern index_of_datatable;
int extern program_line;
int extern first_pass_flag;
command mycommands[COMMANDS_AMOUNT];

/*
function init_command_database - database for the commands for the program 
@param none
@return void
*/
void init_command_database() {
  command_init("mov\0", "0000\0", "0000\0", 2, "0,1,3,\0", "1,3\0", 0);
  command_init("cmp\0", "0001\0", "0000\0", 2, "0,1,3,\0", "0,1,3\0", 1);
  command_init("add\0", "0010\0", "1010\0", 2, "0,1,3,\0", "1,3\0", 2);
  command_init("sub\0", "0010\0", "1011\0", 2, "0,1,3,\0", "1,3\0", 3);
  command_init("lea\0", "0100\0", "0000\0", 2, "1\0", "1,3\0", 4);
  command_init("clr\0", "0101\0", "1010\0", 1, "0\0", "1,3\0", 5);
  command_init("not\0", "0101\0", "1011\0", 1, "0\0", "1,3\0", 6);
  command_init("inc\0", "0101\0", "1100\0", 1, "0\0", "1,3\0", 7);
  command_init("dec\0", "0101\0", "1101\0", 1, "0\0", "1,3\0", 8);
  command_init("jmp\0", "1001\0", "1010\0", 1, "0\0", "1,2\0", 9);
  command_init("bne\0", "1001\0", "1011\0", 1, "0\0", "1,2\0", 10);
  command_init("jsr\0", "1001\0", "1100\0", 1, "0\0", "1,2\0", 11);
  command_init("red\0", "1100\0", "0000\0", 1, "0\0", "1,3\0", 12);
  command_init("prn\0", "1101\0", "0000\0", 1, "0\0", "0,1,3\0", 13);
  command_init("rts\0", "1110\0", "0000\0", 0, "0\0", "0\0", 14);
  command_init("stop\0", "1111\0", "0000\0", 0, "0\0", "0\0", 15);
}
/*
function command_init - this function take argument of the command and add it to the command_table
@param command_name  - command name 
@param command_opcode - the opcode of the command
@param command_funct - the funct of the command
@param allowed_operand_number - the allowed operand numbers of the commands 
@param source_operand -  the source operand numbers allowed 
@param dest_operand - the destination operand numbers allowed 
@param index - the index of command (for inserting commands one by one)
@return void
*/
void command_init(char * command_name, char * command_opcode, char * command_funct, unsigned int allowed_operand_number, char * source_operand, char * dest_operand, unsigned int index) {
  strcpy(mycommands[index].command_name, command_name);
  strcpy(mycommands[index].opcode, command_opcode);
  strcpy(mycommands[index].funct, command_funct);
  mycommands[index].allowed_operand = allowed_operand_number;
  strcpy(mycommands[index].source_operands, source_operand);
  strcpy(mycommands[index].dest_operands, dest_operand);
}
/*
function check_command - check if the command is correct 
@param command - its the command we want to check
@param line    - its the full line we get
@param argument_counter  - its the count of arguments for command 
@param label_flag     - flag for checking if the line is label 
@param test       -  only for testing if string is
@return  int
*/
int check_command(char * command, char * line, int argument_counter, int label_flag, int test) {
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
      if (test == 1) {
        return 1;
      }
      if (mycommands[i].allowed_operand > argument_counter) {
        printf("*** ERROR at line %d missing operand ***\n", program_line);
        first_pass_flag = 0;
      } else {
        if (mycommands[i].allowed_operand < argument_counter) {
          printf("*** ERROR at line %d to many operands ***\n", program_line);
          first_pass_flag = 0;
        }
      }
      sprintf(data_table[index_of_datatable].Adress, "%04d", IC); /*insert to data table*/
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
@return int
*/
int find_adressing_method(char * string, int label_flag, char * command) {
  int i = 0;
  char word[MAX_LINE] = {
    0
  };
  char * tempstring = NULL;
  int dest = 0, source = 0;
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
    if (strstr(command, "stop") != NULL || strstr(command, "rts") != NULL) {
      /*if the command stop/rts*/
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
  sprintf(data_table[index_of_datatable].adress_method, "%X", number_temp); /*insert bits*/
  index_of_datatable++;
  check_command_corrections(source, dest, command); /*check if argument is correct*/
  return 1;
}
/*
@function check_command_corrections - checks if command dest and source is correct or not by comparing them to command
@params source - source operand number
@param  dest   - destination operand number 
@return int
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
        printf("*** ERROR at line %d source operand addressing error ***\n", program_line);
        first_pass_flag = 0;
      }
      if (!dest_flag) {
        printf("*** ERROR at line %d destination operand addressing error ***\n", program_line);
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
@return int
*/
int code_opcode_parsing(char * command_opcode, char * command_func) {

  int number_temp = 0;

  if (strcmp(command_opcode, "1111") == 0) {
    number_temp = strtol(command_opcode, NULL, 2);
    sprintf(data_table[index_of_datatable].opcode, "%01X", number_temp);
    number_temp = strtol(command_func, NULL, 2);
    sprintf(data_table[index_of_datatable].funct, "%02X", number_temp);
    sprintf(data_table[index_of_datatable].TAG, "%c", 'A');
    index_of_datatable++;
    return 0;
  }
  number_temp = strtol(command_opcode, NULL, 2);
  sprintf(data_table[index_of_datatable].opcode, "%X", number_temp);
  number_temp = strtol(command_func, NULL, 2);
  sprintf(data_table[index_of_datatable].funct, "%X", number_temp);
  sprintf(data_table[index_of_datatable].TAG, "%c", 'A');
  return 0;
}

/*
function check_if_number - check if the string/line we got is number
@param string - its a line of the file
@return int
*/
int check_if_number(char * string) {
  int i = 0;
  int number_temp = 0, isnumberflag = 0;
  while (string[i] != '\0') {
    if (string[i] == '#') {
      isnumberflag = 1;
      break;
    }
    i++;
  }
  if (isnumberflag == 1) {
    while (string[i] != '\0') {
      if ((string[i] == '#' && isdigit(string[i + 1]) != 0) || (string[i] == '#' && string[i + 1] == '-' && isdigit(string[i + 2]) != 0)) {
        sprintf(data_table[index_of_datatable].Adress, "%04d", IC);
        memmove(string, string + 1, strlen(string));
        sprintf(data_table[index_of_datatable].TAG, "%c", 'A');
        number_temp = strtol(string, NULL, 10);
        if (number_temp > MAX_DATA || number_temp < MIN_DATA) {
          printf("*** ERROR at line %d  number must be between %d to %d *** \n", program_line, MIN_DATA, MAX_Data_TABLE);
          first_pass_flag = 0;
        }
        sprintf(data_table[index_of_datatable].opcode, "%03X", number_temp);
        if (number_temp < 0) {
          data_table[index_of_datatable].opcode[0] = '\0';
          data_table[index_of_datatable].funct[4] = '\0';
        }
        index_of_datatable++;
        IC++;
        return 1;
      } else {
        printf("*** ERROR at line %d invalid characters *** \n", program_line);
        first_pass_flag = 0;
        break;
      }
      i++;
    }
  }
  return 0;
}

/*
function check_for_reg - check if the line/string is register value
@param string - 1 line of file
@param add_to_table_flag - flag for testing the function if 1 we insert value if not we dont 
@return int
*/
int check_for_reg(char * string, int add_to_table_flag) {
  int i = 0;
  char register_maker[BIT_MAX] = {
    "000000000000\n"
  };
  int number_temp = 0;
  register_maker[13] = '\0';
  for (i = 0; i < REGISTERS_COUNT; i++) {
    if (!strcmp(reg[i], string)) {
      register_maker[11 - i] = '1';
      /*insert values of the register*/
      if (add_to_table_flag == 1) {
        sprintf(data_table[index_of_datatable].Adress, "%04d", IC);
        IC++;
        strncpy(data_table[index_of_datatable].opcode, register_maker, 4);
        number_temp = strtol(data_table[index_of_datatable].opcode, NULL, 2);
        sprintf(data_table[index_of_datatable].opcode, "%X", number_temp);
        strncpy(data_table[index_of_datatable].funct, register_maker + 4, 4);
        number_temp = strtol(data_table[index_of_datatable].funct, NULL, 2);
        sprintf(data_table[index_of_datatable].funct, "%X", number_temp);
        strncpy(data_table[index_of_datatable].adress_method, register_maker + 8, 12);
        number_temp = strtol(data_table[index_of_datatable].adress_method, NULL, 2);
        sprintf(data_table[index_of_datatable].adress_method, "%X", number_temp);
        sprintf(data_table[index_of_datatable].TAG, "%c", 'A');
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