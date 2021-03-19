/*
file name : data.h
explain : header file have declration of function for data.c and struct of command
*/
#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include"firstpass.h"
#define COMMAND_NAME_MAX_SIZE 5
#define COMMANDS_AMOUNT 16
#define REGISTERS_COUNT 8



typedef struct command {

  char command_name[COMMAND_NAME_MAX_SIZE];
  char funct[5];
  char opcode[5];
  int allowed_operand;
  char source_operands[8];
  char dest_operands[8];

}
command;

void init_commands();
int check_command(char * command, char * line, int argument_counter, int label_flag);
int check_line(char * line);
const char * reg[REGISTERS_COUNT];
void init_registers();
char command_code[13];
int code_opcode_parsing(char * command_code, char * command_func);
int find_adressing_method(char * string, int label_flag, char * command);
int check_command_corrections(int source, int dest, char * command);
int check_for_reg(char * string, int add_to_table_flag);
int check_if_number(char * string);