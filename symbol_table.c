/*
* File Name : symbol_table.c
* This file provide all the  functions for symbol table .
* Author : Shadi Badria <shadibadria@gmail.com>
*/
#include <math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"symbol_table.h"


int capacity_table = 1;
int symbol_table_size = 0;

/*
function hashcode - create randome code
@param key - uniqe number
@return int
*/
int hashcode(int key) {
  return (key % capacity_table);
}

/*
function init_array -  init hash table array using malloc 
@param none
@return int
*/
int init_symbol_table() {
  symbol_table = (struct data * ) malloc(capacity_table * sizeof(struct data));
  if (symbol_table == NULL) {
    printf("ERROR: something went wrong while trying to use malloc at symboltable.c\n");
    return 0;
  }
  symbol_table[0].amount = 0;
  memset(symbol_table, 0, capacity_table * sizeof(struct data));
  return 1;
}

/*
function insert_entry - insert entry labels after second pass to the labels 
at the symbol table
@param symbol - symbol (label)
@return void
*/
void insert_entry(char * symbol) {
  int i;

  for (i = 0; i < symbol_table_size; i++) {
    if (strcmp(symbol_table[i].symbol, symbol) == 0) {
      symbol_table[i].attribute = (char * ) realloc(symbol_table[i].attribute, 11);
      if (symbol_table[i].attribute == NULL) {
        printf("Something Went Wrong no memory\n");
        exit(1);
      }
      strcat(symbol_table[i].attribute, ",entry");
    }
  }
}

/*
 function insert -   insert a key in the hash table
 @param key  - uniqe value
 @param value - value of the IC
 @param symbol - label
 @param attribute - type ( extern , entry ...)
 @return void
 */
void insert( int value, char * symbol, char * attribute) {
  int index = hashcode(symbol_table_size);

  capacity_table++;
  symbol_table = (struct data * ) realloc(symbol_table, capacity_table * sizeof(struct data));
  symbol_table[index].amount = 0;
  if (symbol_table == NULL) {
    printf("ERROR: using realloc at symbol_table.c\n");
    exit(0);
  }
  if (symbol_table[index].amount == 0) {
    /*  key not present, insert it  */
    symbol_table[index].key_value = symbol_table_size;
    symbol_table[index].amount = 1;
    /*insert value */
    if (value == 0) {
      symbol_table[index].value = (char * ) malloc(5 * sizeof(char));
      memset(symbol_table[index].value, 0, 5 * sizeof(char));
    } else {
      symbol_table[index].value = (char * ) malloc(((floor(log10(abs(value)))) + 5) * sizeof(char));
      memset(symbol_table[index].value, 0, ((floor(log10(abs(value)))) + 5) * sizeof(char));
    }
    if (symbol_table[index].value == NULL) {
      printf("Something Went Wrong no memory at  symbol_table.c\n");
      exit(1);
    }
    sprintf(symbol_table[index].value, "%04d", value);
    /*insert symbol*/
    symbol_table[index].symbol = (char * ) malloc((strlen(symbol) + 1) * sizeof(char));
    if (symbol_table[index].symbol == NULL) {
      printf("Something Went Wrong no memory\n");
      exit(1);
    }
    memset(symbol_table[index].symbol, 0, (strlen(symbol) + 1) * sizeof(char));
    if (symbol[strlen(symbol) - 1] == ':') {
      symbol[strlen(symbol) - 1] = '\0';
    } else {
      symbol[strlen(symbol)] = '\0';
    }
    strcpy(symbol_table[index].symbol, symbol);
    
    /*insert attribute */
    symbol_table[index].attribute = (char * ) malloc((strlen(attribute) + 3) * sizeof(char));
    if (symbol_table[index].attribute == NULL) {
      printf("Something Went Wrong no memory\n");
      exit(1);
    }
    strcpy(symbol_table[index].attribute, attribute);
    symbol_table_size++;
  } else if (symbol_table[index].key_value == symbol_table_size) {
    /*  updating already existing key  */
    symbol_table[index].amount += 1;
  } else {
    /*  key cannot be insert as the index is already containing some other key  */
    printf("\n ELEMENT CANNOT BE INSERTED \n");
  }
}

/*
 function  display - to display all the elements of a hash table( use it for testing only)
 @param none
 @return void
*/
void display() {
  int i;
  for (i = 0; i < symbol_table_size; i++) {
    if (symbol_table[i].amount == 0) {} else {
      printf("\n--------------------\nkey= %d \nvalue = %s\nsymbol = %s \nattr= %s\n--------------------\n", symbol_table[i].key_value, symbol_table[i].value, symbol_table[i].symbol, symbol_table[i].attribute);
    }
  }
}
/*
function find_label find label at the symbol table
@param label  
@return char *
*/
char * find_label(char * label) {
  int i;
  for (i = 0; i < symbol_table_size; i++) {
    if (strcmp(symbol_table[i].symbol, label) !=0) {
      return "?";
    }
  }
  return "found";
}

/*
function  checkforduplicate  check for duplicate at the symbol table 
@param symbol 
@return int
*/
int checkforduplicate(char * symbol) {
  int i;

  for (i = 0; i < symbol_table_size; i++) {
    if (strcmp(symbol_table[i].symbol, symbol) == 0) {
          if(strcmp(symbol_table[i].attribute,"external")==0){
            return 1;
          }
      return 0;
    }
  }
  return 1;
}
/*
function size_of_hashtable - size hashtable
@param none
@return int
*/
int size_of_hashtable() {
  return symbol_table_size;
}
/*
function free_symbol_table_memory - free memory of hashtable
@param none
@return void
*/
void free_symbol_table_memory() {
  int i = 0;
  for (i = 0; i < symbol_table_size; i++) {
    free(symbol_table[i].symbol);
    free(symbol_table[i].value);
    free(symbol_table[i].attribute);
  }
  free(symbol_table);
   capacity_table = 1;
symbol_table_size = 0;
}