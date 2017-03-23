/***********
 * CS 124 Programming Assignment 2
 * 70940507 and 30978137
***********/

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Prototypes
void con(int n, int A[n][n], int B[n][n], int C[n][n]);
void mat_add(int n, int a[n][n], int b[n][n], int c[n][n]);
void mat_sub(int n, int a[n][n], int b[n][n], int c[n][n]);
void strassen(int n, int A[n][n], int B[n][n], int C[n][n]);
void import(int n, int A[n][n], int B[n][n], char* infile);
void print_mat(int n, int A[n][n]);
void print_diag(int n, int A[n][n]);
void sim(int n, int type, char* outfile);

// Main Function
int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: ./strassen 0 dimension inputfile");
        return -1;
    }

    int n = atoi(argv[2]);
    char* inputfile = argv[3];
    
    int* A = malloc(sizeof(int) * n * n);
    int* B = malloc(sizeof(int) * n * n);
    int* C = malloc(sizeof(int) * n * n);

    import(n, (int (*)[n]) A, (int (*)[n]) B, inputfile);

    // conventional mult
    strassen(n, (int (*)[n]) A, (int (*)[n]) B, (int (*)[n]) C);
    print_diag(n, (int (*)[n]) C);
}   

// functions
/* conventional matrix multiplication

INPUT: 	A - n x n matrix
		B - n x n matrix
		C - n x n matrix (C = A * B)
		n - dimention of A and B

OUTPUT:	nothing, but changes C to be A * B by reference

*/
void con(int n, int A[n][n], int B[n][n], int C[n][n]) {

    // initialize C to hold all 0s
	for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            C[i][k] = 0;

    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            for (int j = 0; j < n; j++)
                C[i][j] += A[i][k]*B[k][j];

}

