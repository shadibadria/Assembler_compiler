
#define COMMAND_NAME_MAX_SIZE 5
#define COMMANDS_AMOUNT 16 
#include<string.h>
#include<stdio.h>
typedef struct command{

char command_name[COMMAND_NAME_MAX_SIZE];
int funct;
int opcode;

}command;


void set_commands();
int check_command(char *command);
int check_if_register(char *string);