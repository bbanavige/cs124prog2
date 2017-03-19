/*

Header file with functions for strassen.c

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* conventional matrix multiplication

INPUT: 	A - n x n matrix
		B - n x n matrix
		C - n x n matrix (C = A * B)
		n - dimention of A and B

OUTPUT:	nothing, but changes C to be A * B by reference

*/
void con(int** A, int** B, int** C, int n){
	for (int i = 0; i < n; i++){
		C[i] = malloc(n * sizeof(int));
	}

	int temp;

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			temp = 0;
			for (int k = 0; k < n; k++){
				temp += A[i][k] * B[k][j];
			}
			C[i][j] = temp;
		}
	}
}