/*
* Filename : data.h
* Header for command table and data parsing access .
* Author : Shadi Badria <shadibadria@gmail.com>
*/

#define COMMAND_NAME_MAX_SIZE 5
#define COMMANDS_AMOUNT       16
#define REGISTERS_COUNT       8
#define FUNCT_SIZE            5
#define OPCODE_SIZE           5
#define SOURCE_SIZE           8
#define DEST_SIZE             8
#define BIT_MAX               13

/*
struct of the commands
@val command_name - has the name of the command
@val opcode - has the first 4 bits of the memory
@val funct - has the second 4 bits of the memory
@val allowed_operands   - how many operands must have
@val source_operands  -  source number alowed
@val dest_operands     - dest number alowed
*/
typedef struct command {
  char command_name[COMMAND_NAME_MAX_SIZE];
  char funct[FUNCT_SIZE];
  char opcode[OPCODE_SIZE];
  unsigned int allowed_operand;
  char source_operands[SOURCE_SIZE];
  char dest_operands[DEST_SIZE];
}
command;
char command_code[BIT_MAX];
const char * reg[REGISTERS_COUNT];

void init_command_database();
int check_command(char * command, char * line, int argument_counter, int label_flag,int test);
void init_registers();
int code_opcode_parsing(char * command_code, char * command_func);
int find_adressing_method(char * string, int label_flag, char * command);
int check_command_corrections(int source, int dest, char * command);
int check_for_reg(char * string, int add_to_table_flag);
int check_if_number(char * string);
void command_init(char *command_name,char *command_opcode, char *command_funct, unsigned int allowed_operand_number ,char *source_operand,char *dest_operand,unsigned int index);