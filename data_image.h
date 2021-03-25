/*
* File name : data_image.h
* Header for data_image table access.
* Author : Shadi Badria <shadibadria@gmail.com>
*/

#define SIZEOFCODE     5
#define SIZEOFADRESS   5
#define MAX_Data_TABLE 4095
#define TAG_SIZE       2

/*
struct of the data image
@val adress - has the adress of the program IC
@val opcode - has the first 4 bits of the memory
@val funct - has the second 4 bits of the memory
@val TAG    - has the Tag name of the type (A,R,E)
@val adress_method  - has the adress method 
@val label_name     - has the label name (helps with second pass)
*/
typedef struct data_image {
  char Adress[SIZEOFADRESS];
  char opcode[SIZEOFCODE];
  char funct[SIZEOFCODE];
  char TAG[TAG_SIZE];
  char adress_method[SIZEOFCODE];
  char label_name[SIZEOFCODE];
}
data_image;

data_image data_table[MAX_Data_TABLE];
void append_command_to_file(char * filename, data_image data);
void append_register_to_file(char * filename, char * register_number);
void append_size_to_file(char *filename ,int instruct_size,int data_size);
void init_data_table();