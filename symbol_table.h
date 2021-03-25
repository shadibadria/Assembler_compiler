/*
* File name : symbol_table.h
* Header for symbol table , symbol_table.c access .
* Author : Shadi Badria <shadibadria@gmail.com>
*/


/*
struct of the symbol data image
@val key_value - uniqe value 
@val amount - amount 
@val value - IC
@val symbol    - has the label name
@val attribute  - has data type
*/
struct data {
  int    key_value;
  int    amount;
  char * value;
  char * symbol;
  char * attribute;
};

struct data * symbol_table;
int hashcode(int key);
int init_array();
void insert( int value, char * symbol, char * attribute);
void append_entry_tofile(char * filename);
void display();
int size_of_hashtable();
int checkforduplicate(char * symbol);
char * find_label(char * label);
void insert_entry(char * symbol);
void free_symbol_table_memory();