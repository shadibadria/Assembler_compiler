
#include"data_image.h"

FILE *file_pointer;
int index_of_datatable=0;


/*append to file function*/

void append_to_file(char *filename,data_image data){
    file_pointer = fopen(filename,"a");
        if(file_pointer==NULL){
            printf("error creating file %s \n",filename);
            exit(0);
        }
        fputs(data.Adress,file_pointer);  
      fputs(" xyz\n",file_pointer);  
    fclose(file_pointer);

}
/*from dec to bin */

/*from bin to hex */

/*create table line*/

/*write line to file*/

/*replace unknown line with adress (second pass)*/

/*if ps.ob file is good then create ps.ent and ps.ext*/