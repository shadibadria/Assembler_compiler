#include"data.h"
action_table table[ACTION_TABLE_MAXSIZE];

/*check if command is correct*/
void create_action_table() {
   
	int i = 0;
	for(i=0;i<15;i++)
	table[i].opcode = i;

	for (i = 0; i < 15; i++)
		printf("%d\n",table[i].opcode);
}


