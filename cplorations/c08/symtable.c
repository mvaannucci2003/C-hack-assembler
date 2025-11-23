/****************************************
 * C-ploration 7 for CS 271
 * 
 * [NAME] Marc Vannucci
 * [TERM] FALL 2025
 * 
 ****************************************/
#include "symtable.h"

/** Symbol Data Struct **/
struct Symbol *hashArray[SYMBOL_TABLE_SIZE];


int hash(char *str) {
	
	unsigned long hash = 5381;
	int c;

	while((c = *str++)) 
		hash = ((hash << 5) + hash) + c;
	
	
	return hash % SYMBOL_TABLE_SIZE;
	}


void symtable_insert(char *key, hack_addr addr) {

	struct Symbol *item = (struct Symbol*)
malloc(sizeof(struct Symbol));
	item->addr = addr;
	item->name = strdup(key);

	int hashIndex = hash(key);

	while(hashArray[hashIndex] != NULL &&
		hashArray[hashIndex]->name != NULL) {

		++hashIndex;
		hashIndex %= SYMBOL_TABLE_SIZE;
	}

	hashArray[hashIndex] = item;
}

struct Symbol *symtable_find(char * key) {
	int hashIndex = hash(key);

	while(hashArray[hashIndex] != NULL) {

		if(strcmp(hashArray[hashIndex]->name, key) == 0)
			return hashArray[hashIndex];

		++hashIndex;

		hashIndex %= SYMBOL_TABLE_SIZE;
	}

	return NULL;
}

//* This function was used for debugging and not nessesary for the assembler. Thus, it has been *// 
//* commented out as to not cause errors.*//
//void symtable_display_table() {
	//int i = 0;

	//for(i = 0; i<SYMBOL_TABLE_SIZE; i++) {

		//if(hashArray[i] != NULL)
			//printf(" (%d,%d) ", hashArray[i]->name, hashArray[i]->addr);
		//else
			//printf(" ~~ ");
	//}

	//printf("\n");
///}

void symtable_print_labels() {
	int i = 0;

	for(i = 0; i<SYMBOL_TABLE_SIZE; i++) {

		if(hashArray[i] != NULL)
			printf("{%s,%d}\n", hashArray[i]->name, hashArray[i]->addr);
}

}
