#include <stdio.h>
#include <stdlib.h>
#include "number.h"
#include "operation.h"

//Function to equal the digits after decimal point.
void makeDecimalEqual(number *num1, number *num2) {
	int i;

	//If num1 has more decimal digits at end
	if(num1->dec > num2->dec) {
		int diff = num1->dec - num2->dec;
		
		//Adding zeroes to decimal part num2
		for(i = 0; i < diff; i++) {
			appendchar(num2, '0');
			num2->dec++;
		}
	}
	//If num2 has more decimal digits
	else if(num2->dec > num1->dec) {

		int diff = num2->dec - num1->dec;
		//Adding zeroes to decimal part of num1
		for(i = 0; i < diff; i++) {
			appendchar(num1, '0');
			num1->dec++;
		}
	}
}

//Equals the length of both numbers by prepending zeros to small number.
void makeLengthEqual(number *num1, number *num2) {
	int gap;

	//Difference in lengths 
	gap = length(*num1) - length(*num2);
	
	//If num1 is bigger
	if(gap > 0) {
		int i = 0;
		
		//Adding zeroes to left of smaller number
		while(i < gap) {
			prepend(num2, 0);
			i++;
		}
	}
	//Else num2 is bigger
	else if(gap < 0) {
		int i = 0;
		gap = -gap;
		
		//Adding zeroes to left of smaller number
		while(i < gap) {
			prepend(num1, 0);
			i++;
		}
	}
}

//checks whether the number is zero or not. returns 0 if it is zero number.
int isNonZero(number num1) {
	int i, truth = 0;

	//Travelling pointer
	node *traveller = num1.head;
	
	for(i = 0; i < length(num1); i++) {
		if(traveller->num != 0){
			truth = 1;
		}
		traveller = traveller->next;
	}
	return truth;
}

//copies number a in number b.
void copy(number *num1, number *num2){
	//length,digit and iterating number
	int i, digit, len;
	char chr;
	len = length(*num1);
	
	//Travelling pointer
	node *traveller = num1->head;

	//Here num2 inherits value of num1
	for(i = 0; i < len; i++){
		digit = traveller->num;

		//Next character to be inserted
		chr = digit + '0';
		appendchar(num2, chr);

		traveller = traveller->next;
	}

	//Here num2 will inherit its sign and number of decimals from num1
	num2->dec = num2->dec;
	num2->sign = num2->sign;
	return;
}

//Addition Operation a=num1,b=num2
number *add(number *num1, number *num2) {

	//The final answer of addition
	number *ans;
	ans = (number *)malloc(sizeof(number));
	initNumber(ans);
	
	//Equalizing the number of decimals
	makeDecimalEqual(num1, num2);

	//Hanling unequal signs
	if(num1->sign != num2->sign){
		
		// -A+B = B - A
		if(num1->sign == MINUS) {
			num1->sign = PLUS;
			ans = sub(num2, num1);
		}

		// A + (-B) = A - B
		else if(num2->sign == MINUS) {
			num2->sign = PLUS;
			ans = sub(num1, num2);
		}
	}

	//Signs are equal now
	else if(num1->sign == num2->sign){

		int i, n1, n2, carry = 0, sum;
		int len_1, len_2;

		node *t1 = num1->tail;
		node *t2 = num2->tail;
		
		len_1 = length(*num1);
		len_2 = length(*num2);
		
		//Sign of answer
		if(num1->sign == MINUS){
			ans->sign = MINUS;
		}
		else{
			ans->sign = PLUS;
		}
		
		//If A is greater than B
		if(len_1 >= len_2) {
			for(i = 1; i <= len_2; i++){
				//Digits from num1 and num2
				n1 = t1->num;
				n2 = t2->num;

				sum = n1 + n2 + carry;
				carry = sum / 10;
				sum = sum % 10;

				prepend(ans, sum);

				t1 = t1->prev;
				t2 = t2->prev;
			}
			//Since length of num1 is greater than num2,
			//we have to prepend digits of num1.
			for(i = 1; i <= len_1 - len_2; i++){
				n1 = t1->num;

				//Last carry from num2
				sum = n1 + carry;
				
				carry = sum / 10;
				sum = sum % 10;

				prepend(ans, sum);
				t1 = t1->prev;
			}
		}
		//If B is greater than A
		else {
			for(i = 1; i <= len_1; i++) {
				//Digits from num1 and num2
				n1 = t1->num;
				n2 = t2->num;
				
				sum = n1 + n2 +carry;
				carry = sum / 10;
				sum = sum % 10;

				prepend(ans, sum);
				t1 = t1->prev;
				t2 = t2->prev;
			}
			//Since length of num2 is greater than num1,
			//we have to prepend digits of num2.
			for(i = 1; i <= len_2 - len_1; i++) {
				n1 = t2->num;

				//Last carry from num1
				sum = n1 + carry;

				carry = sum / 10;
				sum = sum % 10;

				prepend(ans, sum);
				t2 = t2->prev;
			}
		}

		ans->dec = num1->dec;

		//End around Carry	
		if(carry != 0){
			prepend(ans, carry);
		}
	}
	return ans;
}

