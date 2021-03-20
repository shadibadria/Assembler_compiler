/*
file name : symbol_table.c
explain: this file has all the symbol table function
symbol table uses HASH TABLE 
*/

#include"symbol_table.h"
#include "math.h"
int capacity_table=1;
int size_table = 0;

int hashcode(int key) {
  return (key % capacity_table);
}

/*
init hash table array using malloc 
*/
int init_array() {
  
  array = (struct data * ) malloc(capacity_table* sizeof(struct data));
  if(array==NULL){
    printf("ERROR: something went wrong while trying to use malloc at symboltable.c\n");
    return 0;
  }
  return 1;
}


/*append to file function*/


/*
insert entry labels after second pass to the labels 
at the symbol table
*/
void insert_entry(char * symbol){

int i;

  for (i = 0; i < size_table; i++) {
    if (strcmp(array[i].symbol ,symbol)==0) {
        
        array[i].attribute=(char*)realloc(array[i].attribute,6 );

  if (array[i].attribute == NULL) {
    printf("Something Went Wrong no memory\n");
    exit(1);
  }  

      strcat(array[i].attribute,",entry" );
    }
}
}
/* to insert a key in the hash table */
void insert(int key, int value, char * symbol, char * attribute) {
  int index = hashcode(key);
  
  capacity_table++;
  array=(struct data*)realloc(array,capacity_table* sizeof(struct data));
    
  if(array==NULL){
    printf("ERROR: using realloc at symbol_table.c\n");
    exit(0);
  }


  if (array[index].amount == 0) {
    /*  key not present, insert it  */

    array[index].key_value = key;
    array[index].amount = 1;
      /*insert value */
      if(value==0){
              array[index].value = (char * ) malloc(2 * sizeof(char));

      }else{
      array[index].value = (char * ) malloc( (floor(log10(abs(value)))) * sizeof(char));

      }
  if (array[index].value == NULL) {
    printf("Something Went Wrong no memory at  symbol_table.c\n");
    exit(1);
  }  
   sprintf(array[index].value,"%04d",value);

    /*insert symbol*/
   array[index].symbol = (char * ) malloc(strlen(symbol) * sizeof(char));
  if (array[index].symbol == NULL) {
    printf("Something Went Wrong no memory\n");
    exit(1);
  }  
    if(symbol[strlen(symbol)-1]==':'){
            symbol[strlen(symbol)-1]='\0';

    }else{
      symbol[strlen(symbol)]='\0';

    }
      strcpy(array[index].symbol, symbol);

    /*insert attribute */
  array[index].attribute = (char * ) malloc((2+strlen(attribute)) * sizeof(char));
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

/* to display all the elements of a hash table */
void display() {
  int i;
  for (i = 0; i < size_table; i++) {
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
  for (i = 0; i < size_table; i++) {
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
    
  for (i = 0; i < size_table; i++) {
    if (strcmp(array[i].symbol,symbol)==0) {
      return 0;
    }

  }
  return 1;
}
/*get the size of the symbol table*/
int size_of_hashtable() {
  return size_table;
}
void free_symbol_table_memory(){
int i=0;

for(i=0;i<size_table;i++){
  free(array[i].symbol);
    free(array[i].value);
  free(array[i].attribute);
}
free(array);
}