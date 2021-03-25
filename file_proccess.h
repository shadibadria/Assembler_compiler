/*
* Filename : file_proccess.h
* Header for file open and checking, file_proccess.c access .
* Author : Shadi Badria <shadibadria@gmail.com>
*/

int check_file(char * file_name);
void append_entry_tofile(char * filename);
void append_extern_tofile(char * filename);
void append_datatable_tofile(char * filename,int instruct_size,int data_size);
int check_file_for_ending(char * );