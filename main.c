#include "instrucoes.h"
#include "hashtable.h"

#define LETRA(C) (((C) >= 'a'&& (C)<= 'z')|| ((C)>= 'A' && (C)<= 'Z'))

// read a string line
char *ler_nome() {  
	int i=0;
	char aux[MAXNOME], c, *nome;  
	do c = getchar();while (!LETRA(c));
  	do {
    		aux[i++] = c;
    		c = getchar();
  	} while (c != '\n');
  aux[i] = '\0';
  nome = malloc(i+1);
  strcpy(nome,aux);
  return nome;
}


//main which uses the methods
int main() {
	printf("Intrepretador de linguagem de programacao\n");
	printf("Introduza as suas instrucoes:\n");
	printf("\n");

	char* string;

	string = ler_nome();

	List list = NULL;

	// read instructions until "quit" command is read
	while(true){

		if(strcmp(string, "quit;") == 0) {
			break;
		}

		Instr* instrucao = parser(string);
		
		if(instrucao == NULL) {
			printf("Not an instruction\n");
			return -1;
		}

		list = newList(instrucao,list);
		string = ler_nome();
	}

	//starting point of the list
	list = reverse(list);


	// Reads the instructions structs and executes instructions
	printf("\n");
	Instr* instr;
	OpKind operator;
	//while there is instructions to do, check the different types of instructions
	while(list != NULL) {
		int v;
		instr = list->head;

		operator = instr->op;

		if(operator == READ) {
			printf("Atribuir valor a %s : ", instr->first.contents.name);
			scanf("%d",&v);
			insert(instr->first.contents.name, v);
		}

		else if (operator == PRINT) {
			v = lookup(instr->first.contents.name);
			printf("%d\n", v);
		}

		else if (operator == ADD) {

			int v1,v2;

			if(instr->second.kind == INT_CONST && instr->third.kind == INT_CONST) {

				v1 = instr->second.contents.val;
				v2 = instr->third.contents.val;
			}

			else if(instr->second.kind == INT_CONST && instr->third.kind == STRING) {
				
				v1 = instr->second.contents.val;
				v2 = lookup(instr->third.contents.name);
			}

			else if(instr->second.kind == STRING && instr->third.kind == INT_CONST) {
				
				v1 = lookup(instr->second.contents.name);
				v2 = instr->third.contents.val;
			}

			else if(instr->second.kind == STRING && instr->third.kind == STRING) {
				
				v1 = lookup(instr->second.contents.name);
				v2 = lookup(instr->third.contents.name);
			}

			v = v1+v2;
			insert(instr->first.contents.name, v);
		}

		else if (operator == SUB) {

			int v1,v2;

			if(instr->second.kind == INT_CONST && instr->third.kind == INT_CONST) {

				v1 = instr->second.contents.val;
				v2 = instr->third.contents.val;
			}

			else if(instr->second.kind == INT_CONST && instr->third.kind == STRING) {
				
				v1 = instr->second.contents.val;
				v2 = lookup(instr->third.contents.name);
			}

			else if(instr->second.kind == STRING && instr->third.kind == INT_CONST) {
				
				v1 = lookup(instr->second.contents.name);
				v2 = instr->third.contents.val;
			}

			else if(instr->second.kind == STRING && instr->third.kind == STRING) {
				
				v1 = lookup(instr->second.contents.name);
				v2 = lookup(instr->third.contents.name);
			}

			v = v1-v2;
			insert(instr->first.contents.name, v);
		}

		else if (operator == MUL) {
			
			int v1,v2;

			if(instr->second.kind == INT_CONST && instr->third.kind == INT_CONST) {

				v1 = instr->second.contents.val;
				v2 = instr->third.contents.val;
			}

			else if(instr->second.kind == INT_CONST && instr->third.kind == STRING) {
				
				v1 = instr->second.contents.val;
				v2 = lookup(instr->third.contents.name);
			}

			else if(instr->second.kind == STRING && instr->third.kind == INT_CONST) {
				
				v1 = lookup(instr->second.contents.name);
				v2 = instr->third.contents.val;
			}

			else if(instr->second.kind == STRING && instr->third.kind == STRING) {
				
				v1 = lookup(instr->second.contents.name);
				v2 = lookup(instr->third.contents.name);
			}

			v = v1*v2;
			insert(instr->first.contents.name, v);
		}

		else if (operator == DIV) {
			
			int v1,v2;

			if(instr->second.kind == INT_CONST && instr->third.kind == INT_CONST) {

				v1 = instr->second.contents.val;
				v2 = instr->third.contents.val;
			}

			else if(instr->second.kind == INT_CONST && instr->third.kind == STRING) {
				
				v1 = instr->second.contents.val;
				v2 = lookup(instr->third.contents.name);
			}

			else if(instr->second.kind == STRING && instr->third.kind == INT_CONST) {
				
				v1 = lookup(instr->second.contents.name);
				v2 = instr->third.contents.val;
			}

			else if(instr->second.kind == STRING && instr->third.kind == STRING) {
				
				v1 = lookup(instr->second.contents.name);
				v2 = lookup(instr->third.contents.name);
			}

			v = v1/v2;
			insert(instr->first.contents.name, v);
		}

		else if (operator == ATRIB) {
			
			if( instr->second.kind == STRING)
				v = lookup(instr->second.contents.name);
			else
				v = instr->second.contents.val;

			insert(instr->first.contents.name, v);
		}

		else if (operator == GOTO_I) {
			char *aux = strdup(instr->first.contents.name);
			while(instr->op != LABEL && strcmp(aux, instr->first.contents.name)==0){
				list = list->tail;
				instr = list->head;
			}

		}

		else if (operator == IF_I) {
			if(lookup(instr->first.contents.name)!=0){
				char *aux = strdup(instr->second.contents.name);
				while(instr->op != LABEL && strcmp(aux, instr->first.contents.name)!=0){
					list = list->tail;
					instr = list->head;
				}
			}
		}

		else if (operator == LABEL) {
			;
		}

		//next element of the list
		list = list->tail;
	}

	free(list);
	return 0;
}
