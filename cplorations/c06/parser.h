/****************************************
 * C-ploration 5 for CS 271
 * 
 * [NAME] Marc Vannucci
 * [TERM] FALL 2025
 * 
 ****************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

typedef int16_t hack_addr;
typedef int16_t opcode;
#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH -2)

/** function prototypes **/
char *strip(char *s);

void parse(FILE * file);

/** function headers **/
bool is_Atype(const char *);

bool is_label(const char *);

bool is_Ctype(const char *);

/** function label header **/
char *extract_label(const char *line, char* label);

typedef enum def_instr_type {
	INVALID = -1,
	ATYPE,
	CTYPE,

}

typedef struct c_instruction {
	opcode a:1;
	opcode comp:6;
	opcode dest:3;
	opcode jump:3;
}

typedef struct a_instruction {
	union {
		hack_addr address;
		char *label;
};

	bool is_addr;
}

typedef struct instruction {
	union {
		a_instruction a_inst;
		c_instruction c_inst;
	} inst;
	 def_instr_type inst_type;
} instruction;

