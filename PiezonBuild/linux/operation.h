//Scale is defined to handle the non terminating decimals
#define SCALE 31

//Operations
number *add(number *num1, number *num2);
number *sub(number *num1, number *num2);
number *mult(number *num1, number *num2);
number *division(number *num1, number *num2);
number *modulus(number *a, number *b);

//Utility functions
int isEqual(number a, number b);
void makeDecimalEqual(number *num1, number *num2);
int isNonZero(number num1);
void copy(number *num1, number *num2);