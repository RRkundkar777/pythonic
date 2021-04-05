//Defining PLUS AND MINUS SIGNS
#define PLUS 1
#define MINUS -1

//Node struture will store the digits of a number
typedef struct node {
	int num;
	struct node *next, *prev;
}node;

//Number structure stores the following
//Sign
//number of decimal numbers
//Head and Tail of number
typedef struct number {
	int sign, dec;
	node *head, *tail; 
}number;

//Functions
void initNumber(number *a);
void appendchar(number *num, char chr);
int length(number a);
void prepend(number *number, int digit);
void removdigit(number *num, int position);
void zeroRemov(number *number);
void display(number num1);