#define NUM_PREDEFINED_SYMBOLS 23
#define MAX_SYMBOL_NAME_LENGTH 200
typedef int16_t address;

typedef enum symbol_id
{
    SYM_SP = 0,
    SYM_LCL = 1,
    SYM_ARG = 2,
    SYM_THIS = 3,
    SYM_THAT = 4,
    SYM_R0 = 5,
    SYM_R1 = 6,
    SYM_R2 = 7,
    SYM_R3 = 8,
    SYM_R4 = 9,
    SYM_R5 = 10,
    SYM_R6 = 11,
    SYM_R7 = 12,
    SYM_R8 = 13,
    SYM_R9 = 14,
    SYM_R10 = 15,
    SYM_R11 = 16,
    SYM_R12 = 17,
    SYM_R13 = 18,
    SYM_R14 = 19,
    SYM_R15 = 20,
    SYM_SCREEN = 16384,
    SYM_KBD = 24576,

} symbol_id;

typedef struct predefined_symbol
{
    char *name;
    address address;

} predefined_symbol;
