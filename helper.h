/*

function definitions for header file

*/

#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// conventional matrix multiplication
void con(int** A, int** B, int n);

// import file
void import(int** A, int** B, int n, char* infile);

// simulate
void sim(int n, int type, char* outfile);

// print matrix A, which is n x n
void print_mat(int** A, int n);

#endif // HELPER_H