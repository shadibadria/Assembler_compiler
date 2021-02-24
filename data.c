#include"data.h"

command mycommands[COMMANDS_AMOUNT];



void set_commands(){
    int i=0;
/*setting up commands*/
strcpy(mycommands[i].command_name,"mov\0");
mycommands[i].opcode=0;
mycommands[i].funct=0;
i++;
strcpy(mycommands[i].command_name,"cmp\0");
mycommands[i].opcode=1;
mycommands[i].funct=0;
i++;
strcpy(mycommands[i].command_name,"add\0");
mycommands[i].opcode=2;
mycommands[i].funct=0;
i++;
strcpy(mycommands[i].command_name,"sub\0");
mycommands[i].opcode=2;
mycommands[i].funct=0;
i++;
strcpy(mycommands[i].command_name,"lea\0");
mycommands[i].opcode=4;
mycommands[i].funct=0;
i++;

strcpy(mycommands[i].command_name,"clr\0");
mycommands[i].opcode=5;
mycommands[i].funct=0;
i++;

strcpy(mycommands[i].command_name,"not\0");
mycommands[i].opcode=5;
mycommands[i].funct=0;
i++;

strcpy(mycommands[i].command_name,"inc\0");
mycommands[i].opcode=5;
mycommands[i].funct=0;
i++;

strcpy(mycommands[i].command_name,"dec\0");
mycommands[i].opcode=5;
mycommands[i].funct=0;
i++;

strcpy(mycommands[i].command_name,"jmp\0");
mycommands[i].opcode=9;
mycommands[i].funct=0;
i++;

strcpy(mycommands[i].command_name,"bne\0");
mycommands[i].opcode=9;
mycommands[i].funct=0;
i++;

strcpy(mycommands[i].command_name,"jsr\0");
mycommands[i].opcode=9;
mycommands[i].funct=0;
i++;

strcpy(mycommands[i].command_name,"red\0");
mycommands[i].opcode=12;
mycommands[i].funct=0;
i++;

strcpy(mycommands[i].command_name,"prn\0");
mycommands[i].opcode=13;
mycommands[i].funct=0;
i++;

strcpy(mycommands[i].command_name,"rts\0");
mycommands[i].opcode=14;
mycommands[i].funct=0;
i++;

strcpy(mycommands[i].command_name,"stop\0");
mycommands[i].opcode=15;
mycommands[i].funct=0;



}

int check_command(char *command){

int i=0;
for(i=0;i<COMMANDS_AMOUNT;i++){
    if(strcmp(mycommands[i].command_name,command)==0){
        return mycommands[i].opcode;
    }
}
return 0;
}