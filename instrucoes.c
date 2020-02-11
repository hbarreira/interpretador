#include "instrucoes.h"

// See if string str starts with string pre
bool startsWith(const char *pre, const char *str) {
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? false : strncmp(pre, str, lenpre) == 0;
}

// See if a string represents an attribution or an arithmetic expression
int ExprOuAtrib(char *expr) {

	int i=0;
	char *token = strtok(expr,"+-*/");
	while(token!=NULL){
		i++;
		token = strtok(NULL,"+-*/");
	}
	return i; // returns 1 if its atrib and 2 if its expression
}


// Create empty instruction
Instr* createEmptyInstr() {
	Instr *Instruction = (Instr *)malloc(sizeof(Instr));
	Instruction->op = 0;
	Instruction->first.kind = EMPTY;
	Instruction->second.kind = EMPTY;
	Instruction->third.kind = EMPTY;
	return Instruction;
}


// Create Instr Struct for read instruction
Instr* createReadInstruction(char* instrucao){
	char constante[20];

	if(sscanf(instrucao,"ler(%[^)]);",constante)!=1)
		return NULL;

	Instr *Instruction = createEmptyInstr();
	Instruction->op = READ;
	Instruction->first.kind = STRING;
	Instruction->first.contents.name = strdup(constante);
	return Instruction;
}

// Create Instr Struct for write instruction
Instr* createWriteInstruction(char* instrucao){
	char constante[20];

	if(sscanf(instrucao,"escrever(%[^)]);",constante)!=1)
		return NULL;

	Instr *Instruction = createEmptyInstr();
	Instruction->op = PRINT;
	Instruction->first.kind = STRING;
	Instruction->first.contents.name = strdup(constante);
	return Instruction;
}

// Create Instr Struct for if instruction
Instr* createIfInstruction(char* instrucao) {
	char variavel[15],label[15];

	if(sscanf(instrucao, "if %s goto %[^;];", variavel,label)!=2) {
		return NULL;
	}

	Instr *Instruction = createEmptyInstr();
	Instruction->op = IF_I;
	Instruction->first.kind = STRING;
	Instruction->first.contents.name = strdup(variavel);
	Instruction->second.kind = STRING;
	Instruction->second.contents.name = strdup(label);
	return Instruction;
}

// Create Instr Struct for label instruction
Instr* createLabelInstruction(char* instrucao) {
	char constante[15];

	if(sscanf(instrucao,"label %[^;];",constante)!=1)
		return NULL;

	Instr *Instruction = createEmptyInstr();
	Instruction->op = LABEL;
	Instruction->first.kind = STRING;
	Instruction->first.contents.name = strdup(constante);
	return Instruction;
}

// Create Instr Struct for goto instruction
Instr* createGotoInstruction(char* instrucao) {
	char constante[15];

	if(sscanf(instrucao, "goto %[^;];",constante)!=1)
		return NULL;

	Instr *Instruction = createEmptyInstr();
	Instruction->op = GOTO_I;
	Instruction->first.kind = STRING;
	Instruction->first.contents.name = strdup(constante);
	return Instruction;
}

// Create Instr Struct for atribution instruction
Instr* createAtribInstruction(char* instrucao) {
	
	char var[15],expr[90];

	if (sscanf(instrucao,"%s = %[^;];",var,expr)!=2) {
		return NULL;
	}

	char *expr2 = strdup(expr);

	int type = ExprOuAtrib(expr2);

	Instr *Instruction = createEmptyInstr();
	Instruction->first.kind = STRING;
	Instruction->first.contents.name = strdup(var);

	if(type==1) {  // atribution expression 

		Instruction->op = ATRIB;

		if(isdigit(expr[0])) { // x = 4;
			int x = atoi(expr);
			Instruction->second.kind=INT_CONST;
			Instruction->second.contents.val = x;
		}

		else { // x = y;
			Instruction->second.kind = STRING;
			Instruction->second.contents.name = strdup(expr);
		}
	}

	else if(type==2) { // arithmetic expression

		char opz[1];
		char t1[20];
		char t2[30];
		char *var2 = strdup(var);
		if (sscanf(expr,"%[^ ] %[^ ] %s",t1,opz,t2)!=3){
			return NULL;
		}

		// Check the operator to see whats the OpKind of the Instruction
		if(strcmp(opz, "+") == 0)
			Instruction->op =ADD;
		else if(strcmp(opz, "-") == 0) 
			Instruction->op =SUB;
		else if(strcmp(opz, "*") == 0) 
			Instruction->op =MUL;
		else if(strcmp(opz, "/") == 0)
			Instruction->op =DIV;
		else
			return NULL;


		// Check the arguments kind (if its STRING or INT_CONST)
		int x1,x2;

		if(isdigit(t1[0])) {  // Second Elem is INT_CONST

			x1 = atoi(t1);
			Instruction->second.kind=INT_CONST;
			Instruction->second.contents.val = x1;

			if (isdigit(t2[0])) { // Third Elem is INT_CONST

				x2 = atoi(t2);
				Instruction->third.kind = INT_CONST;
				Instruction->third.contents.val = x2;
			}

			else { // Third Elem is STRING

				Instruction->third.kind = STRING;
				Instruction->third.contents.name = strdup(t2);
				
			}
		}

		else { // Second Elem is STRING


			Instruction->second.kind=STRING;
			Instruction->second.contents.name = strdup(t1);

			if (isdigit(t2[0])) { // Third Elem is INT_CONST
				x2 = atoi(t2);
				Instruction->third.kind = INT_CONST;
				Instruction->third.contents.val = x2;
			}

			else { // Third Elem is STRING

				Instruction->third.kind = STRING;
				Instruction->third.contents.name = strdup(t2);
			}
		}
	}
	
	return Instruction;
}

//Parse the instructions

Instr* parser(char* instrucao) {

	if(startsWith("ler",instrucao)) {
		return createReadInstruction(instrucao);
	}

	else if(startsWith("escrever",instrucao)) {
		return createWriteInstruction(instrucao);
	}

	else if(startsWith("label",instrucao)) {
		return createLabelInstruction(instrucao);
	}

	else if(startsWith("goto",instrucao)) {
		return createGotoInstruction(instrucao);
	}

	else if(startsWith("if",instrucao)) {
		return createIfInstruction(instrucao);
	}

	else {
		return createAtribInstruction(instrucao);
	}
}


//LIST methods

List newList(void* n, List l1) {
	List l = malloc(sizeof(struct list));
	l->head = n;
	l->tail = l1;
	return l;
}

List reverse(List l){
    if (tail(l) == NULL)
        return l;
    List l1 = append(newList(head(l),NULL),reverse(tail(l)));
    return l1;
}

List append(List l1, List l2) {
	List copy2 = copyList(l2);
    List temp = lastElement(copy2);
    List copy = copyList(l1);
    temp->tail = copy;
    return copy2;
}

List lastElement(List l){
    if (tail(l)!=NULL){
        return lastElement(tail(l));
    }
    return l;
}

List copyList(List l){
    if (l == NULL)
        return NULL;
    List l1 = newList(head(l),copyList(tail(l)));
    return l1;
}

void* head(List l) {
	if (l == NULL) {
		return NULL;
	}
	return (l->head);
}

List tail(List l) {
	return (l->tail);
}

int length (List l) {
	if (l == NULL)
        return 0;
    return length(tail(l))+1;
}
