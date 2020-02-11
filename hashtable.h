#include "headers.h"

//hash table struct
typedef struct hlist {
	char *key;
	int value;
	struct hlist *next;
} hashList;

hashList *table[HASH_SIZE];
int lookup(char *key);
void insert(char *key, int value);
unsigned int hash(char *str);