#include"symbol_table.h"
int capacity_table = 20;
int size_table = 0;
int hashcode(int key)
{
	return (key % capacity_table);
}

void init_array()
{
	int i;	
	array = (struct data*) malloc(capacity_table * sizeof(struct data));
	for (i = 0; i < capacity_table; i++) 
        {
		array[i].key_value = 0;
		array[i].amount = 0;
	}
}
 
/* to insert a key in the hash table */
void insert(int key,char *symbol,char *attribute)
{
	int index = hashcode(key);
	if (array[index].amount == 0) 
        {
		/*  key not present, insert it  */
		array[index].key_value = key;
		array[index].amount = 1;
        strcpy(array[index].symbol,symbol);
          strcpy(array[index].attribute,attribute);
		size_table++;
		printf("\n Key (%d) has been inserted \n", key);
	}
	else if(array[index].key_value == key) 
        {
		/*  updating already existing key  */
		printf("\n Key (%d) already present, hence updating its value \n", key);
		array[index].amount += 1;
	}
	else
        {
		/*  key cannot be insert as the index is already containing some other key  */
		printf("\n ELEMENT CANNOT BE INSERTED \n");
	}
}


/* to display all the elements of a hash table */
void display()
{
	int i;
	for (i = 0; i < capacity_table; i++)
        {
		if (array[i].amount == 0)
                {
			
		}
		else 
                {
			printf("\n--- array[%d] : ---\nkey= %d \nsymbol = %s \nattr=%s \t", i, array[i].key_value,array[i].symbol,array[i].attribute);
		}
	}
}
 
 int size_of_hashtable()
{
	return size_table;
}