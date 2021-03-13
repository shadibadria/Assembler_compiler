#include"data_image.h"

FILE * file_pointer;
int index_of_datatable = 0;

/*append to file function*/

void append_command_to_file(char * filename, data_image data) {
  file_pointer = fopen(filename, "a");
  if (file_pointer == NULL) {
    printf("error creating file %s \n", filename);
    exit(0);
  }

  fputs(data.Adress, file_pointer);
  fputs("      ", file_pointer);
  fputs(data.opcode, file_pointer);
  fputs(data.funct, file_pointer);
  fputs(data.adress_method, file_pointer);
  fputs("        ", file_pointer);
  fputs(data.TAG, file_pointer);

  fputs("\n", file_pointer);

}


void append_register_to_file(char * filename, char * register_number) {
  file_pointer = fopen(filename, "a");
  if (file_pointer == NULL) {
    printf("error creating file %s \n", filename);
    exit(0);
  }

  fputs(register_number, file_pointer);

  fputs("\n", file_pointer);

}
void close_file() {
  fclose(file_pointer);

}
/*from dec to bin */

/*from bin to hex */

/*create table line*/

/*write line to file*/

/*replace unknown line with adress (second pass)*/

/*if ps.ob file is good then create ps.ent and ps.ext*/