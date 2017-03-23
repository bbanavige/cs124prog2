strassen: strassen.o 
	gcc -std=c99 -o strassen -O3 strassen.c
simulate: simulate.o
	gcc -std=c99 -o simulate -O3 simulate.c -lm
