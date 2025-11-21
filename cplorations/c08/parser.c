/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] Marc Vannucci
 * [TERM] FALL 2025
 * 
 ****************************************/
#include "parser.h"
#include "symtable.h"


/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s){	

	char s_new[strlen(s) + 1];
	int i = 0;

	for (char *s2 = s; *s2; s2++) {
		if (*s2 == '/' && *(s2+1) == '/') {
			break;
		}
		else if (!isspace(*s2)) {
			s_new[i++] = *s2;
		}
	}

	s_new[i] = '\0';
	strcpy(s, s_new);
    return s;	
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments. 
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
void parse(FILE * file){
	
	char line[MAX_LINE_LENGTH] = {0};
	int inst_count = 0;
	while(fgets(line, sizeof(line), file)) {
		strip(line);
		if(*line == '\0') {
			continue;
		}

		//char inst_type = ' ';

		//if (is_Atype(line)) {
			//inst_type = 'A';
//}

		//if (is_label(line)) {
			//inst_type = 'L';
		//}

		//if (is_Ctype(line)) {
			//inst_type = 'C';
		

		if (is_label(line)) {
			char n_label[MAX_LABEL_LENGTH] = {0};
			extract_label(line, n_label);
			strcpy(line, n_label);
			symtable_insert(n_label, inst_count);
		}	else {
			inst_count++;
		}
		}
		}
		//printf("%c  %s\n", inst_type, line);
	
//}

/* type checker, this checks if our input is a Atype, label, or Ctype*/
bool is_Atype(const char *line) {
	char target = line[0];

	if (target == '@') {
		return true;
}   else {
		return false;
	}

}

bool is_label(const char *line) {
	char target_1 = line[0];
	char target_2 = line[strlen(line) - 1];
	 //printf("DEBUG is_label: target_1='%c' target_2='%c' (ASCII: %d)\n", target_1, target_2, target_2);
	if (target_1 == '(' && target_2 == ')') {
		return true;
	} else {
		return false;
	}

	}


bool is_Ctype(const char *line) {

	if (!is_Atype(line) && !is_label(line)) {
		return true;
	}
	return false;
}

/* Label Extractor. This extracts the string inside the label. */

char *extract_label(const char *line, char *label) {
	int x, i;
	int start_of_string = 1;
	int end_of_string = strlen(line) -2;

	for (x = start_of_string, i = 0; i < end_of_string; ++x, ++i) {
		label[i] = line[x];
		}

	label[i] = '\0'; 
	return label;
}


