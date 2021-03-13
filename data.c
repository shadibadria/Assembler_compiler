#include"data.h"

#include"data_image.h"

#include"symbol_table.h"

int extern IC;
int extern index_of_datatable;

command mycommands[COMMANDS_AMOUNT];

/*
add values to the command struct
*/
void init_commands() {
  int i = 0;
  /*setting up commands*/
  strcpy(mycommands[i].command_name, "mov\0");
  strcpy(mycommands[i].opcode, "0000\0");
  strcpy(mycommands[i].funct, "0000\0");

  i++;
  strcpy(mycommands[i].command_name, "cmp\0");
  strcpy(mycommands[i].opcode, "0001\0");
  strcpy(mycommands[i].funct, "0000\0");

  i++;
  strcpy(mycommands[i].command_name, "add\0");
  strcpy(mycommands[i].opcode, "0010\0");
  strcpy(mycommands[i].funct, "1010\0");
  i++;
  strcpy(mycommands[i].command_name, "sub\0");
  strcpy(mycommands[i].opcode, "0010\0");
  strcpy(mycommands[i].funct, "1011\0");

  i++;
  strcpy(mycommands[i].command_name, "lea\0");
  strcpy(mycommands[i].opcode, "0100\0");
  strcpy(mycommands[i].funct, "0000\0");

  i++;

  strcpy(mycommands[i].command_name, "clr\0");
  strcpy(mycommands[i].opcode, "0101\0");
  strcpy(mycommands[i].funct, "1010\0");

  i++;

  strcpy(mycommands[i].command_name, "not\0");
  strcpy(mycommands[i].opcode, "0101\0");
  strcpy(mycommands[i].funct, "1011\0");

  i++;

  strcpy(mycommands[i].command_name, "inc\0");
  strcpy(mycommands[i].opcode, "0101\0");
  strcpy(mycommands[i].funct, "1100\0");

  i++;

  strcpy(mycommands[i].command_name, "dec\0");
  strcpy(mycommands[i].opcode, "0101\0");
  strcpy(mycommands[i].funct, "1101\0");

  i++;

  strcpy(mycommands[i].command_name, "jmp\0");
  strcpy(mycommands[i].opcode, "1001\0");
  strcpy(mycommands[i].funct, "1010\0");

  i++;

  strcpy(mycommands[i].command_name, "bne\0");
  strcpy(mycommands[i].opcode, "1001\0");
  strcpy(mycommands[i].funct, "1011\0");

  i++;

  strcpy(mycommands[i].command_name, "jsr\0");
  strcpy(mycommands[i].opcode, "1001\0");
  strcpy(mycommands[i].funct, "1100\0");
  i++;

  strcpy(mycommands[i].command_name, "red\0");
  strcpy(mycommands[i].opcode, "1100\0");
  strcpy(mycommands[i].funct, "0000\0");
  i++;

  strcpy(mycommands[i].command_name, "prn\0");
  strcpy(mycommands[i].opcode, "1101\0");
  strcpy(mycommands[i].funct, "0000\0");
  i++;

  strcpy(mycommands[i].command_name, "rts\0");
  strcpy(mycommands[i].opcode, "1110\0");
  strcpy(mycommands[i].funct, "0000\0");
  i++;

  strcpy(mycommands[i].command_name, "stop\0");
  strcpy(mycommands[i].opcode, "1111\0");
  strcpy(mycommands[i].funct, "0000\0");

}

