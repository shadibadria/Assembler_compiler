#pragma warning (disable : 4996)

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

	assemble_parsing(buffer);
	
}


return 0;
}
int parse_line(char* line) {

	int line_length = strlen(line);
	int i = 0,comment_flag=0;
	char temp[80];
	int j = 0;
	for (i = 0; i < line_length; i++)
	{
		if (line[i] != ' ' && line[i] != '\t'&& line[i]!='\0'&&line[i]!='\n') {
			
			if (line[i] == ';') {
				printf("comment\n");
				return 1;
			}
			
			temp[j++]= line[i];
			if (line[i] == ':') {
				temp[j] = '\0';
				printf("[label]>%s\n", temp);
				j = 0;
			}

			if ( line[i+1] == ' '&& j!=0 && temp[0]!='.' ) {
				
					temp[j] = '\0';
				printf("[xcommand]>%s\n", temp);
				j = 0;

			}
			if (line[i] == ',') {
				temp[j -1] = '\0';

				printf("[xarg1]>%s\n", temp);
				j = 0;
			}
			if (line[i+1] == '\n'&& temp[0]!='.') {
				temp[j ] = '\0';

				printf("[xarg2]>%s\n", temp);

			}

		}

	}
}
void assemble_parsing(char *line){

	/*printf("%s\n", line);*/

	parse_line(line);

	printf("\n----------\n");


}


