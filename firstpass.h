
/*
file name : firstpass.h
explain: this header file has all the function declration for firstpass.c
*/
#include<stdio.h>

#include<string.h>

#include<ctype.h>

#include<stdlib.h>

#define bufferLength 4095
#define MAX_LINE 80
#define MAX_LABEL 31
#define MAX_DATA 2047
#define MIN_DATA -2047

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
int data_parsing(char * line,int i);
int string_parsing(char * line, int index);
int check_if_command(char * command,char *line,int label_flag);
void check_comma(char *line);
int check_line_arguments(char *line);
int count_word( char *s);
void remove_label(char *line);
