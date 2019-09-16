#include "matrix_lib.h"

int main(int argc, char **argv){
	float scalar = atof(argv[1]);
	int count;
	Matrix matA, matB;
	matA.height = atoi(argv[2]);
	matA.width = atoi(argv[3]);
	matB.height = atoi(argv[4]);
	matB.width =atoi(argv[5]);
	int mat_scalar, mat_mult;


	FILE *file1, *file2, *result1, *result2;
    file1 = fopen(argv[6],"rb");
	file2 = fopen(argv[7],"rb");
	result1 = fopen(argv[8],"wb");
	result2 = fopen(argv[9],"wb");

	if(file1 == NULL || file2 ==NULL)
	{
		fprintf(stdout, ".dat failed to open.  exiting...\n");
		exit(1);
	}

	count=0;
	
	float* vetA= (float*)aligned_alloc(32, (matA.height*matA.width) * sizeof(float));
	float vetA_aux;

	for(int i=0; i<matA.height*matA.width; i++){
		fread((void*)(&vetA_aux), sizeof(vetA_aux), 1, file1);
		vetA[count]=vetA_aux;
		count++;
	}
	matA.rows = vetA;
	
	count=0;
	float* vetB= (float*)aligned_alloc(32, (matB.height*matB.width) * sizeof(float));
	float vetB_aux;
	
	for(int i=0; i<matB.height*matB.width; i++){
		fread((void*)(&vetB_aux), sizeof(vetB_aux), 1, file2);
		vetB[count]=vetB_aux;
		count++;
	}
	matB.rows = vetB;
	
	Matrix matC;
	matC.height = matA.height;
	matC.width = matB.width;

	float* vetC= (float*)aligned_alloc(32, (matC.height*matC.width) * sizeof(float));
	
	for(int i=0; i< (matC.height*matC.width); i++){
		vetC[i] = 0;
	}
	matC.rows = vetC;
	
	mat_scalar = scalar_matrix_mult(scalar, &matA);
	if(!mat_scalar)
		printf("Error while multiplying by scalar\n");

	for(int i=0; i<matA.height*matA.width; i++){	
 		fwrite((void*)(&matA.rows[i]), sizeof(matA.rows[i]), 1, result1);
	}
	
	mat_mult = matrix_matrix_mult(&matA, &matB, &matC);
	if(!mat_mult)
		printf("Error while multiplying matrix A by matrix B");


	for(int i=0; i<matC.height*matC.width; i++){	
 		fwrite((void*)(&matC.rows[i]), sizeof(matC.rows[i]), 1, result2);
	}
	free(vetA);
	free(vetB);
	free(vetC);
	fclose(file1);
	fclose(file2);
	fclose(result1);
	fclose(result2);

	return 0;
}
