#include "matrix_lib.h"
#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>



void printMatrix(Matrix *m){
    int len = m->height*m->width;

    for (int i = 0; i < len; i++)
    {
        printf("rows[%d] = %.2f ",i, m->rows[i]);
        if(i%8 == 0){
            printf("\n");
        }
    }
    
}

Matrix *initMatrix(unsigned long int height, unsigned long width, float init_value){
    Matrix *res = (Matrix*)malloc(sizeof(Matrix));
    int N = height*width;
    res->rows = (float*)aligned_alloc(32, N);
    res->height = height; res->width = width;

    __m256 mask_row = _mm256_set1_ps(init_value);
    float *buffer = res->rows;

    int i;
    for (i = 0; i < N/8; i++, buffer+= 8)
    {
        _mm256_store_ps(buffer, mask_row);
    }

    return res;

}

void print_mat(Matrix *m){
    int len = m->height * m->width;

    for(int i = 0; i < len; i++)
    {
        printf("row[%d]: %.2f ", i, m->rows[i]);
        if(i % 8 == 0)
            printf("\n");
    }
}

int main(){

    Matrix *test = initMatrix(8, 8, 5.0f);
    print_mat(test);
    return 0;

}