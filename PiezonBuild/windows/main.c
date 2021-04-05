#include<stdio.h>
#include<stdlib.h>
#include"stack.h"
#include "operation.h"

//Defining Unique Values
#define OPERAND	100
#define OPERATOR 200
#define END	300
#define ERR 400

//Structure of Token
typedef struct token{
	int type; //i.e operator or operand
	number *num; //Num structure
	char op;
}token;

//Enumerating the possible states
enum state { NUMBER, DOT, OP, FINISH, ERROR, SPC };

//The gettoken function handles the invalid operators and returns the next token
token gettoken(char *expr, int *reset){
	//Static integer is needed to remember the state
	static int i = 0;

	//If token turns out to be a number, then it will be returned and token.num = a 
	number *a = (number *)malloc(sizeof(number));
	initNumber(a);

	//The current char
	char currchar;

	//At first, we set currstate as space
	static enum state currstate = SPC;

	//The nextstate
	enum state nextstate;

	token t;

	//Resetting
	if(*reset == 1) {
		currstate = SPC;
		*reset = 0;
		i = 0;
		//t.dec = 0;
	}

	while(1){
		currchar = expr[i];
		//Whatever might be the state,we must check all the possible nextstate
		switch(currstate){
			//When currstate is number
			case NUMBER:
				switch(currchar){
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						//Appending the encountered digit to the number ADT
						nextstate = NUMBER;
						appendchar(a, currchar);
						i++;
						//We will not return unless we encounter such continous digits
						break;

					case '+': case '-': case '*': case '/': case '%': case '(' : case ')' :

						nextstate = OP;
						
						//If the previous state was NUMBER and now we have encountered an operator,then it means we recorded
						//the number and now it is time to return
						t.type = OPERAND;
						t.num = a;
						
						//Obviously now the current state will be operator
						currstate = nextstate;
						i++;
						
						return t;
						break;
					
					case '\0':
						//These all states will have the same logic as the above OP
						nextstate = FINISH;

						t.type = OPERAND;
						t.num = a;

						currstate = nextstate;

						//No i++ bcoz as soon as we encounter the END,we must stop evaluating
						return t;
						break;
						
					case ' ':
						//These all states will have the same logic as the above OP
						nextstate = SPC;

						t.type = OPERAND;
						t.num = a;

						currstate = nextstate;
						i++;

						return t;
						break;
					
					case '.':
						//These all states will have the same logic as the above OP

						//Note that dot is only of symbolic importance
						//In our operation.c,we have our numbers as sequence of digits and a dec count
						nextstate = DOT;
						i++;
						currstate = nextstate;
						break;
					
					default: 
						//This state is vital as it enables our gettoken function to handle the invalid operators
						nextstate = ERROR;

						t.type = OPERAND;
						t.num = a;

						currstate = nextstate;

						return t;
						break;
				}
				break;
				//breaks out of the outer switch case
				//This is needed when nextstate is also a number
			
			//If current state is dot
			case DOT:
				switch(currchar){
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						//Decimal Appending
						appendchar(a, currchar);
						a->dec++;
						
						//Why next state dot?
						//Coz we are collecting all the decimal digits of our number
						nextstate = DOT;

						currstate = nextstate;
						
						//We are not returning bcoz we have to collect all the decimals
						i++;
						break;

					case '+': case '-': case '*': case '/': case '%': case '(' : case ')' :

						nextstate = OP;
						
						//Obviously if we encountered a dot,then our token must be of OPERAND type
						t.type = OPERAND;
						t.num = a;

						currstate = nextstate;
						
						i++;
						return t;
						break;
					
					case '\0':
					//The obvious returning logic
						nextstate = FINISH;

						t.type = OPERAND;
						t.num = a;

						currstate = nextstate;
						return t;
						break;
					
					case ' ':
						nextstate = SPC;
						
						t.type = OPERAND;
						t.num = a;

						currstate = nextstate;

						i++;
						return t;
						break;
					
					//If character is not any of the valid characters then fire error
					default:
						nextstate = ERROR;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						return t;
						break;
				}
				break;
				//Breaking the outer switch

			//If current state is operator	
			case OP:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						
						//Returning the operator
						t.type = OPERATOR;
						//Since curr char is number,the previous char must be the operator
						t.op = expr[i - 1];
						
						nextstate = NUMBER;
						currstate = nextstate;
						
						return t;
						break;
					
					case '+': case '-': case '*': case '/': case '%': case '(' : case ')' : 
						
						//Normal returning
						nextstate = OP;
						
						t.type = OPERATOR;
						t.op = expr[i - 1];

						currstate = nextstate;
						
						i++;
						return t;
						break;

					case '\0':
					//Normal return
					//Reached EOL
						nextstate = FINISH;

						t.type = OPERATOR;
						t.op = expr[i - 1];

						currstate = nextstate;
						return t;
						break;

					case ' ':
					//Normal return
						nextstate = SPC;

						t.type = OPERATOR;
						t.op = expr[i - 1];

						currstate = nextstate;
						
						i++;
						return t;
						break;
					
					case '.':
					//Normal return
						nextstate = DOT;

						t.type = OPERATOR;
						t.op = expr[i -1];

						currstate = nextstate;

						i++;
						return t;
						break;
					
					default: // Invalid characters
						nextstate = ERROR;
						t.type = OPERATOR;
						t.op = expr[i - 1];
						currstate = nextstate;
						return t;
						break;
				}
				break;
				//Breaking the outer switch

			case FINISH:
			//The EOL
				t.type = END;
				return t;
				break;

			case ERROR:
			//ERROR case
				t.type = ERR;
				return t;
				break;

			//The starting case
			//The SPC or space will not return anything	
			case SPC:
				switch(currchar){
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
		
						appendchar(a, currchar);
						nextstate = NUMBER;

						i++;
						break;

					case '+': case '-': case '*': case '/': case '%': case '(' : case ')' :
						
						nextstate = OP;
						i++;
						break;

					case '\0':
						nextstate = FINISH;
						break;

					case ' ':
						nextstate = SPC;
						i++;
						break;
					
					case '.':
						nextstate = DOT;
						i++;
						break;
					
					default: // Invalid characters
						nextstate = ERROR;
						break;
				}
				currstate = nextstate;
				break;
		}
	}
}

