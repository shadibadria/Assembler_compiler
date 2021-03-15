/*
file name : symbol_table.h
explain: header file that has declrations of symbol_table.c
it has hash struct
*/

#include<stdio.h>

#include<stdlib.h>

#include<string.h>

struct data {
  int key_value;
  int amount; /*if value is more than 1 (same adress twice)*/
  char *value;
  char *symbol;
  char *attribute;
};

struct data * array;

int hashcode(int key);
int init_array();
void insert(int key, int value, char * symbol, char * attribute);
void append_entry_tofile(char * filename);
void display();
int size_of_hashtable();
int checkforduplicate(char * symbol);
char * find_label(char * label);
void insert_entry(char * symbol);
void free_symbol_table_memory();