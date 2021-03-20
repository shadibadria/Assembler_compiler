/*
file name : file_proccess.h
explain: this header has declration for file_process.h functions
*/

#include<stdio.h>

#include<string.h>

int check_file(char * file_name);
void append_entry_tofile(char * filename);
void append_extern_tofile(char * filename);
void append_datatable_tofile(char *filename);
int check_file_for_ending(char *);