// Comparing two numbers
int isEqual(number num1, number num2){
	
	//Making both numbers equal
	makeLengthEqual(&num1, &num2);
	makeDecimalEqual(&num1, &num2);
	
	//Travelling pointers
	node *t1, *t2;

	int len;
	int i;

	len = length(num1);

	t1 = num1.head;
	t2 = num2.head;
	
	//Bitwise comparison (starting from the head)
	for(i = 1; i <= len; i++){

		if(t1->num > t2->num){
			return 1;  //A is greater than B
		}

		else if(t1->num < t2->num){
			return -1;  //B is greater than A
		}
		t1 = t1->next;
		t2 = t2->next;
	}

	return 0;    //A  = B
}

//Subtraction operation.
number *sub(number *num1, number *num2) {
	
	//Final answer of subtraction
	number *ans;
	ans = (number *)malloc(sizeof(number));
	initNumber(ans);
	
	//decimal digits and length made equal.
	makeDecimalEqual(num1, num2);
	makeLengthEqual(num1, num2);

	//Handling unequal signs
	if(num1->sign != num2->sign){
		//If num1 is -ve
		if(num1->sign == MINUS) {
			num1->sign = PLUS;
			
			// -A-B = -(A+B)
			ans = add(num1, num2);
			ans->sign = MINUS;
		}
		//if num2 is -ve
		else if(num2->sign == MINUS){

			num2->sign = PLUS;
			// A - (-B) = A + B 
			ans = add(num1, num2);
			ans->sign = PLUS;
		}
	}
	else if(num1->sign == num2->sign){
		
		//Handling equal and negative signs
		if(num1->sign == MINUS) {
			num1->sign = num2->sign = PLUS;
			ans = sub(num2, num1);
		}
		
		//Main Code
		else if(num1->sign == PLUS){
			int n1, n2, diff, borrow = 0, i, len;

			//Travelling pointers
			node *t1 = num1->tail;
			node *t2 = num2->tail;

			//length of both numbers is same now because of makeLengthEqual.
			len = length(*num2);

			//If A > B
			if(isEqual(*num1, *num2) == 1){
				
				for(i = 1; i <= len; i++){
					n1 = t1->num;
					n2 = t2->num;
					
					//Adding the borrow if any
					n1 = n1 - borrow;
					
					//If digit n1 is greater than both n2+borow
					//then the next digit will not have a borrow
					if(n1 >= n2){
						diff = n1 - n2;
						borrow = 0;
						prepend(ans, diff);
					}
					//If n1 is not greater than n2+borrow then,
					//borrow will propagate to next digit
					//Borrow can be atmost 1
					else {
						n1 = n1 + 10;
						diff = n1 - n2;
						borrow = 1;
						prepend(ans, diff);
					}
					//Travelling to next digit
					t1 = t1->prev;
					t2 = t2->prev;
				}	
			}
			//If B > A
			else if(isEqual(*num1, *num2) == -1){
				// A - B is negative if B is greater than A
				ans->sign = MINUS;
				
				//The process is same as in above block of code
				for(i = 1; i <= len; i++){
					n1 = t1->num;
					n2 = t2->num;
					
					//Adding the borrow if any
					n2 = n2 - borrow;

					//If digit n2 is greater than both n1+borow
					//then the next digit will not have a borrow
					if(n2 >= n1) {
						diff = n2 - n1;
						borrow = 0;
						prepend(ans, diff);
					}
					//If n2 is not greater than n1+borrow then,
					//borrow will propagate to next digit
					//Borrow can be atmost 1
					else {
						n2 = n2 + 10;
						diff = n2 - n1;
						borrow = 1;
						prepend(ans, diff);
					}
					//Travelling to next digit
					t1 = t1->prev;
					t2 = t2->prev;
				}	
			}

			//If A = B then A  - B = 0
			else{
				if(isEqual(*num1, *num2) == 0) {
					prepend(ans, 0);
				}
			}
		}
	}
	//Answer must inherit the decimals
	ans->dec = num1->dec;
	return ans;
}

