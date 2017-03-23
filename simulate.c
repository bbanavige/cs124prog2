/*

Ben Banavige and Jack Deschler

CS124 Coding Assignment 2

Usage: ./simulate dimension outfile

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "helper.c"

int main(int argc, char* argv[]){
	if (argc != 3){
		printf("Usage: ./simulate dimension outfile");
		return -1;
	}

	int n = atoi(argv[1]);
	char* outfile = argv[2];

	srand(clock());
	sim(n, 0, outfile);

}