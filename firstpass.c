
#include"firstpass.h"
int firstpass(char* filename){

int i=0;
int IC = 100;
int DC = 0;
FILE *filePointer;
char buffer[bufferLength];

filePointer = fopen(filename, "r");

if(filePointer==NULL){
printf("\ncant open file \n");
return 0;
}


while(fgets(buffer, bufferLength, filePointer)) {
    printf("%s\n", buffer);
}


return 0;
}

void assemble_parsing(char *line){

}