//Multiplication Operation.
number *mult(number *num1, number *num2){

	//The final result of multiplication
	number *ans = (number *)malloc(sizeof(number));
	initNumber(ans);
	
	//checks if any one of the numbers is zero.
	if((isNonZero(*num1) == 0) || (isNonZero(*num2) == 0)){
		appendchar(ans, '0');
		return ans;
	}

	//Difference of lengths
	int lengthdiff;

	//Handling equal signs
	if(num1->sign == num2->sign) {
		ans->sign = PLUS;
		num1->sign = num2->sign = PLUS;
	}
	//Handling unequal signs
	else{
		ans->sign = MINUS;
		num1->sign = num2->sign = PLUS;
	}

	lengthdiff = length(*num1) - length(*num2);
	
	//Handling num2 > num1
	if(lengthdiff < 0) {
		ans = mult(num2, num1);
		return ans;
	}

	//Main Code
	else {
		//Travelling pointers
		node *t1, *t2;

		//Lengths of numbers
		int len_1 = length(*num1);
		int len_2 = length(*num2);

		//The tempresult stores the final digits after multiplication
		int i, j, n1 = 0, n2 = 0;
		int tempresult[2 * len_1];

		//Initializing the the tempresult
		for(i = 0; i < 2 *len_1; i++){
			tempresult[i] = 0;
		}

		int k = 2 * len_1 - 1;
		t2 = num2->tail;
		
		//The variables i and j are adjusted such that shift becomes possible when the inner for loop breaks
		for(i = 0; i < len_2; i++){

			//Initializing the tail
			t1 = num1->tail;
			
			int prev_carry = 0, next_carry = 0;

			for(j = k - i; j > len_1 - 2; j--){

				if(t1 != NULL && t2 != NULL){
					n1 = t1->num * t2->num + prev_carry;
					t1 = t1->prev;

					prev_carry = n1 / 10;
					
					n1 = n1 % 10;
					n2 = tempresult[j] + n1 + next_carry;
					
					next_carry = n2 / 10;
					n2 = n2 % 10;
					
					tempresult[j] = n2;
				}
				else {
					break;
				}
			}

			tempresult[j] = prev_carry + next_carry + tempresult[j];
			len_1--;
			t2 = t2->prev;	
		}

		for(i = k; i >= len_1 - 1 && i >= 0; i--) {
			prepend(ans, tempresult[i]);
		}

		ans->dec = num1->dec + num2->dec;
		return ans;
	}
}

