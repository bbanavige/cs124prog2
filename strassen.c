/*

Ben Banavige and Jack Deschler

CS124 Coding Assignment 2

Usage: ./strassen 0 dimension inputfile

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, char* argv[]){
	if (argc != 4){
		printf("Usage: ./strassen 0 dimension inputfile");
		return -1;
	}

	dim = stoi(argv[2]);
	inputfile = argv[3];

	int** A = malloc(n * sizeof(int*));
	int** B = malloc(n * sizeof(int*));

	for (int i = 0; i < n; i++){
		A[i] = malloc(n * sizeof(int));
		B[i] = malloc(n * sizeof(int));
	}

	

}