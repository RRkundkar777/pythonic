#include<stdlib.h>
#include"stack.h"

// Stack to store numbers (operands)
void iinit(istack *s) {
	*s = NULL;
}

void ipush (istack *s, number *t) {
	istack temp;
	temp = (inode *)malloc(sizeof(inode));
	temp->a = t;
	temp->p = *s; 
	*s = temp;
}

number *ipop(istack *s) {
	number *t;
	istack temp;
	t = (*s)->a;
	temp = *s;
	*s = (*s)->p;
	free(temp);
	return t;
}

int iisempty (istack *s) {
	return *s == NULL;
}

//  Stack to store characters (operators)
void cinit(cstack *s) {
	*s = NULL;
}

void cpush (cstack *s, char t) {
	cstack temp;
	temp = (cnode *)malloc(sizeof(cnode));
	temp->a = t;
	temp->p = (*s);
	*s = temp;
}

char cpop(cstack *s) {
	char t;
	cstack temp;
	temp = (*s);
	t = (*s)->a;
	*s = (*s)->p;
	free(temp);
	return t;
}

int cisempty (cstack *s) {
	return *s == NULL;
}

char ctop(cstack *s) {
	char ch;
	ch = cpop(s);
	cpush(s, ch);
	return ch;
}