#include "number.h"

//Number stack node which stores head of number ADT
typedef struct inode {
	number *a;
	struct inode *p;
}inode;

typedef inode *istack;

void iinit(istack *s);
void ipush(istack *s, number *a);
number *ipop(istack *s);
int iisempty(istack *s);

// Operator Stack node which directly stores the operators
typedef struct cnode {
	char a;
	struct cnode *p;
}cnode;

typedef cnode *cstack;

void cinit(cstack *s);
void cpush(cstack *s, char t);
char cpop(cstack *s);
int cisempty(cstack *s);
char ctop(cstack *s);