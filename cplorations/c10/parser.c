/****************************************
 * C-ploration for CS 271
 *
 * [NAME] Marc Vannucci
 * [TERM] FALL 2025
 *
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"
#include "hack.h"

/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s)
{

	char s_new[strlen(s) + 1];
	int i = 0;

	for (char *s2 = s; *s2; s2++)
	{
		if (*s2 == '/' && *(s2 + 1) == '/')
		{
			break;
		}
		else if (!isspace(*s2))
		{
			s_new[i++] = *s2;
		}
	}

	s_new[i] = '\0';
	strcpy(s, s_new);
	return s;
}

/* Function for loading predefined symbols. */
void add_predefined_symbols()
{

	for (int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++)
	{
		predefined_symbol current = predefined_symbols[i];
		symtable_insert(current.name, current.address);
	}
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments.
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
int parse(FILE *file, instruction *instructions)
{
	instruction instr;
	char line[MAX_LINE_LENGTH] = {0};
	int instr_num = 0;
	int line_num = 0;
	while (fgets(line, sizeof(line), file))
	{
		line_num++;
		if (instr_num >= MAX_INSTRUCTIONS)
		{
			exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
		}
		strip(line);
		if (*line == '\0')
		{
			continue;
		}

		char inst_type = ' ';

		if (is_Atype(line))
		{
			inst_type = 'A';
			if (!parse_A_instruction(line, &instr.inst.a_inst))
			{
				exit_program(EXIT_INVALID_A_INSTR, line_num, line);
			}

			instr.inst_type = ATYPE;
		}

		if (is_label(line))
		{
			inst_type = 'L';
		}

		if (is_Ctype(line))
		{
			inst_type = 'C';
			char tmp_line[MAX_LINE_LENGTH];
			strcpy(tmp_line, line);
			parse_C_instruction(tmp_line, &instr.inst.c_inst);
			if (instr.inst.c_inst == DEST_INVALID)
			{
				exit_program(EXIT_INVALID_C_DEST, line_num, line);
			}
			else if (instr.inst.c_inst == COMP_INVALID)
			{
				exit_program(EXIT_INVALID_C_COMP, line_num, line);
			}
			else if (instr.inst.c_inst == JMP_INVALID)
			{
				exit_program(EXIT_INVALID_C_JUMP, line_num, line);
			}

			instr.inst_type = CTYPE;
		}

		if (is_label(line))
		{
			char n_label[MAX_LABEL_LENGTH] = {0};
			extract_label(line, n_label);
			strcpy(line, extract_label(line, n_label));
			if (!isalpha(n_label[0]))
			{
				exit_program(EXIT_INVALID_LABEL, line_num, n_label);
			}
			if (symtable_find(n_label) != NULL)
			{
				exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, n_label);
			}

			symtable_insert(n_label, instr_num);
			continue;
		}
		// printf("%u: %c  %s\n", instr_num, inst_type, line);
		if (inst_type == ATYPE && hack_addr)
		{
			printf("A: %d\n", instr.inst.a_inst.is_addr);
		}
		else if (instruction == hack_addr)
		{
			printf("A: %d\n", instr.inst.a_inst.addr.address);
		}
		else
		{
			printf("A: %d\n", instr.inst.a_inst.addr.label);
		}
	}

	if (instr.inst_type == CTYPE)
	{
		printf("C: d=%d, c=%d, j=%d\n", instr.inst.c_inst.dest, instr.inst.c_inst.comp, instr.inst.c_inst.jump);
	}

	instructions[instr_num++] = instr;
	return instr_num;
}

/* type checker, this checks if our input is a Atype, label, or Ctype*/
bool is_Atype(const char *line)
{
	char target = line[0];

	if (target == '@')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool is_label(const char *line)
{
	char target_1 = line[0];
	char target_2 = line[strlen(line) - 1];
	// printf("DEBUG is_label: target_1='%c' target_2='%c' (ASCII: %d)\n", target_1, target_2, target_2);
	if (target_1 == '(' && target_2 == ')')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool is_Ctype(const char *line)
{

	if (!is_Atype(line) && !is_label(line))
	{
		return true;
	}
	return false;
}

/* Label Extractor. This extracts the string inside the label. */

char *extract_label(const char *line, char *label)
{
	int x, i;
	int start_of_string = 1;
	int end_of_string = strlen(line) - 2;

	for (x = start_of_string, i = 0; i < end_of_string; ++x, ++i)
	{
		label[i] = line[x];
	}

	label[i] = '\0';
	return label;
}

/* Function for parsing a A_instruction*/
bool parse_A_instruction(const char *line, a_instruction *instr)
{
	char *s;
	s = malloc(strlen(line));
	strcpy(s, line + 1);
	char *s_end = NULL;

	long result = strtol(s, &s_end, 10);

	if (s == s_end)
	{
		instr->addr.label = malloc(strlen(s) + 1);
		strcpy(instr->addr.label, s);
		instr->is_addr = false;
	}

	else if (*s_end != 0)
	{
		return false;
	}

	else
	{
		instr->addr.address = result;
		instr->is_addr = true;
	}

	return true;
}

// Function for parsing a C instruction.
void parse_C_instruction(char *line, c_instruction *instr)
{
	char *temp = strtok(line, ";");
	char *jump = strtok(NULL, ";"); // Null tells strtok to continue from last position.

	char *dest = strtok(temp, "=");
	char *comp = strtok(NULL, "=");

	if (comp == NULL)
	{
		dest = NULL;
		comp = temp;
	}
	int a_temp = 0;
	instr->jump = str_to_jumpid(jump);
	instr->comp = str_to_compid(comp, &a_temp);
	instr->dest = str_to_destid(dest);

	// ternary check.
	instr->a = a_temp;
	instr->a = (strchr(comp, 'M') != NULL) ? 1 : 0;
}