//Division Operation.
number *division(number *num1, number *num2){

	//Handling Zero Division Error
	if(isNonZero(*num2) == 0) {
		printf("ZeroDivisionError: division by zero is undefined.\n");
		return NULL; 
	}

	//Removing zeroes from num1 and num2
	zeroRemov(num1);
	zeroRemov(num2);
	
	//Decimals of greater number
	int k = num1->dec > num2->dec ? num1->dec : num2->dec;
	int i = 0;
	
	//Converting into integer by multiplying with 10
	while(i < k) {
		if(num1->dec > 0)
			num1->dec--;
		else
			appendchar(num1, '0');
		if(num2->dec > 0)
			num2->dec--;
		else
			appendchar(num2, '0');
		i++;
	}

	//Main Code
	i = 9;

	number *c, *d, *ans, *q, *pro;
	c = (number *)malloc(sizeof(number));
	d = (number *)malloc(sizeof(number));
	ans = (number *)malloc(sizeof(number));
	pro = (number *)malloc(sizeof(number));
	q = (number *)malloc(sizeof(number));
	
	initNumber(ans);
	initNumber(c);
	initNumber(q);
	initNumber(d);

	//Handling the Signs
	if(num1->sign == num2->sign) {
		q->sign = PLUS;
		num1->sign = num2->sign = PLUS;
	}
	else {
		q->sign = MINUS;
		num1->sign = num2->sign = PLUS;
	}

	node *p = num1->head;
	char ch = p->num + '0';

	appendchar(d, ch);

	while(q->dec < SCALE){
		//Checks if the first digit is greater than num2*(c) where 0<c<10

		while(i >= 0){

			prepend(c, i);
			pro = mult(num2, c);
			ans = sub(d, pro);
			
			//This tells us that the first digit of number is greater than num2*(c)
			if(ans->sign != MINUS){

				//Quotient will get appended
				appendchar(q, i + '0');

				//c is made empty for further processing
				node *tmp = c->head;
				free(tmp);
				c->head = c->tail = NULL;
				break;
			}
			//But if first digit is not greater than num2*(c) the quotient will not get appended
			else{
				//Just c is made empty
				node *tmp = c->head;
				free(tmp);
				c->head = c->tail = NULL;
				i--; 
			}
		}
		//d is made the ans (division is repeated subtraction)
		d = ans;
		
		//Now the next digit of number is appended and the subtraction goes on
		if(p->next != NULL){
			p = p->next;
			ch = p->num + '0';
			appendchar(d, ch);
		}
		//But if num1 gets empty,no of decimals incremented by one and its must get
		else{	
			q->dec++;	
			appendchar(d, '0');
		}

		i = 9;
		//Emptying c for further processing
		node *tmp = c->head;
		free(tmp);
		c->head = c->tail = NULL;
	}
	
	q->dec--;
	return q;
}

//Function which gives the modulo
number *modulus(number *num1, number *num2){

	//Handling division ny zero
	if(isNonZero(*num2) == 0) {
		printf("ZeroDivisionError : Modulo by Zero is not allowed.\n");
		return NULL;
	}
	//This will be the final sign of answer
	int tempsign;

	//Handling negative sign
	if(num1->sign == MINUS) {
		tempsign = MINUS;
		num1->sign = num2->sign = PLUS;
	}

	else{
		tempsign = PLUS;
		num1->sign = num2->sign = PLUS;
	}
	
	//Making the decimals equal
	makeDecimalEqual(num1, num2);

	//Number of decimals after decimal point
	int a_dec = num1->dec;

	//Final result of modulo
	number *ans = (number *)malloc(sizeof(number));
	number *temp = (number *)malloc(sizeof(number));
	initNumber(ans);
	initNumber(temp);

	//Dividing A/B
	temp = division(num1, num2);

	//Remaoval of decimal numbers (modulo is an integer) OR WE CAN SAY FLOORING THE DIVISION
	if(temp->dec != 0){
		//position of last digit
		int pos = length(*temp) - 1; 

		//Removal of all decimal digits by position
		while(temp->dec != 0){
			removdigit(temp, pos);
			temp->dec--;
			pos--;
		}
	}
	//Now A%B = A - (A//B)*B, therfore temp is multiplied by B i.e. num2
	temp = mult(temp, num2);
	ans = sub(num1, temp);

	ans->sign = tempsign;
	ans->dec = a_dec;
	return ans;
}