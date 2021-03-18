/*
file name : data.c
explain: all function of data (commands , datat ,string )
*/

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
  mycommands[i].allowed_operand=2;

  i++;
  strcpy(mycommands[i].command_name, "cmp\0");
  strcpy(mycommands[i].opcode, "0001\0");
  strcpy(mycommands[i].funct, "0000\0");
  mycommands[i].allowed_operand=2;

  i++;
  strcpy(mycommands[i].command_name, "add\0");
  strcpy(mycommands[i].opcode, "0010\0");
  strcpy(mycommands[i].funct, "1010\0");
    mycommands[i].allowed_operand=2;

  i++;
  strcpy(mycommands[i].command_name, "sub\0");
  strcpy(mycommands[i].opcode, "0010\0");
  strcpy(mycommands[i].funct, "1011\0");
    mycommands[i].allowed_operand=2;


  i++;
  strcpy(mycommands[i].command_name, "lea\0");
  strcpy(mycommands[i].opcode, "0100\0");
  strcpy(mycommands[i].funct, "0000\0");
    mycommands[i].allowed_operand=2;


  i++;

  strcpy(mycommands[i].command_name, "clr\0");
  strcpy(mycommands[i].opcode, "0101\0");
  strcpy(mycommands[i].funct, "1010\0");
    mycommands[i].allowed_operand=1;
  i++;

  strcpy(mycommands[i].command_name, "not\0");
  strcpy(mycommands[i].opcode, "0101\0");
  strcpy(mycommands[i].funct, "1011\0");
    mycommands[i].allowed_operand=1;

  i++;

  strcpy(mycommands[i].command_name, "inc\0");
  strcpy(mycommands[i].opcode, "0101\0");
  strcpy(mycommands[i].funct, "1100\0");
  mycommands[i].allowed_operand=1;
  i++;

  strcpy(mycommands[i].command_name, "dec\0");
  strcpy(mycommands[i].opcode, "0101\0");
  strcpy(mycommands[i].funct, "1101\0");
  mycommands[i].allowed_operand=1;

  i++;

  strcpy(mycommands[i].command_name, "jmp\0");
  strcpy(mycommands[i].opcode, "1001\0");
  strcpy(mycommands[i].funct, "1010\0");
  mycommands[i].allowed_operand=1;

  i++;

  strcpy(mycommands[i].command_name, "bne\0");
  strcpy(mycommands[i].opcode, "1001\0");
  strcpy(mycommands[i].funct, "1011\0");
  mycommands[i].allowed_operand=1;

  i++;

  strcpy(mycommands[i].command_name, "jsr\0");
  strcpy(mycommands[i].opcode, "1001\0");
  strcpy(mycommands[i].funct, "1100\0");
    mycommands[i].allowed_operand=1;

  i++;

  strcpy(mycommands[i].command_name, "red\0");
  strcpy(mycommands[i].opcode, "1100\0");
  strcpy(mycommands[i].funct, "0000\0");
    mycommands[i].allowed_operand=1;

  i++;

  strcpy(mycommands[i].command_name, "prn\0");
  strcpy(mycommands[i].opcode, "1101\0");
  strcpy(mycommands[i].funct, "0000\0");
    mycommands[i].allowed_operand=1;

  i++;

  strcpy(mycommands[i].command_name, "rts\0");
  strcpy(mycommands[i].opcode, "1110\0");
  strcpy(mycommands[i].funct, "0000\0");
    mycommands[i].allowed_operand=1;

  i++;

  strcpy(mycommands[i].command_name, "stop\0");
  strcpy(mycommands[i].opcode, "1111\0");
  strcpy(mycommands[i].funct, "0000\0");
  mycommands[i].allowed_operand=0;

}

/*
check if its command and inc the IC 
*/
int check_command(char * command,char *line,int argument_counter,int label_flag) {
  int i = 0;
  int coma_flag=0;
  

  printf("CHECK:%d\n",argument_counter);
  if(command[strlen(command)-1]==','){
    command[strlen(command)-1]='\0';
    coma_flag=1;
  }
i=strlen(command);
 while(line[i]==' '||line[i]=='\t'){
   
   i++;
 }
 if(line[i]==','){
   printf("ERROR:to many commas\n");
 }
 

  command[strlen(command)] = '\0';
  for (i = 0; i < COMMANDS_AMOUNT; i++) {
    if (strcmp(mycommands[i].command_name, command) == 0) {
        if(mycommands[i].allowed_operand!=argument_counter){
          printf("ERROR: not correct operands\n");
        }
      if(coma_flag==1){
        printf("ERROR:to many commas\n");
      }
      sprintf(arr[index_of_datatable].Adress, "%04d", IC);
      printf("COMMAND_IC:%d\n", IC);

      IC++;
            printf("lineeeee::%s\n", line);

      code_opcode_parsing(mycommands[i].opcode, mycommands[i].funct);
      
          find_adressing_method(line,label_flag,command);

      return 1;
    }
  }
  return 0;
}

