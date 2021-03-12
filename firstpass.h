#include<stdio.h>

#include<string.h>

#include<ctype.h>

#include<stdlib.h>

#define bufferLength 80

int firstpass(char * filename);
int assemble_parsing(char * line);
char * remove_space_tabs(char * string);
int check_if_extern(char * line,int test);
char * remove_spaces_from_index(char * line, int i);
int check_if_entry(char * line,int test);
int check_if_label(char * line,int test);
int parse_line(char * line);
int check_if_its_data(char * line,int test);
int check_if_its_string(char * line,int test);
void data_parsing(char * line);
int string_parsing(char * line, int index);
int check_if_command(char * line);
int find_adressing_method(char * string, int label_flag);