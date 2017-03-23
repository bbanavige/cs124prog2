/***********
 * CS 124 Programming Assignment 2
 * 70940507 and 30978137
***********/

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

// Prototypes
void con(int n, int A[n][n], int B[n][n], int C[n][n]);
void mat_add(int n, int a[n][n], int b[n][n], int c[n][n]);
void mat_sub(int n, int a[n][n], int b[n][n], int c[n][n]);
void strassen(int n, int A[n][n], int B[n][n], int C[n][n]);
void import(int n, int A[n][n], int B[n][n], char* infile);
void print_mat(int n, int A[n][n]);
void sim(int n, int type, char* outfile);

// Main Function
int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: ./strassen 0 dimension inputfile");
        return -1;
    }

    int n = atoi(argv[2]);
    char* inputfile = argv[3];
    
    int A[n][n], B[n][n], C[n][n];

    import(n, A, B, inputfile);

    // conventional mult
    con(n,A,B,C);
    print_mat(n,C);
    strassen(n,A,B,C);
    print_mat(n,C);
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
    // BASE CASE
    if (n == 1)
        C[0][0] = A[0][0] * B[0][0];

    // create splits
    bool odd = n % 2;
    int newsize = odd ? n / 2 : n / 2 + 1;
    int a11[newsize][newsize], a12[newsize][newsize], a21[newsize][newsize],
        a22[newsize][newsize], b11[newsize][newsize], b12[newsize][newsize],
        b21[newsize][newsize], b22[newsize][newsize];

    for (int i = 0; i < newsize; i++)
        for (int k = 0; k < newsize; k++) {
            a11[i][k] = A[i][k];
            b11[i][k] = B[i][k];
        }

    for (int i = 0; i < newsize; i++)                                           
        for (int k = newsize; k < n; k++) {                                     
            a21[i][k-newsize] = A[i][k];                                                
            b21[i][k-newsize] = B[i][k];                                                
        } 

    for (int i = newsize; i < n; i++)                                           
        for (int k = 0; k < newsize; k++) {                                     
            a12[i-newsize][k] = A[i][k];                                                
            b12[i-newsize][k] = B[i][k];                                                
        } 

    for (int i = newsize; i < n; i++)
        for (int k = newsize; k < n; k++) {
            a22[i-newsize][k-newsize] = A[i][k];                                                
            b22[i-newsize][k-newsize] = B[i][k];                                                
        }

    // pad if necessary 
    if (!odd) {
        for (int i = 0; i < newsize; i++) {
            a12[newsize-1][i] = 0;
            b12[newsize-1][i] = 0;
            a22[newsize-1][i] = 0;
            b22[newsize-1][i] = 0;
            a22[i][newsize-1] = 0;
            b22[i][newsize-1] = 0;
            a21[i][newsize-1] = 0;
            b21[i][newsize-1] = 0;
        }
    } 

    // build m1 through m7
    int temp1[newsize][newsize], temp2[newsize][newsize], m1[newsize][newsize],
        m2[newsize][newsize], m3[newsize][newsize], m4[newsize][newsize],
        m5[newsize][newsize], m6[newsize][newsize], m7[newsize][newsize];
    
    mat_add(newsize, a11, a22, temp1);
    mat_add(newsize, b11, b22, temp2);
    strassen(newsize, temp1, temp2, m1);

    mat_add(newsize, a21, a22, temp1);
    strassen(newsize, temp1, b11, m2);
    
    mat_sub(newsize, b12, b22, temp1);
    strassen(newsize, a11, temp1, m3);

    mat_sub(newsize, b21, b11, temp1);
    strassen(newsize, a22, temp1, m4);

    mat_add(newsize, a11, a12, temp1);
    strassen(newsize, temp1, b22, m5);

    mat_sub(newsize, a21, a11, temp1);
    mat_add(newsize, b11, b12, temp2);
    strassen(newsize, temp1, temp2, m6);

    mat_sub(newsize, a12, a22, temp1);
    mat_add(newsize, b21, b22, temp2);
    strassen(newsize, temp1, temp2, m7);
    
    // create c set --> be clever and reuse the set of matrices from splitting a
    mat_sub(newsize, m4, m5, temp1);
    mat_add(newsize, m1, m7, temp2);
    mat_add(newsize, temp1, temp2, a11);
    
    mat_add(newsize, m3, m5, a12);

    mat_add(newsize, m2, m4, a21);

    mat_sub(newsize, m1, m2, temp1);
    mat_add(newsize, m3, m6, temp2);
    mat_add(newsize, temp1, temp2, a22);
    
    // merge back together
    for (int i = 0; i < newsize; i++)
        for (int j = 0; j < newsize; j++)
            C[i][j] = a11[i][j];

    for (int i = 0; i < newsize; i++)
        for (int j = newsize; j < n; j++)
            C[i][j] = a21[i][j-newsize];

    for (int i = newsize; i < n; i++)
        for (int j = 0; j < newsize; j++)
            C[i][j] = a12[i-newsize][j];
        
    for (int i = newsize; i < n; i++)
        for (int j = newsize; j < n; j++)
            C[i][j] = a22[i-newsize][j-newsize];
}

/* imports from file

INPUT: 	A - n x n matrix to store data
		B - n x n matrix to store data
		n - dimention of A and B
		infile - file address

OUTPUT:	nothing, but changes A and B by reference

*/
void import(int n, int A[n][n], int B[n][n], char* infile){
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
void print_mat(int n, int A[n][n]){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			printf("%i\t", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

