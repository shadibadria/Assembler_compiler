#include"data.h"
#include"data_image.h"
int extern IC;
int extern index_of_datatable;

command mycommands[COMMANDS_AMOUNT];

void init_commands() {
  int i = 0;
  /*setting up commands*/
  strcpy(mycommands[i].command_name, "mov\0");
  mycommands[i].opcode = 0;
  mycommands[i].funct = 0;
  i++;
  strcpy(mycommands[i].command_name, "cmp\0");
  mycommands[i].opcode = 1;
  mycommands[i].funct = 0;
  i++;
  strcpy(mycommands[i].command_name, "add\0");
  mycommands[i].opcode = 2;
  mycommands[i].funct = 10;
  i++;
  strcpy(mycommands[i].command_name, "sub\0");
  mycommands[i].opcode = 2;
  mycommands[i].funct = 11;
  i++;
  strcpy(mycommands[i].command_name, "lea\0");
  mycommands[i].opcode = 4;
  mycommands[i].funct = 0;
  i++;

  strcpy(mycommands[i].command_name, "clr\0");
  mycommands[i].opcode = 5;
  mycommands[i].funct = 10;
  i++;

  strcpy(mycommands[i].command_name, "not\0");
  mycommands[i].opcode = 5;
  mycommands[i].funct = 11;
  i++;

  strcpy(mycommands[i].command_name, "inc\0");
  mycommands[i].opcode = 5;
  mycommands[i].funct = 12;
  i++;

  strcpy(mycommands[i].command_name, "dec\0");
  mycommands[i].opcode = 5;
  mycommands[i].funct = 13;
  i++;

  strcpy(mycommands[i].command_name, "jmp\0");
  mycommands[i].opcode = 9;
  mycommands[i].funct = 10;
  i++;

  strcpy(mycommands[i].command_name, "bne\0");
  mycommands[i].opcode = 9;
  mycommands[i].funct = 11;
  i++;

  strcpy(mycommands[i].command_name, "jsr\0");
  mycommands[i].opcode = 9;
  mycommands[i].funct = 12;
  i++;

  strcpy(mycommands[i].command_name, "red\0");
  mycommands[i].opcode = 12;
  mycommands[i].funct = 0;
  i++;

  strcpy(mycommands[i].command_name, "prn\0");
  mycommands[i].opcode = 13;
  mycommands[i].funct = 0;
  i++;

  strcpy(mycommands[i].command_name, "rts\0");
  mycommands[i].opcode = 14;
  mycommands[i].funct = 0;
  i++;

  strcpy(mycommands[i].command_name, "stop\0");
  mycommands[i].opcode = 15;
  mycommands[i].funct = 0;

}

int check_command(char * command) {
  int i = 0;
  command[strlen(command)] = '\0';

  for (i = 0; i < COMMANDS_AMOUNT; i++) {
    if (strcmp(mycommands[i].command_name, command) == 0) {
      sprintf(arr[index_of_datatable].Adress,"%d",IC);
      
          sprintf(arr[index_of_datatable].code,"%d",mycommands[i].opcode);

        index_of_datatable++;
        printf("COMMAND_IC:%d\n", IC);
        IC++;
      /* printf("Command_name :%s\nopcode :%d \nfunct: %d\n ",mycommands[i].command_name,mycommands[i].opcode,mycommands[i].funct);*/
      return 1;
    }
  }
  return 0;
}

int check_if_register(char * line) {

  int i = 0, j = 0;
  char temp[80];
  int comma_flag = 0;
  while (line[i] != '\n' && line[i] != '\0') {

    temp[j++] = line[i];
    if (line[i] == ',') {
      temp[j - 1] = '\0';

      comma_flag = 1;
      if (check_for_reg(temp) == 0) {
        printf("xother_IC:%d\n", IC);
         sprintf(arr[index_of_datatable].Adress,"%d",IC);
  index_of_datatable++;
        IC++;

      }
      temp[0] = '\0';
      j = 0;
    }

    i++;
  }

  temp[j] = '\0';

  if (comma_flag == 1) {
    if (check_for_reg(temp)) {
      return 1;
    } else {

      i = 0;
      while (temp[i] != '\0') {
        if ((temp[i] == '#' && isdigit(temp[i + 1]) != 0) || (temp[i] == '#' && temp[i + 1] == '-' && isdigit(temp[i + 2]) != 0)) {
          printf("number_ic:%d\n", IC);
  sprintf(arr[index_of_datatable].Adress,"%d",IC);
  index_of_datatable++;
          IC++;
          return 1;
        }
        i++;
      }
      printf("other_IC:%d \n", IC);
        sprintf(arr[index_of_datatable].Adress,"%d",IC);
  index_of_datatable++;
      IC++;
    }
  } else {

    i = 0;
    if (check_for_reg(temp) == 1) {
      return 1;
    }
    while (temp[i] != '\0') {
      if ((temp[i] == '#' && isdigit(temp[i + 1]) != 0) || (temp[i] == '#' && temp[i + 1] == '-' && isdigit(temp[i + 2]) != 0)) {
        printf("number_ic:%d\n", IC);
  sprintf(arr[index_of_datatable].Adress,"%d",IC);
  index_of_datatable++;
        IC++;
        return 1;
      }

      i++;
    }
    i = 0;
    remove_space_tabs(temp);
    if (temp[0] != '\0') {
      printf("other_IC:%d is:%s\n", IC, temp);
        sprintf(arr[index_of_datatable].Adress,"%d",IC);
  index_of_datatable++;
      IC++;
    }

  }

  return 0;
}

int check_for_reg(char * string) {
  int i = 0;

  for (i = 0; i < REGISTERS_COUNT; i++) {
    if (!strcmp(reg[i], string)) {
      printf("Register_IC:%d\n", IC);
  sprintf(arr[index_of_datatable].Adress,"%d",IC);
  index_of_datatable++;
      IC++;

      return 1;
    }
  }
  return 0;
}
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