// adds matrices
void mat_add(int n, int a[n][n], int b[n][n], int c[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c[i][j] = a[i][j] + b[i][j];
}

// subtracts matrices
void mat_sub(int n, int a[n][n], int b[n][n], int c[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c[i][j] = a[i][j] - b[i][j];
}

/* Strassen's Algorithm

Same input and Output as the traditional

*/

void strassen(int n, int A[n][n], int B[n][n], int C[n][n]) {
    bool odd = n % 2;
    // BASE CASE
    if (!odd && n < 16) {
        con(n, A, B, C); 
        return;
    }
    else if (n < 38) {
        con(n, A, B, C);
        return;
    }

    // create splits
    int newsize = odd ? n / 2 + 1 : n / 2;
    int* a11 = malloc(sizeof(int) * newsize * newsize);
    int* a12 = malloc(sizeof(int) * newsize * newsize); 
    int* a21 = malloc(sizeof(int) * newsize * newsize);
    int* a22 = malloc(sizeof(int) * newsize * newsize);
    int* b11 = malloc(sizeof(int) * newsize * newsize);
    int* b22 = malloc(sizeof(int) * newsize * newsize);
    int* b21 = malloc(sizeof(int) * newsize * newsize);
    int* b12 = malloc(sizeof(int) * newsize * newsize);
    
    // upper left quadrant
    for (int i = 0; i < newsize; i++)
        for (int k = 0; k < newsize; k++) {
            a11[i*newsize + k] = A[i][k];
            b11[i*newsize + k] = B[i][k];
        }
    
    // upper right quadrant
    for (int i = 0; i < newsize; i++)                                           
        for (int k = newsize; k < n; k++) {                                     
            a12[i*newsize + (k-newsize)] = A[i][k];                                                
            b12[i*newsize + (k-newsize)] = B[i][k];                                                
        } 
    // lower left quadrant
    for (int i = newsize; i < n; i++)                                           
        for (int k = 0; k < newsize; k++) {                                     
            a21[(i-newsize)*newsize + k] = A[i][k];                                                
            b21[(i-newsize)*newsize + k] = B[i][k];                                                
        } 

    // lower right quadrant
    for (int i = newsize; i < n; i++)
        for (int k = newsize; k < n; k++) {
            a22[(i-newsize)*newsize + (k-newsize)] = A[i][k];                                                
            b22[(i-newsize)*newsize + (k-newsize)] = B[i][k];                                                
        }

    // pad if necessary 
    if (odd) {
        for (int i = 0; i < newsize; i++) {
            a21[(newsize-1)*newsize + i] = 0;
            b21[(newsize-1)*newsize + i] = 0;
            a22[(newsize-1)*newsize + i] = 0;
            b22[(newsize-1)*newsize + i] = 0;
            a22[i*newsize + newsize-1] = 0;
            b22[i*newsize + newsize-1] = 0;
            a12[i*newsize + newsize-1] = 0;
            b12[i*newsize + newsize-1] = 0;
        }
    } 

    // build m1 through m7
    int* temp1 = malloc(sizeof(int) * newsize * newsize);
    int* temp2 = malloc(sizeof(int) * newsize * newsize); 
    int* m1 = malloc(sizeof(int) * newsize * newsize);
    int* m2 = malloc(sizeof(int) * newsize * newsize);
    int* m3 = malloc(sizeof(int) * newsize * newsize);
    int* m4 = malloc(sizeof(int) * newsize * newsize);
    int* m5 = malloc(sizeof(int) * newsize * newsize);
    int* m6 = malloc(sizeof(int) * newsize * newsize);
    int* m7 = malloc(sizeof(int) * newsize * newsize);

    // Note the pointer conversions, for ease later on --> in C there is no cost for typecasting
    mat_add(newsize, (int (*)[newsize]) a11, (int (*)[newsize]) a22, (int (*)[newsize]) temp1);
    mat_add(newsize, (int (*)[newsize]) b11, (int (*)[newsize]) b22, (int (*)[newsize]) temp2);
    strassen(newsize, (int (*)[newsize]) temp1, (int (*)[newsize]) temp2, (int (*)[newsize]) m1);

    mat_add(newsize, (int (*)[newsize]) a21, (int (*)[newsize]) a22, (int (*)[newsize]) temp1);
    strassen(newsize, (int (*)[newsize]) temp1, (int (*)[newsize]) b11, (int (*)[newsize]) m2);
    
    mat_sub(newsize, (int (*)[newsize]) b12, (int (*)[newsize]) b22, (int (*)[newsize]) temp1);
    strassen(newsize, (int (*)[newsize]) a11, (int (*)[newsize]) temp1, (int (*)[newsize]) m3);

    mat_sub(newsize, (int (*)[newsize]) b21, (int (*)[newsize]) b11, (int (*)[newsize]) temp1);
    strassen(newsize, (int (*)[newsize]) a22, (int (*)[newsize]) temp1, (int (*)[newsize]) m4);

    mat_add(newsize, (int (*)[newsize]) a11, (int (*)[newsize]) a12, (int (*)[newsize]) temp1);
    strassen(newsize, (int (*)[newsize]) temp1, (int (*)[newsize]) b22, (int (*)[newsize]) m5);

    mat_sub(newsize, (int (*)[newsize]) a21, (int (*)[newsize]) a11, (int (*)[newsize]) temp1);
    mat_add(newsize, (int (*)[newsize]) b11, (int (*)[newsize]) b12, (int (*)[newsize]) temp2);
    strassen(newsize, (int (*)[newsize]) temp1, (int (*)[newsize]) temp2, (int (*)[newsize]) m6);

    mat_sub(newsize, (int (*)[newsize]) a12, (int (*)[newsize]) a22, (int (*)[newsize]) temp1);
    mat_add(newsize, (int (*)[newsize]) b21, (int (*)[newsize]) b22, (int (*)[newsize]) temp2);
    strassen(newsize, (int (*)[newsize]) temp1, (int (*)[newsize]) temp2, (int (*)[newsize]) m7);
    
    // create c set --> be clever and reuse the set of matrices from splitting a
    mat_sub(newsize, (int (*)[newsize]) m4, (int (*)[newsize]) m5, (int (*)[newsize]) temp1);
    mat_add(newsize, (int (*)[newsize]) m1, (int (*)[newsize]) m7, (int (*)[newsize]) temp2);
    mat_add(newsize, (int (*)[newsize]) temp1, (int (*)[newsize]) temp2, (int (*)[newsize]) a11);
    
    mat_add(newsize, (int (*)[newsize]) m3, (int (*)[newsize]) m5, (int (*)[newsize]) a12);

    mat_add(newsize, (int (*)[newsize]) m2, (int (*)[newsize]) m4, (int (*)[newsize]) a21);

    mat_sub(newsize, (int (*)[newsize]) m1, (int (*)[newsize]) m2, (int (*)[newsize]) temp1);
    mat_add(newsize, (int (*)[newsize]) m3, (int (*)[newsize]) m6, (int (*)[newsize]) temp2);
    mat_add(newsize, (int (*)[newsize]) temp1, (int (*)[newsize]) temp2, (int (*)[newsize]) a22);
    
    // merge back together
    for (int i = 0; i < newsize; i++)
        for (int j = 0; j < newsize; j++)
            C[i][j] = a11[i*newsize + j];

    for (int i = 0; i < newsize; i++)
        for (int j = newsize; j < n; j++)
            C[i][j] = a12[i*newsize + (j-newsize)];

    for (int i = newsize; i < n; i++)
        for (int j = 0; j < newsize; j++)
            C[i][j] = a21[(i-newsize)*newsize + j];
        
    for (int i = newsize; i < n; i++)
        for (int j = newsize; j < n; j++)
            C[i][j] = a22[(i-newsize)*newsize + (j-newsize)];

    // memory cleanup
    free(a11); free(a12); free(a21); free(a22); free(b11); free(b12); free(b21);
    free(b22); free(temp1); free(temp2); free(m1); free(m2); free(m3); free(m4);
    free(m5); free(m6); free(m7);
}

/* imports from file

INPUT: 	A - n x n matrix to store data
		B - n x n matrix to store data
		n - dimention of A and B
		infile - file address

OUTPUT:	nothing, but changes A and B by reference

*/
void import(int n, int A[n][n], int B[n][n], char* infile) {
	FILE *file = fopen(infile, "r");
    int i = 0;
    int num;
    for (int i = 0; i < n; i++) {
    	for (int j = 0; j < n; j++) {
    		fscanf(file, "%d", &num);
    		A[i][j] = num;
        }
    }
 	for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
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
void sim(int n, int type, char* outfile) {
	FILE* file = fopen(outfile, "w+");

	char* c;
	int a;

	// randomly generate A
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fprintf(file, "%d\n", rand() % 2);
		}
	}

	// randomly generate B
	for (int i = 0; i < n; i++ ){
		for (int j = 0; j < n; j++) {
			fprintf(file, "%d\n", rand() % 2);
		}
	}

	fclose(file);
}

// print matrix A, which is n x n
void print_mat(int n, int A[n][n]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%i\t", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

// print values along the diagonals of matrix A
void print_diag(int n, int A[n][n]) {
    for (int i = 0; i < n; i++)
        printf("%d\n", A[i][i]);
}

