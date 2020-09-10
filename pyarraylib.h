#include<stdio.h>

/* 1 Dimensional Integer and Float Arrays*/

//INPUTTING AN INTEGER ARRAY
void intarrayin(int item,int size,int array[size]){
	int i;
	for(i = 0; i<size;i++){
		printf("Item%d : ",i);
		scanf("%d",&item);
		array[i] = item;
	}
}

// INPUTTING A FLOAT ARRAY
void farrayin(float item,int size,float array[size]){
	int i;
	for(i = 0; i<size;i++){
		printf("Item%d : ",i);
		scanf("%f",&item);
		array[i] = item;
	}
}

//DELETING INTEGER ARRAY ELEMENTS BY INDEX
void delint(int index,int size, int array[size]){
	int temp1 = 0,temp2 = array[size-1];
	
	for(int i = size-1; i>index; i--){
		temp1 = array[i-1];
		array[i-1] = temp2;
		temp2 = temp1;	
	}
	size--;	
}

//DELETING FLOAT ARRAY ELEMENTS BY INDEX
void delf(int index,int size, float array[size]){
	float temp1 = 0,temp2 = array[size-1];
	
	for(int i = size-1; i>index; i--){
		temp1 = array[i-1];
		array[i-1] = temp2;
		temp2 = temp1;	
	}
	size --;
}

//INVERTING AN INTEGER ARRAY
void invert(int size, int array[size]){
	int i,temp1,temp2;
	for(i = 0;i<size/2;i++){
		temp2 = array[size-1-i] ;
		temp1 = array[i];
		array[i] = temp2;
		array[size-1-i] = temp1;	
	}
}

//INVERTING A FLOAT ARRAY
void finvert(int size, float array[size]){
	int i,temp1,temp2;
	for(i = 0;i<size/2;i++){
		temp2 = array[size-1-i] ;
		temp1 = array[i];
		array[i] = temp2;
		array[size-1-i] = temp1;	
	}
}

//COPYING AN INTEGER ARRAY
void copyintarray(int size,int array1[size],int array2[size]){
	int i;
	for(i = 0;i<size;i++){
		array2[i] = array1[i];
	}
}

//COPYING FLOAT ARRAY
void copyfarray(int size,float array1[size],float array2[size]){
	int i;
	for(i = 0;i<size;i++){
		array2[i] = array1[i];
	}
}

//OUTPUTTING AN  INTEGER ARRAY
void intarrayout(int size,int array[size]){
	int i;
	for(i = 0; i<size; i++){
		printf(" %d ",array[i]);
	}
	printf("\n");
}

//OUTPUTTING A FLOAT ARRAY
void farrayout(int size,float array[size]){
	int i;
	for(i = 0; i<size; i++){
		printf(" %f ",array[i]);
	}
	printf("\n");
}
