/*
file name : symbol_table.c
explain: this file has all the symbol table function
symbol table uses HASH TABLE 
*/

#include"symbol_table.h"

int capacity_table = 100;
int size_table = 25;
FILE * file_pointer;
int hashcode(int key) {
  return (key % capacity_table);
}

/*
init hash table array using malloc 
*/
void init_array() {
  int i;
  array = (struct data * ) malloc(capacity_table * sizeof(struct data));
  for (i = 0; i < capacity_table; i++) {

  }
}


/*append to file function*/

void append_entry_tofile(char * filename) {
  int i=0;
  file_pointer = fopen(filename, "a");
  if (file_pointer == NULL) {
    printf("error creating file %s \n", filename);
    exit(0);
  }

    for(i=0;i<100;i++){
        if(strstr(array[i].attribute,"entry")!=NULL){
      fputs(array[i].symbol, file_pointer);
      fputs("      ", file_pointer);
            fputs(array[i].value, file_pointer);

  fputs("\n", file_pointer);

        }
    }

}
/*
insert entry labels after second pass to the labels 
at the symbol table
*/
void insert_entry(char * symbol){

int i;

  for (i = 0; i < capacity_table; i++) {
    if (strcmp(array[i].symbol ,symbol)==0) {
            printf("STR:%s\n",symbol);

      strcat(array[i].attribute,",entry" );
    }
}
}
/* to insert a key in the hash table */
void insert(int key, int value, char * symbol, char * attribute) {
  int index = hashcode(key);
  if (array[index].amount == 0) {
    /*  key not present, insert it  */
    array[index].key_value = key;
    array[index].amount = 1;

    sprintf(array[index].value,"%04d",value);
    strcpy(array[index].symbol, symbol);
    strcpy(array[index].attribute, attribute);
    size_table++;
   printf("\n Key (%d) has been inserted \n", key);
  } else if (array[index].key_value == key) {
    /*  updating already existing key  */
    printf("\n Key (%d) already present, hence updating its value \n", key);
    array[index].amount += 1;
  } else {
    /*  key cannot be insert as the index is already containing some other key  */
    printf("\n ELEMENT CANNOT BE INSERTED \n");
  }
}

/* to display all the elements of a hash table */
void display() {
  int i;
  for (i = 0; i < capacity_table; i++) {
    if (array[i].amount == 0) {

    } else {
      printf("\n--------------------\nkey= %d \nvalue = %s\nsymbol = %s \nattr= %s\n--------------------\n", array[i].key_value, array[i].value, array[i].symbol, array[i].attribute);
    }
  }
}
/*
find label at the symbol table
*/
char * find_label(char * label) {
  int i;
  for (i = 0; i < capacity_table; i++) {
    if (strcmp(array[i].symbol, label) == -1) {

      return "found";
    }
  }
  return "?";
}
/*
check for duplicate at the symbol table 
*/
int checkforduplicate(char * symbol) {

  int i;
        printf("Symbol :%s\n",symbol);

  for (i = 0; i < capacity_table; i++) {
    if (strcmp(array[i].symbol,symbol)==0) {
      printf("Symbol Already Exsist \n");
      return 0;
    }

  }
  return 1;
}
/*get the size of the symbol table*/
int size_of_hashtable() {
  return size_table;
}