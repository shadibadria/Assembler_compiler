
#define COMMAND_NAME_MAX_SIZE 5
#define COMMANDS_AMOUNT 16 
#define REGISTERS_COUNT 8
#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include"firstpass.h"
typedef struct command{

char command_name[COMMAND_NAME_MAX_SIZE];
int funct;
int opcode;

}command;


void init_commands();
int check_command(char *command);
int check_if_register(char *string);
int check_for_reg(char *string);
const char *reg[REGISTERS_COUNT];
void init_registers();