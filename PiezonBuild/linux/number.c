#include <stdio.h>
#include <stdlib.h>
#include "number.h"

//INITIALIZING A NUMBER ADT
void initNumber(number *num) {
	num->head = num->tail = NULL;
	num->dec = 0;
	num->sign = PLUS;
}

//APPENDS A CHARACTER AT THE END OF NUMBER
void appendchar(number *num, char chr) {
	//Checking if character is a number
	if(chr < '0' || chr > '9'){
		return;
	}
	//Allocating memory
	node *newnode = (node *)malloc(sizeof(node));

	//Handling Malloc Failure
	if(!newnode){
		return;
	}

	//Setting the newnode
	newnode->num = chr - '0';
	newnode->next = NULL;

	//Handling empty number case
	if((num->head == NULL) && (num->tail == NULL)) {
		
		//Linking the newnode to number
		newnode->prev = NULL;
		num->head = newnode;
		num->tail = newnode;
		return;
	}

	//Default Case (Number not empty)

	//Linking the newnode
	newnode->prev = num->tail;
	num->tail->next = newnode;
	num->tail = newnode;
	return;
}

//RETURNS THE NUMBER OF DIGITS IN A NUMBER
int length(number num) {
	//Travelling pointer
	node *traveller;
    traveller = num.head;
	
	int len_num = 0;

	while(traveller != NULL) {
		len_num++;
		traveller = traveller->next;
	}
	return len_num;
}

//PREPENDS A DIGIT TO A NUMBER
void prepend(number *number, int digit){

	//Digit must be in its limit
	if(digit < 0 || digit > 9){
		return;
	}

	//Initializing a newnode
	node *newnode = (node *)malloc(sizeof(node));

	//Handling malloc failure
	if(!newnode){
		return;
	}

	//Setting up the newnode
	newnode->num = digit;
	newnode->prev = NULL;

	//Handling empty number case
	if((number->head == NULL) && (number->tail == NULL)){
		//Linking the newnode
		newnode->next = NULL;
		number->head = number->tail = newnode;
		return;
	}
	//Default case linking
	newnode->next = number->head;
	number->head->prev = newnode;
	number->head = newnode;
	return;
}
//REMOVES A DIGIT AT A SPECIFIED LOCATION
void removdigit(number *num, int position){
	int i;
	node *traveller, *tmp;

	//Handling out of bounds	
	if(position < 0 || position >= length(*num)){
		return;
	}
	//Traveller pointer
	traveller = num->head;

	//Travelling to a position
	for(i = 0; i < position - 1; i++){
		traveller = traveller->next;
	}

	//Handling empty number
	if(num->head == NULL) {
		return;
	}
	//Handling unit length
	if(length(*num) == 1) {	
		num->head = num->tail = traveller = NULL;
		return;
	}
	//Removal from beginning
	if(position == 0) {	
		traveller->next->prev = NULL;
		num->head = traveller->next;
		free(traveller);
		return;
	}
	//Removal from the end
	if(position == length(*num) - 1) {	
		tmp = traveller->next;
		traveller->next = NULL;
		num->tail = traveller;
		free(tmp);
		return;
	}
	
	//Removing a digit at ab intermediate position
	tmp = traveller->next;
	traveller->next = traveller->next->next;
	tmp->next->prev = traveller;	
	free(tmp);
	return;
}

//Removal of leading and trailing zeroes
void zeroRemov(number *number){

	// Initializing a travelling pointer
	node *traveller = number->head;
	int i, len = length(*number);

	//Removing zeroes from integral part
	for(i = 0; i < len - number->dec - 1; i++) {
		if(traveller->num == 0) {
			
			//Delinking the node with zero
			number->head = traveller->next;
			traveller->next = NULL;
			number->head->prev = NULL;

			//Freeing memory
			free(traveller);
			traveller = number->head;
		}
		else{
			break;
		}
	}

	traveller = number->tail;
	int decimal = number->dec;

	//Removal of Trailing Zeroes
	for(i = 0; i < decimal - 1; i++) {
		if(traveller->num == 0) {
			//Delinking the node with zero
			number->tail = traveller->prev;
			traveller->prev = NULL;
			number->tail->next = NULL;
			
			//Freeing memory
			free(traveller);

			traveller = number->tail;
			number->dec--;
			
		}
		else{
			break;
		}
	}
	return;
}

//Displaying the number
void display(number num1){
	//Travelling pointer
	node *traveller;
	
	//Position
	int position = 0;
	
	//Removing the zeroes if any
	zeroRemov(&num1);
	traveller = num1.head;

	//Printing the sign
	if(num1.sign == MINUS) {
		printf("-");
		num1.sign = PLUS;
	}
	
	//Printing the number
	while(traveller != NULL) {
		position++;
		
		//Printing the decimal point
		if(position == (length(num1) - num1.dec + 1)){
			printf(".");
		}

		printf("%d", traveller->num);
		traveller = traveller->next;
	}
	printf("\n");
}