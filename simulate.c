/*

70940507 and 30978137

CS124 Coding Assignment 2
Program for generating random input files

Usage: ./simulate flag dimension outfile

*/
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[]) {
	if (argc != 4) {
		printf("Usage: ./simulate dimension flag outfile\n");
		return -1;
	}

	int n = atoi(argv[1]);
    n = 2 * n * n;
	int flag = atoi(argv[2]);
    char* outfile = argv[3];

	srand(clock());

    FILE* out = fopen(outfile, "w");
    if (!out) {
        printf("Error opening file.\n");
        return -2;
    }

    if (flag == 1) {// just 0s and 1s
        for (int i = 0; i < n; i++) {
            int num = rand() % 2;
            fprintf(out, "%d\n", num);
        }
    }
    else if (flag == 2) { // 0, 1, 2
        for (int i = 0; i < n; i++) {
            int num = rand() % 3;
            fprintf(out, "%d\n", num);
        }
    }
    else if (flag == 3) { // 0, 1, -1
        for (int i = 0; i < n; i++) {
            int num = (rand() % 3) - 1;
            fprintf(out, "%d\n", num); 
        }
    }
    else {
        printf("Please enter valid flag (1,2,3).\n");
        return -3;
    }
}
