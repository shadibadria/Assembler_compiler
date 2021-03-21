/*
file name : symbol_table.c
explain: this file has all the symbol table function
symbol table uses HASH TABLE 
*/

#include"symbol_table.h"

#include "math.h"

int capacity_table = 1;
int size_table = 0;

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
int init_array() {
  array = (struct data * ) malloc(capacity_table * sizeof(struct data));
  if (array == NULL) {
    printf("ERROR: something went wrong while trying to use malloc at symboltable.c\n");
    return 0;
  }
  array[0].amount = 0;
  memset(array, 0, capacity_table * sizeof(struct data));
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

  for (i = 0; i < size_table; i++) {
    if (strcmp(array[i].symbol, symbol) == 0) {
      array[i].attribute = (char * ) realloc(array[i].attribute, 7);
      if (array[i].attribute == NULL) {
        printf("Something Went Wrong no memory\n");
        exit(1);
      }
      strcat(array[i].attribute, ",entry");
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
void insert(int key, int value, char * symbol, char * attribute) {
  int index = hashcode(key);

  capacity_table++;
  array = (struct data * ) realloc(array, capacity_table * sizeof(struct data));
  array[index].amount = 0;
  if (array == NULL) {
    printf("ERROR: using realloc at symbol_table.c\n");
    exit(0);
  }
  if (array[index].amount == 0) {
    /*  key not present, insert it  */
    array[index].key_value = key;
    array[index].amount = 1;
    /*insert value */
    if (value == 0) {
      array[index].value = (char * ) malloc(4 * sizeof(char));
      memset(array[index].value, 0, 4 * sizeof(char));
    } else {
      array[index].value = (char * ) malloc(((floor(log10(abs(value)))) + 6) * sizeof(char));
      memset(array[index].value, 0, ((floor(log10(abs(value)))) + 6) * sizeof(char));
    }
    if (array[index].value == NULL) {
      printf("Something Went Wrong no memory at  symbol_table.c\n");
      exit(1);
    }
    sprintf(array[index].value, "%04d", value);
    /*insert symbol*/
    array[index].symbol = (char * ) malloc((strlen(symbol) + 1) * sizeof(char));
    if (array[index].symbol == NULL) {
      printf("Something Went Wrong no memory\n");
      exit(1);
    }
    memset(array[index].symbol, 0, (strlen(symbol) + 1) * sizeof(char));
    if (symbol[strlen(symbol) - 1] == ':') {
      symbol[strlen(symbol) - 1] = '\0';
    } else {
      symbol[strlen(symbol)] = '\0';
    }
    strcpy(array[index].symbol, symbol);
    printf("LABEL:%s\n", array[index].symbol);
    /*insert attribute */
    array[index].attribute = (char * ) malloc((strlen(attribute) + 3) * sizeof(char));
    if (array[index].attribute == NULL) {
      printf("Something Went Wrong no memory\n");
      exit(1);
    }
    strcpy(array[index].attribute, attribute);
    size_table++;
  } else if (array[index].key_value == key) {
    /*  updating already existing key  */
    array[index].amount += 1;
  } else {
    /*  key cannot be insert as the index is already containing some other key  */
    printf("\n ELEMENT CANNOT BE INSERTED \n");
  }
}

/*
 function  display - to display all the elements of a hash table(testing only)
 @param none
 @return void
*/
void display() {
  int i;
  for (i = 0; i < size_table; i++) {
    if (array[i].amount == 0) {} else {
      printf("\n--------------------\nkey= %d \nvalue = %s\nsymbol = %s \nattr= %s\n--------------------\n", array[i].key_value, array[i].value, array[i].symbol, array[i].attribute);
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
  for (i = 0; i < size_table; i++) {
    if (strcmp(array[i].symbol, label) == -1) {
      return "found";
    }
  }
  return "?";
}
/*
function  checkforduplicate  check for duplicate at the symbol table 
@param symbol 
@return int
*/
int checkforduplicate(char * symbol) {
  int i;
  for (i = 0; i < size_table; i++) {
    if (strcmp(array[i].symbol, symbol) == 0) {
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
  return size_table;
}
/*
function free_symbol_table_memory - free memory of hashtable
@param none
@return void
*/
void free_symbol_table_memory() {
  int i = 0;
  for (i = 0; i < size_table; i++) {
    free(array[i].symbol);
    free(array[i].value);
    free(array[i].attribute);
  }
  free(array);
}