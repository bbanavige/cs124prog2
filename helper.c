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

/* imports from file

INPUT: 	A - n x n matrix to store data
		B - n x n matrix to store data
		n - dimention of A and B
		infile - file address

OUTPUT:	nothing, but changes A and B by reference

*/
void import(int** A, int** B, int n, char* infile){
	FILE *file = fopen(infile, "r");
    int i=0;
    int num;
    for (int i = 0; i < n; i++){
    	for (int j = 0; j < n; j++){
    		fscanf(file, "%d", &num);
    		A[i][j] = num;
    	}
    }
 	for (int i = 0; i < n; i++){
    	for (int j = 0; j < n; j++){
    		fscanf(file, "%d", &num);
    		B[i][j] = num;
    	}
    }
    fclose(file);
}

/* imports from file

INPUT: 	A - n x n matrix to store data
		B - n x n matrix to store data
		n - dimention of A and B
		type - type of random simulation

OUTPUT:	nothing, but changes A and B by reference

*/
void sim(int n, int type, char* outfile){
	FILE* file = fopen(outfile, "w+");

	char* c;
	int a;

	// randomly generate A
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			fprintf(file, "%d\n", rand() % 2);
		}
	}

	// randomly generate B
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			fprintf(file, "%d\n", rand() % 2);
		}
	}

	fclose(file);
}

// print matrix A, which is n x n
void print_mat(int** A, int n){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			printf("%i\t", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}



