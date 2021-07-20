#include<stdio.h>

//INPUTTING AN INTEGER MATRIX
void mtxin(int item,int row, int col, int array[row][col]){
	int i,j;
	for(i = 0; i< row; i++){
		for(j = 0; j<col; j++){
			printf("m%d%d : ",i,j);
			scanf("%d",&item);
			array[i][j] = item;
		}
	}
}

//INPUTTING AN FLOAT MATRIX
void fmtxin(float item,int row, int col, float array[row][col]){
	int i,j;
	for(i = 0; i< row; i++){
		for(j = 0; j<col; j++){
			printf("m%d%d : ",i,j);
			scanf("%f",&item);
			array[i][j] = item;
		}
	}
}

//OUTPUTTING AN INTEGER MATRIX
void mtxout(int row, int col, int array[row][col]){
	int i,j;
	for(i = 0; i< row; i++){
		for(j = 0; j<col; j++){
			printf("%3d",array[i][j]);
		}
		printf("\n");
	}
}

//OUTPUTTING AN FLOAT MATRIX
void fmtxout(int row, int col, float array[row][col]){
	int i,j;
	for(i = 0; i< row; i++){
		for(j = 0; j<col; j++){
			printf("%6.2f",array[i][j]);
		}
		printf("\n");
	}
}

//TRANSPOSE OF AN INTEGER MATRIX
void transpose(int row, int col, int array[row][col]){
	int i,j,k = 0;
	int temp1,temp2;
	for(i = 0; i<row; i++){
		for(j = k; j<col; j++){
			temp1 = array[i][j];
			temp2 = array[j][i] ;
			array[j][i] = temp1;
			array[i][j] = temp2;  
		}
		k++;
	}
}

//TRANSPOSE OF A FLOAT MATRIX
void ftranspose(int row, int col, float array[row][col]){
	int i,j,k = 0;
	float temp1,temp2;
	for(i = 0; i<row; i++){
		for(j = k; j<col; j++){
			temp1 = array[i][j];
			temp2 = array[j][i] ;
			array[j][i] = temp1;
			array[i][j] = temp2;  
		}
		k++;
	}
}

// UPPER TRIANGULAR MATRIX
void utm(int row, int col,int array[row][col] ){
	int i,j;
	for(i = 0; i<row; i++ ){
		for(j = 0; j<col; j++){
			if(i>j){
				array[i][j] = 0;
			}
		}
	}
}

// UPPER TRIANGULAR MATRIX (FLOAT)
void futm(int row, int col,float array[row][col] ){
	int i,j;
	for(i = 0; i<row; i++ ){
		for(j = 0; j<col; j++){
			if(i>j){
				array[i][j] = 0;
			}
		}
	}
}

// LOWER TRIANGULAR MATRIX
void ltm(int row, int col,int array[row][col] ){
	int i,j;
	for(i = 0; i<row; i++ ){
		for(j = 0; j<col; j++){
			if(j>i){
				array[i][j] = 0;
			}
		}
	}
}

// LOWER TRIANGULAR MATRIX (FLOAT)
void fltm(int row, int col,float array[row][col] ){
	int i,j;
	for(i = 0; i<row; i++ ){
		for(j = 0; j<col; j++){
			if(j>i){
				array[i][j] = 0;
			}
		}
	}
}