//The precedence decider
int precedence(char operator){
	switch(operator){
		case ')' :
			return 0;
			break;

		case '+' :case '-' :
			return 1;
			break;

		case '*' :case '/':
			return 2;
			break;

		case '%' :
			return 3;
			break;
		
		case '(' :
			return 4;
			break;

		default :
			return 5;
			break;
	}
	return 5;
}

//The infix evaluation
number *infix(char *exp){
	//Token to be outputted by gettoken 
	token t;

	//Current operator and previous operator
	char curr_op, prev_op, ch;
	
	//Counter for open and closed brackets,reset, current and previous types of tokens
	int cnt_ob = 0, cnt_cb = 0, reset  = 1, curr, prev;
	number *a, *b, *z;

	//Numbers
	a = (number *)malloc(sizeof(number));
	b = (number *)malloc(sizeof(number));
	z = (number *)malloc(sizeof(number));

	initNumber(a);
	initNumber(b);
	initNumber(z);

	//Stacks for storing the numbers and chars
	istack is;
	cstack cs;

	iinit(&is);
	cinit(&cs);

	//Initializing the Previous state to error
	prev = ERR;

	while(1){

		//getting a token
		t = gettoken(exp, &reset);
		//Token type
		curr = t.type;

		//Handling number types
		//If token type is again a number,then we must fetch another number
		if(curr == prev && prev == OPERAND){
			return NULL;
		}

		//Pushing a number into a stack (when token is number)
		if(t.type == OPERAND){
			ipush(&is, t.num);
		}

		//If token is operator
		else if(t.type == OPERATOR){
			//Setting the current operator
			curr_op = t.op;

			//Increasing open bracket  count
			if(curr_op == '('){
				cnt_ob++;
			}
			
			//Increasing the closed bracket count
			if(curr_op == ')'){
				cnt_cb++;
			}

			//Handling the the closed bracket > open bracket
			if(cnt_cb > cnt_ob){
				return NULL;
			}

			//If operator stack is not empty
			if(!cisempty(&cs)){

				prev_op = ctop(&cs);

				//This handles the situation when precedence of operator is greater than that of top of stack
				while(precedence(prev_op) >= precedence(curr_op)){
					//popping the top of stack
					prev_op = cpop(&cs);
					
					//Popping the first operand from the operand stack 
					if(!iisempty(&is)){
						a = ipop(&is);
					}
					
					//If integer stack is empty then we cannot proceed further
					else{
						cpush(&cs, prev_op);
						break;
					}

					//Popping the second operand from the operand stack 
					if(!iisempty(&is)) {
						b = ipop(&is);
					}
					
					//Since we are dealing with only binary operators,if integer stack is not empty,we cannot proceed
					//Hence we again push the previous integer a onto stack
					else {
						cpush(&cs, prev_op);
						ipush(&is, a);
						break;
					}
					
					//Handling the ZeroDivisionError
					if((prev_op == '/' || prev_op == '%') && a == 0) {
                            fprintf(stderr, "Zero Division Error\n");
                            return NULL;
                    }

					//Evaluating the expressions with respect to operators
					switch (prev_op) {
						case '+' :
							//z = b + a;
							z = add(a, b);
							ipush(&is, z);
							break;
						case '-' :
							//z = b - a;
							z = sub(b, a);
							ipush(&is, z);
							break;
						case '*' :
							//z = b * a;
							z = mult(b, a);
							ipush(&is, z);
							break;
						case '/' :
							//z = b / a;
							z = division(b, a);
							ipush(&is, z);
							break;
						case '%' :
							//z = b % a;
							z = modulus(b, a);
							ipush(&is, z);
							break;
						
						case '(' :
							//If an opening bracket is encountered,then we push the elements again onto stack
							cpush(&cs, prev_op);
							ipush(&is, b);
							ipush(&is, a);
							break;

						default :
							return NULL;
					}
					//Highest precedence therefore break
					if (prev_op == '('){
						break;
					}
					
					if(!cisempty(&cs)){
						prev_op = ctop(&cs);
					}
					else{
						break;
					}
				}
			}

			//Finally pushing the current operator into stack
			cpush(&cs, t.op);

			//If current operator is closing bracket,then we pop the elements 
			if(curr_op == ')'){
				ch = cpop(&cs);
				cnt_cb--;
				ch = cpop(&cs);
				cnt_ob--;
			}
		}

		else if(t.type == END){
			//Check if number of open brackets and closed brackets arew equal
			if(cnt_ob == cnt_cb){
				
				//Emptying the operator stack
				while(!cisempty(&cs)){

					//Handling the less no. of operands	
					if(!iisempty(&is)){
						a = ipop(&is);
					}
					//Error firing
					else {
						fprintf(stderr, "OperandError: Less Operands\n");
                        return NULL;
					}
					//Popping out the second element
					if(!iisempty(&is)) {
						b = ipop(&is);
					}
					//Handling the empty operand error
					else {
						fprintf(stderr, "OperandError: Less Operands\n");
                        
                        return NULL;
					}
					
					ch = cpop(&cs);
					//Handling Zero Division Error
					if((ch == '/' || ch == '%') && a == 0){
						fprintf(stderr, "ZeroDivisionError: Cannot Divide by Zero\n");
						
						return NULL;
					}

					//Evaluation based on the operator
					switch(ch){
						case '+' :
							z = add(b, a);
							ipush(&is, z);
							break;
						case '-' :
							z = sub(b, a);
							ipush(&is, z);
							break;
						case '*' :
							z = mult(b, a);
							ipush(&is, z);
							break;
						case '/' :
							z = division(b, a);
							ipush(&is, z);
							break;
						case '%' :
							z = modulus(b, a);
							ipush(&is, z);
							break;
						default :
							
							return NULL;
					}
				}
			}
			//Firing the brackets unequal error
			else {
				fprintf(stderr, "BracketError: Unequal Brackets\n");
				return NULL;
			}
			//Operator stack is emptied  but operand stack is not empty
			if(!iisempty(&is)){
				
				z = ipop(&is);
				
				if(iisempty(&is)){
					return z;
				}
				else{
                    fprintf(stderr, "OperatorError: Less Operators\n");
                    return NULL;
                }
			}
		}
		//If an invalid character is entered
		else if(t.type == ERR) {
			return NULL;
		}
		//prev will now be curr
		//And in next iteration,curr will be t.type
		prev = curr;
	}
}

//Takes a line from user and handles the newline character,also returns the length of line
int readline(char *line, int len){
	int i;
	char chr;
	i = 0;

	//Reading the line
	while(i < len - 1){
		chr = getchar();
		//If newline character is encountered,then line is terminated
		if(chr == '\n'){
			line[i++] = '\0';
			return i - 1;
		}
		//Else the line is appended with characters
		else{
			line[i++] = chr;
		}
	}
	//Default case
	line[len - 1] = '\0';
	return len - 1;
}

int main(int argc, char *argv[]) {
	printf("\n");
	printf("Piezon 1.0.0 (default, Oct 17 2020, 14:00:26)\n[MinGW-W64 8.1.0] on windows \nCOEP MIS: 111903073\n");	
	number *r;
	char line[2048];
	while(readline(line, 2048)){
		r = infix(line);
		if(r != NULL)
			display(*r);
		else
			fprintf(stderr, "ExpressionError\n");
	}
	return 0;
}
