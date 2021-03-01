#include<stdio.h>

#include<string.h>

#include<ctype.h>

#include<stdlib.h>

#define bufferLength 80

int firstpass(char * filename);
int assemble_parsing(char * line);
char * remove_space_tabs(char * string);
int check_if_extern(char * line);
char * remove_spaces_from_index(char * line, int i);
int check_if_entry(char * line);
int check_if_label(char * line);
int parse_line(char * line);
int check_if_its_data(char * line);
int check_if_its_string(char * line);
void data_parsing(char * line);
void string_parsing(char * line, int index);
int check_if_command(char * line);
