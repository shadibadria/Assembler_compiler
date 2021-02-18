

#define RAM_WORD_SIZE 12
#define ACTION_NAME_MAX_SIZE 4
#define ACTION_TABLE_MAXSIZE 15
#define INSTRUCTION_TABLE_SIZE (sizeof(instruction_table) / sizeof(instruction_descriptor))

void create_action_table();

typedef struct RAMword {/*RAM word in memory*/
	int address;/*address of RAM word in memory*/
	unsigned int dataa : RAM_WORD_SIZE;/*data of the RAM word*/
}RAMword;

typedef struct RAM {/*table of RAM words*/
	int size;/*number of RAM words in the memory*/
	int IC;/*number of instruction words*/
	int DC;/*number of data words*/
	RAMword* word;
}RAM;


typedef struct action_table {

	unsigned int opcode;
	unsigned int funct;
	char action_name[ACTION_NAME_MAX_SIZE];
}action_table;



typedef struct {
    unsigned int immediate:1;
    unsigned int direct:1;
    unsigned int relative:1;
    unsigned int register_direct:1;
} supported_addressing_methods;
	typedef struct {
    const char *name;
    unsigned short opcode;
    unsigned short funct;
    supported_addressing_methods src_op_addressing;
    supported_addressing_methods dst_op_addressing;
} instruction_descriptor;



