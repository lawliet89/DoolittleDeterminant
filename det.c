#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIMENSION 3     // Dimension for the matrix to be defined

float determinant(float *matrix, int dimension);
float getAt(float *m, int i, int j, int dimension);
void putAt(float *m, int i, int j, int dimension, float value);

int main(int argc, char ** argv){
    float matrix[DIMENSION][DIMENSION] = {
        {25, 5, 1},
        {64, 8, 1},
        {144, 12, 1}};
    float det;
    det = determinant( (float *) matrix, DIMENSION);
    
    printf("%f \n", det);   // answer should be -84
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