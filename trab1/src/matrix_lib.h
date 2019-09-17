#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <immintrin.h>


typedef struct matrix{
	unsigned long int height; //num de linhas da matriz (32 bits)
	unsigned long int width; //num de colunas da matriz (32 bits)
	float *rows; //sequencia de linhas da matriz
} Matrix;

int scalar_matrix_mult(float scalar_value, Matrix *matrix);
int matrix_matrix_mult(Matrix *matrixA, Matrix *matrixB, Matrix *matrixC);