/*
check if its command and inc the IC 
*/
int check_command(char * command) {
  int i = 0;

  command[strlen(command)] = '\0';

  for (i = 0; i < COMMANDS_AMOUNT; i++) {
    if (strcmp(mycommands[i].command_name, command) == 0) {
      sprintf(arr[index_of_datatable].Adress, "%04d", IC);

      code_opcode_parsing(mycommands[i].opcode, mycommands[i].funct);
      printf("COMMAND_IC:%d\n", IC);
      IC++;
      /* printf("Command_name :%s\nopcode :%d \nfunct: %d\n ",mycommands[i].command_name,mycommands[i].opcode,mycommands[i].funct);*/
      return 1;
    }
  }
  return 0;
}
/*
opcode parsing 
get command code and command func
then create hex value and insert it to the file

*/
int code_opcode_parsing(char * command_code, char * command_func) {
  int number_temp = 0;
  number_temp = strtol(command_code, NULL, 2);
  printf("firsr 4 bits:%s", command_code);
  sprintf(arr[index_of_datatable].opcode, "%X", number_temp);
  number_temp = strtol(command_func, NULL, 2);
  sprintf(arr[index_of_datatable].funct, "%X", number_temp);
  sprintf(arr[index_of_datatable].TAG, "%c", 'A');
  printf("%s\n", command_func);

  return 1;
}
/*
check command if register / label / number
*/
int check_line(char * line) {

  int i = 0, j = 0;
  char temp[80];
  int comma_flag = 0;
  int number_temp = 0;
  while (line[i] != '\n' && line[i] != '\0') {

    temp[j++] = line[i];
    if (line[i] == ',') {
      temp[j - 1] = '\0';

      comma_flag = 1;
      if (check_for_reg(temp, 1) == 0) {
        printf("xother_IC:%d\n", IC);
        sprintf(arr[index_of_datatable].Adress, "%04d", IC);
 if(strcmp(find_label(temp),"?")==0){
        
      sprintf(arr[index_of_datatable].label_name, "%s",temp );
                    sprintf(arr[index_of_datatable].opcode, "%s","?" );

      }else{
              sprintf(arr[index_of_datatable].opcode, "%s","found" );

      }
        index_of_datatable++;
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
    if (check_for_reg(temp, 1)) {
      return 1;
    } else {

      i = 0;
      while (temp[i] != '\0') {
        if ((temp[i] == '#' && isdigit(temp[i + 1]) != 0) || (temp[i] == '#' && temp[i + 1] == '-' && isdigit(temp[i + 2]) != 0)) {

          printf("number_ic:%d\n", IC);
          sprintf(arr[index_of_datatable].Adress, "%04d", IC);
          sprintf(arr[index_of_datatable].TAG, "%c", 'A');

          memmove(temp, temp + 1, strlen(temp));
          number_temp = strtol(temp, NULL, 10);
          sprintf(arr[index_of_datatable].opcode, "%03X", number_temp);
          if (number_temp < 0) {
            arr[index_of_datatable].opcode[0] = '\0';
            arr[index_of_datatable].funct[4] = '\0';
          }
          index_of_datatable++;
          IC++;
          return 1;
        }
        i++;
      }
      printf("hereother_IC:%d \n", IC);

      sprintf(arr[index_of_datatable].Adress, "%04d", IC);

 if(strcmp(find_label(temp),"?")==0){
        
      sprintf(arr[index_of_datatable].label_name, "%s",temp );
      sprintf(arr[index_of_datatable].opcode, "%s","?" );
      }else{
              sprintf(arr[index_of_datatable].opcode, "%s","found" );

      }
      index_of_datatable++;
      IC++;
    }
  } else {

    i = 0;
    if (check_for_reg(temp, 1) == 1) {
      return 1;
    }
    while (temp[i] != '\0') {
      if ((temp[i] == '#' && isdigit(temp[i + 1]) != 0) || (temp[i] == '#' && temp[i + 1] == '-' && isdigit(temp[i + 2]) != 0)) {
        printf("number_ic:%d\n", IC);
        sprintf(arr[index_of_datatable].Adress, "%04d", IC);
        memmove(temp, temp + 1, strlen(temp));
        printf("NUMBERIS :%s\n", temp);
        sprintf(arr[index_of_datatable].TAG, "%c", 'A');

        number_temp = strtol(temp, NULL, 10);
        printf("tempnum :%d\n", number_temp);

        sprintf(arr[index_of_datatable].opcode, "%03X", number_temp);
        if (number_temp < 0) {
          arr[index_of_datatable].opcode[0] = '\0';
          arr[index_of_datatable].funct[4] = '\0';
        }

        index_of_datatable++;
        IC++;
        return 1;
      }

      i++;
    }
    i = 0;
    remove_space_tabs(temp);
    if (temp[0] != '\0') {
      printf("other_IC:%d istemp:%s\n", IC, temp);
      sprintf(arr[index_of_datatable].Adress, "%04d", IC);
      if(strcmp(find_label(temp),"?")==0){
        
      sprintf(arr[index_of_datatable].label_name, "%s",temp );
      sprintf(arr[index_of_datatable].opcode, "%s","?" );
      }else{
              sprintf(arr[index_of_datatable].opcode, "%s","found" );

      }
      index_of_datatable++;
      IC++;
    }

  }

  return 0;
}
/*
check if value is register
*/
int check_for_reg(char * string, int add_to_table_flag) {
  int i = 0;
  char register_maker[13] = {
    "000000000000\n"
  };
  int number_temp = 0;
  register_maker[13] = '\0';
  for (i = 0; i < REGISTERS_COUNT; i++) {
    if (!strcmp(reg[i], string)) {
      register_maker[11 - i] = '1';

      if (add_to_table_flag == 1) {
        printf("Register_IC:%d\n", IC);
        sprintf(arr[index_of_datatable].Adress, "%04d", IC);
        IC++;

        strncpy(arr[index_of_datatable].opcode, register_maker, 4);
        number_temp = strtol(arr[index_of_datatable].opcode, NULL, 2);
        sprintf(arr[index_of_datatable].opcode, "%X", number_temp);

        strncpy(arr[index_of_datatable].funct, register_maker + 4, 4);
        number_temp = strtol(arr[index_of_datatable].funct, NULL, 2);
        sprintf(arr[index_of_datatable].funct, "%X", number_temp);

        strncpy(arr[index_of_datatable].adress_method, register_maker + 8, 12);
        number_temp = strtol(arr[index_of_datatable].adress_method, NULL, 2);
        sprintf(arr[index_of_datatable].adress_method, "%X", number_temp);
        sprintf(arr[index_of_datatable].TAG, "%c", 'A');

        index_of_datatable++;
        return 1;
      }

      return 1;
    }
  }
  return 0;
}
/*
init register table
*/
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