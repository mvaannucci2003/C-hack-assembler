/****************************************
 * C-ploration 3 for CS 271
 * 
 * [NAME] Marc Vannucci
 * [TERM] FALL 2025
 * 
 ****************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE_LENGTH 200

int main(int argc, const char *argv[])
{	
	// if incorrect number of arguments.
	if(argc != 2) {
		printf("Usage: %s [filename]\n", argv[0]);
		exit(EXIT_FAILURE);
	
}
	//Open the input file.
	FILE *fin = fopen( argv[1], "r");

	if(fin == NULL) {
		perror("Unable to open file!");
		exit(EXIT_FAILURE);		
	}

	//Open the Output file.
	char out_file[MAX_LINE_LENGTH];
	strcpy(out_file,argv[1]);
	strcat(out_file, ".echo");
	FILE *fout = fopen(out_file, "w+");

	if(fout == NULL) {
		perror("Unable to create file!");
		exit(EXIT_FAILURE);	
	}

	//Reading in the file.
	char line[MAX_LINE_LENGTH] = {0};
	unsigned int line_num = 0;
	while (fgets(line, sizeof(line), fin)) {
		line_num++;
		printf("[%04d] %s", line_num, line);
		fprintf(fout, line);
	}

	//Closing the file.
	fclose(fin);
	fclose(fout);
	









	
}

