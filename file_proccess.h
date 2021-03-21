/*
filename : file_proccess.h
this header has declration for file_process.c functions
*/

#include<stdio.h>

#include<string.h>

int check_file(char * file_name);
void append_entry_tofile(char * filename);
void append_extern_tofile(char * filename);
void append_datatable_tofile(char * filename);
int check_file_for_ending(char * );