#include<stdio.h>

#include<string.h>

#include<ctype.h>

#include<stdlib.h>

#define bufferLength 1000

int firstpass(char * filename);
void assemble_parsing(char * line);
char * remove_space_tabs(char * string);
int check_if_extern(char * line);
char *remove_spaces_from_index(char * line,int i);