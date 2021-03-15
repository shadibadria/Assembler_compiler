/*
file name : second_pass.h
explain: this header file has declrations of the second_pass.c file
*/
#define bufferLength 80
int secondpass_pasrsing(char *line);
int secondpass(char *filename);
int check_for_label(char * line);
void fill_table();
void check_for_label_error();