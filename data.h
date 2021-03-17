/*
file name : data.h
explain : header file have declration of function for data.c and struct of command
*/
#define COMMAND_NAME_MAX_SIZE 5
#define COMMANDS_AMOUNT 16
#define REGISTERS_COUNT 8
#include<string.h>

#include<stdio.h>

#include<ctype.h>

#include"firstpass.h"

typedef struct command {

  char command_name[COMMAND_NAME_MAX_SIZE];
  char funct[5];
  char opcode[5];
  int allowed_operand;
}
command;

void init_commands();
int check_command(char * command,char *line,int argument_counter);
int check_line(char * line);
const char * reg[REGISTERS_COUNT];
void init_registers();
char command_code[13];
int code_opcode_parsing(char * command_code, char * command_func);

int check_for_reg(char * string, int add_to_table_flag);