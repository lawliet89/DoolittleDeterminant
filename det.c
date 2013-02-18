#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DIMENSION 20     // Dimension for the matrix to be defined

float determinant(float *matrix, int dimension);
float getAt(float *m, int i, int j, int dimension);
void putAt(float *m, int i, int j, int dimension, float value);
void randomMatrix(float *matrix, int dimension);

int main(int argc, char ** argv){
    float matrix[DIMENSION][DIMENSION];
    float det;
    
   // Generate random matrix
    randomMatrix((float *) matrix, DIMENSION);
    det = determinant( (float *) matrix, DIMENSION);
    
    printf("%f \n", det);   
    return 0;
}

float determinant(float *matrix, int dimension){
    int i, j, p;
    float a, result;
    float *m;

    // Let us copy the matrix first
    m = (float *) malloc( sizeof(float)*dimension*dimension );
    memcpy(m, matrix, sizeof(float)*dimension*dimension );

    // First step: perform LU Decomposition using Doolittle's Method
    // This algorithm will return, in the same matrix, a lower unit triangular matrix
    // (i.e. diagonals one)
    // and an upper trangular matrix
    // https://vismor.com/documents/network_analysis/matrix_algorithms/S4.SS2.php

    for (i = 0; i < dimension; i++){
        for (j = 0; j < i; j++){
            a = getAt(m, i, j, dimension);
            for (p = 0; p < j; p++){
                a -= getAt(m, i, p, dimension) * getAt(m, p, j, dimension);
            }
            putAt(m, i, j, dimension, a/getAt(m, j, j, dimension));
        }
        for (j = i; j < dimension; j++){
            a = getAt(m, i, j, dimension);
            for (p = 0; p < i; p++){
                a -= getAt(m, i, p, dimension) * getAt(m, p, j, dimension);
            }
            putAt(m, i, j, dimension, a);
        }
    }

    // Second step is to find the determinant.
    // Because the lower triangle is a unit triangular matrix
    // the determinant is simply a product of all the upper triangle diagonal
    // which in this case is exactly the diagonal of m
    result = 1;
    for (i = 0; i < dimension; i++)
        result *= getAt(m, i, i, dimension);

    free(m);

    return result;
}

// Based on i and j, and a float pointer, get the value at row i column j
float getAt(float *m, int i, int j, int dimension){
    return *(m + i*dimension + j);
}

// Based on i and j, and a float pointer, put the value at row i column j
void putAt(float *m, int i, int j, int dimension, float value){
    *(m + i*dimension + j) = value;
}

// Generate a n by n matrix consisting of numbers between -1 and 1.
// Outputs in a Matlab format, good for checking in Matlab
void randomMatrix(float *matrix, int dimension){
	int i, j;
	float no;
	srand(time(NULL));
	printf("[\n");
	for (i = 0; i < dimension; i++){
		for (j = 0; j < dimension; j++){
			no = ((float) (rand()%20))/10-1;
			*(matrix+i*dimension+j) = no;
			printf("%f ", no);
		}
		printf(";\n");
	}
	printf("\n]\n");
}
