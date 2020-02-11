#include "hashtable.h"

//check if exits in hashtable and returns
int lookup(char *key) {

	int index;
	index = hash(key);
	hashList* l = table[index];

	while (l != NULL) {

		if (strcmp(l->key, key) == 0)
			return l->value;
		l = l->next;
	}	

	return 0;
}

//inserts in hashtable
void insert(char *k, int v) {

	int index;
	hashList* new;
	index = hash(k);
	new = (hashList*)malloc(sizeof(hashList));
	new->key = k;
	new->value = v;
	new->next = table[index];
	table[index] = new;
}

//hashfunction
unsigned int hash(char* str) {
	unsigned int h;
	unsigned char *p;
	h = 0;
	for (p = (unsigned char* )str; *p!= '\0' ; p++)
		h = MULTIPLIER*h + *p;
	return h % HASH_SIZE;
}
