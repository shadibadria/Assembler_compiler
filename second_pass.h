/*
* File name : second_pass.h
* Header for second pass functions, second_pass.c access .
* Author : Shadi Badria <shadibadria@gmail.com>
*/


int secondpass_pasrsing(char * line);
int secondpass(char * filename);
int check_for_label(char * line);
void fill_table();
void check_for_label_error();