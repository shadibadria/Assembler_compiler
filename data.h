

#define RAM_WORD_SIZE 12
#define ACTION_NAME_MAX_SIZE 4
#define ACTION_TABLE_MAXSIZE 15

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



