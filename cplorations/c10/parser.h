/****************************************
 * C-ploration 5 for CS 271
 *
 * [NAME] Marc Vannucci
 * [TERM] FALL 2025
 *
 ****************************************/
#ifndef __PARSER_H__
#define __PARSER_H__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

typedef int16_t hack_addr;
typedef int16_t opcode;
#define MAX_LINE_LENGTH 200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH - 2)
#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS

/** function prototypes **/
char *strip(char *s);

/** function headers **/
bool is_Atype(const char *);

bool is_label(const char *);

bool is_Ctype(const char *);

/** function label header **/
char *extract_label(const char *line, char *label);

typedef enum def_instr_type
{
	INVALID = -1,
	ATYPE,
	CTYPE,

} def_instr_type;

// Header to parse C instructions.

typedef struct c_instruction
{
	opcode a : 1;
	opcode comp : 7;
	opcode dest : 4;
	opcode jump : 4;
} c_instruction;

typedef struct a_instruction
{
	union
	{
		hack_addr address;
		char *label;
	} addr;

	bool is_addr;
} a_instruction;

bool parse_A_instruction(const char *, a_instruction *);

typedef struct instruction
{
	union
	{
		a_instruction a_inst;
		c_instruction c_inst;
	} inst;
	def_instr_type inst_type;
} instruction;

int parse(FILE *file, instruction *instructions);

void parse_C_instruction(char *line, c_instruction *instr);
#endif