/*
find adress method and create the bits of it 

*/
int find_adressing_method(char * string, int label_flag,char * command) {

  int i = 0;
  char temp[80];
  char * tempstring;
  int dest,source;
  char last_bits[5] = "0000\n";
  int j = 0, k = 0, commaflag = 0, number_temp = 0;
  printf("HERE:%s\n",string);
  tempstring = (char * ) malloc(strlen(string) * sizeof(char));
  if (tempstring == NULL) {
    printf("Something Went Wrong no memory\n");
    return 0;

  }
  strcpy(tempstring, string);
  tempstring[strlen(tempstring)] = '\0';
  if (label_flag == 1) {
    while (tempstring[i] != '\0') {
      if (tempstring[i] == ':') {

        break;
      }
      i++;
    }
    i++;
  }
  remove_spaces_from_index(tempstring, i);
  tempstring[strlen(tempstring)] = '\0';

  i = 0;
  while (tempstring[i] != '\0') {
    if (tempstring[i] == ' ' || tempstring[i] == '\t') {
      break;
    }
    i++;
  }
  remove_spaces_from_index(tempstring, i);
  
  i = 0;
  tempstring[strlen(tempstring)] = '\0';
  while(tempstring[i]!='\0'){
    temp[j++]=tempstring[i];
    if(tempstring[i]==','){
      commaflag=1;

      break;
    }
    i++;
  }
      i++;

  if(commaflag==0){

    if (check_for_reg(tempstring, 0) == 1) {
      last_bits[k++] = '0';
      last_bits[k++] = '0';
      last_bits[k++] = '1';
      last_bits[k++] = '1';
    } else
    if (tempstring[0] == '#') {
      last_bits[k++] = '0';
      last_bits[k++] = '0';
      last_bits[k++] = '0';
      last_bits[k++] = '0';

    } else
    if (tempstring[0] == '%') {
      last_bits[k++] = '0';
      last_bits[k++] = '0';
      last_bits[k++] = '1';
      last_bits[k++] = '0';
    } else {
      last_bits[k++] = '0';
      last_bits[k++] = '0';
      last_bits[k++] = '0';
      last_bits[k++] = '1';
    }

  }else{
    temp[j-1]='\0';
      j=0;

     if (check_for_reg(temp, 0) == 1) {

      last_bits[k++] = '1';
      last_bits[k++] = '1';
    } else
    if (temp[0] == '#') {
      last_bits[k++] = '0';
      last_bits[k++] = '0';
      

    } else
    if (temp[0] == '%') {
    
      last_bits[k++] = '1';
      last_bits[k++] = '0';
    } else {
     
      last_bits[k++] = '0';
      last_bits[k++] = '1';
    }
  j=0;

    while(tempstring[i]!='\0'){

      temp[j++]=tempstring[i];
      i++;
    }
          temp[j]='\0';
    
    if (check_for_reg(temp, 0) == 1) {
    
      last_bits[k++] = '1';
      last_bits[k++] = '1';
    } else
    if (temp[0] == '#') {
      last_bits[k++] = '0';
      last_bits[k++] = '0';
 

    } else
    if (temp[0] == '%') {
     
      last_bits[k++] = '1';
      last_bits[k++] = '0';
    } else {

      last_bits[k++] = '0';
      last_bits[k++] = '1';
    }

  }
    last_bits[5] = '\0';
      last_bits[5] = '\0';

  
  free(tempstring);

  
  number_temp = strtol(last_bits, NULL, 2);
  printf("Lastbits:%s\n", last_bits);
  temp[0]=last_bits[0];
  temp[1]=last_bits[1];
  temp[3]='\0';
  source = strtol(temp, NULL, 2);
  temp[0]=last_bits[2];
  temp[1]=last_bits[3];
  temp[2]='\0';
  dest = strtol(temp, NULL, 2);
          printf("*******************command is :%X \n",number_temp);

  sprintf(arr[index_of_datatable].adress_method, "%X", number_temp);
  index_of_datatable++;
    check_command_corrections(source,dest,command);

  return 1;
}
int  check_command_corrections(int source,int dest,char *command){
  int i=0;
  for (i = 0; i < COMMANDS_AMOUNT; i++) {
    if (strcmp(mycommands[i].command_name, command) == 0) {
   
        printf("command is :%s , source is :%d , dest is :%d\n",command,source,dest);
      return 1;
    }
  }


return 1;
}
/*
opcode parsing 
get command code and command func
then create hex value and insert it to the file

*/
int code_opcode_parsing(char * command_code, char * command_func) {

  int number_temp = 0;
  

  if (strcmp(command_code, "1111") == 0) {
    number_temp = strtol(command_code, NULL, 2);
    printf("firsr 4 bits:%s", command_code);
    sprintf(arr[index_of_datatable].opcode, "%01X", number_temp);
    number_temp = strtol(command_func, NULL, 2);
    sprintf(arr[index_of_datatable].funct, "%02X", number_temp);
    sprintf(arr[index_of_datatable].TAG, "%c", 'A');
    printf("%s\n", command_func);
    index_of_datatable++;

    return 0;
  }
  printf("***********commandcode:%s\n",command_code);
    printf("***********commandfunct:%s\n",command_code);
  printf("COMMAND:%s\n", command_code);
  number_temp = strtol(command_code, NULL, 2);
  printf("firsr 4 bits:%s", command_code);
  sprintf(arr[index_of_datatable].opcode, "%X", number_temp);
  number_temp = strtol(command_func, NULL, 2);
  sprintf(arr[index_of_datatable].funct, "%X", number_temp);
  sprintf(arr[index_of_datatable].TAG, "%c", 'A');
  printf("%s\n", command_func);

  return 0;
}
int check_if_number(char *string){
  int i=0;
  int number_temp;
   while (string[i] != '\0') {
      if ((string[i] == '#' && isdigit(string[i + 1]) != 0) || (string[i] == '#' && string[i + 1] == '-' && isdigit(string[i + 2]) != 0)) {
        printf("number_ic:%d\n", IC);
        sprintf(arr[index_of_datatable].Adress, "%04d", IC);
        memmove(string, string + 1, strlen(string));
        printf("NUMBERIS :%s\n", string);
        sprintf(arr[index_of_datatable].TAG, "%c", 'A');

        number_temp = strtol(string, NULL, 10);
        printf("number_temp :%d\n", number_temp);
        if(number_temp>2047||number_temp<-2047){
          printf("ERROR: number must be between -2047 to 2047\n");
        }
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
    return 0;
}
/*
check command if register / label / number
*/
int check_line(char * line) {

  int i = 0, j = 0;
  char temp[80];
  int comma_flag = 0;

    if(strcmp("stop",line)==0){
      return 1;
    }


  while (line[i] != '\n' && line[i] != '\0') {
 
    temp[j++] = line[i];

    if (line[i] == ',') {
      comma_flag=1;
      temp[j - 1] = '\0';
      if(check_if_number(temp)==1){
        break;
       }
       if(check_for_reg(temp,1)==1){
         break;
       }
       printf("xother_IC:%d\n", IC);
        sprintf(arr[index_of_datatable].Adress, "%04d", IC);
        if (strcmp(find_label(temp), "?") == 0) {
          sprintf(arr[index_of_datatable].label_name, "%s", temp);
          sprintf(arr[index_of_datatable].opcode, "%s", "?");

        } 
        index_of_datatable++;
        IC++;
        break;
        }
        i++;
    }


  if (comma_flag == 0) {
      line[strlen(line)]='\0';
    if(check_if_number(line)==1) return 1;
    if(check_for_reg(line,1)) return 1;
     printf("hereother_IC:%d \n", IC);
         sprintf(arr[index_of_datatable].Adress, "%04d", IC);
         printf("tempppp:%s*******\n",line);


      if (strcmp(find_label(line), "?") == 0) {

        sprintf(arr[index_of_datatable].label_name, "%s", line);
        sprintf(arr[index_of_datatable].opcode, "%s", "?");
      } 
      index_of_datatable++;
      IC++;
   return 0;
  }
    i++;
       temp[0] = '\0';
       j=0;
      while(line[i]!='\0'){

          temp[j++]=line[i];
        i++;
      }
        temp[j]='\0';

        if(check_if_number(temp)==1)
          return 1;
        if(check_for_reg(temp,1)==1)
          return 1;

         printf("hereother_IC:%d \n", IC);
         sprintf(arr[index_of_datatable].Adress, "%04d", IC);
         printf("tempppp:%s*******\n",temp);

      if (strcmp(find_label(temp), "?") == 0) {

        sprintf(arr[index_of_datatable].label_name, "%s", temp);
        sprintf(arr[index_of_datatable].opcode, "%s", "?");
      } 
      index_of_datatable++;
      IC++;

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
