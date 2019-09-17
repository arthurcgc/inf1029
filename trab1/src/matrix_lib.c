#include "matrix_lib.h"

int scalar_matrix_mult(float scalar_value, Matrix *matrix){
	unsigned long int i;
	unsigned long int h;
	unsigned long int w;

	h = matrix->height;
	w = matrix->width;

	if(matrix == NULL || (h*w) % 8 != 0 || h == 0) 
		return 0;

  	__m256 vec_scalar = _mm256_set1_ps(scalar_value); 
 	
 	float *buffer = matrix->rows;
 	
 	for(i=0; i<h*w; i+=8, buffer+=8){
 		__m256 vec_rows = _mm256_load_ps(buffer);	
 		__m256 vec_result = _mm256_mul_ps(vec_scalar, vec_rows);
 		_mm256_store_ps(buffer, vec_result);
	}	

	return 1;
}

int matrix_matrix_mult(Matrix *mA, Matrix *mB, Matrix *mC){	
	unsigned long int i,j,k;	

	if(mA == NULL || mB == NULL|| mC == NULL) return 0;


	if(mA->height*mA->width != mB->width*mB->height){
		printf("Wrong row x column distribuition");
		return 0;
	}
		
	float *bufferA = mA->rows;
	float *bufferB = mB->rows;
	float *bufferC = mC->rows;
	
	__m256 vec_c = _mm256_setzero_ps();
	for(i=0; i<mA->width*mA->height; i++){
		if(i%mA->width == 0)
			bufferB = mB->rows;

		__m256 vec_aij = _mm256_set1_ps(bufferA[i]);
		bufferC = mC->rows + mB->width * (i/mA->width);

		for(j=0; j<mB->width; j+=8, bufferB+=8,bufferC+=8){
			__m256 vec_b = _mm256_load_ps(bufferB);
			__m256 vec_c = _mm256_load_ps(bufferC);
			__m256 result = _mm256_fmadd_ps(vec_aij,vec_b,vec_c);
			_mm256_store_ps(bufferC, result);
		}
	}

	return 1;
}