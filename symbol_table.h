
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct data 
{
	int key_value;
	int amount;/*if value is more than 1 (same adress twice)*/
    char symbol[15];
    char attribute[15];
};

struct data *array;


int hashcode(int key);
void init_array();
void insert(int key,char *symbol,char *attribute);

void display();
 int size_of_hashtable();
