#include "headers.h"

// linked list struct
typedef struct list {
  void* head;
  struct list *tail;
} *List;

// instruction structs
typedef enum {
  ATRIB,
  ADD, 
  SUB,
  MUL,
  DIV,
  IF_I, 
  PRINT, 
  READ, 
  GOTO_I, 
  LABEL,
  NONE,
  } OpKind;

typedef enum {EMPTY, INT_CONST, STRING} ElemKind;

typedef struct {

  ElemKind kind;

  union { 
    int val;
    char *name;
  } contents;
} Elem;

typedef struct {
  OpKind op;
  Elem first, second, third;
} Instr;



// parse the input line
Instr* parser(char* instrucao);
//creates empty instruction
Instr* createEmptyInstr();
// creates read intruction
Instr* createReadInstruction(char* instrucao);
// creates write instruction
Instr* createWriteInstruction(char* instrucao);
// creates if instruction
Instr* createIfInstruction(char* instrucao);
// creates label instruction
Instr* createLabelInstruction(char* instrucao);
// creates goto instruction
Instr* createGotoInstruction(char* instrucao);
// creates atribution instruction
Instr* createAtribInstruction(char* instrucao);


// creates new linkedlist
List newList(void* n, List l1);
// reverse a list
List reverse(List l);
//appends two lists
List append(List l1, List l2);
//last element of the list
List lastElement(List l);
//clones a list
List copyList(List l);
//first element of the list
void* head(List l);
//rest of the list
List tail(List l);
//length of the list
int length (List l);
//prints a list of any type of element
void generalPrint(List l,void (*print)(void* element));



// See if string str starts with string pre
bool startsWith(const char *pre, const char *str);
// See if expr is either an arithmetic expression or atribution expression
int ExprOuAtrib(char *expr);