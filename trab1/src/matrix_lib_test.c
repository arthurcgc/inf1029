#include "matrix_lib.h"

int main(int argc, char **argv){
	float scalar = atof(argv[1]);
	int count = 0;
	Matrix mA, mB;
	mA.height = atoi(argv[2]);
	mA.width = atoi(argv[3]);
	mB.height = atoi(argv[4]);
	mB.width =atoi(argv[5]);
	int mat_scalar, mat_mult;


	FILE *file1, *file2, *result1, *result2;
    file1 = fopen(argv[6],"rb");
	file2 = fopen(argv[7],"rb");
	result1 = fopen(argv[8],"wb");
	result2 = fopen(argv[9],"wb");

	if(file1 == NULL || file2 ==NULL)
	{
		printf("could not open one or more .dat files\n");
		return 0;
	}

	float *vA= (float*)aligned_alloc(32, (mA.height*mA.width) * sizeof(float));
	float aux;
	for(int i=0; i < mA.height * mA.width; i++)
	{
		fread((void*)(&aux), sizeof(aux), 1, file1);
		vA[count]=aux;
		count++;
	}
	mA.rows = vA;
	
	count=0;
	float* vB= (float*)aligned_alloc(32, (mB.height*mB.width) * sizeof(float));
	for(int i=0; i < mB.height * mB.width; i++)
	{
		fread((void*)(&aux), sizeof(aux), 1, file2);
		vB[count]=aux;
		count++;
	}
	mB.rows = vB;
	
	Matrix mC;
	mC.height = mA.height;
	mC.width = mA.width;

	float* vC= (float*)aligned_alloc(32, (mC.height*mC.width) * sizeof(float));
	
	for(int i=0 ; i < (mC.height*mC.width); i++)
		vC[i] = 0;
	
	mC.rows = vC;
	
	mat_scalar = scalar_matrix_mult(scalar, &mA);
	if(!mat_scalar)
	{
		printf("Error while multiplying by scalar\n");
		return 0;
	}

	for(int i=0 ; i < mA.height * mA.width ; i++)	
 		fwrite((void*)(&mA.rows[i]), sizeof(mA.rows[i]), 1, result1);
	
	mat_mult = matrix_matrix_mult(&mA, &mB, &mC);
	if(!mat_mult)
	{
		printf("Error while multiplying matrix A by matrix B");
		return 0;
	}

	for(int i=0; i<mC.height*mC.width; i++)
 		fwrite( (void*)( &mC.rows[i] ), sizeof( mC.rows[i] ), 1, result2 );
	
	free(vA);
	free(vB);
	free(vC);
	fclose(file1);
	fclose(file2);
	fclose(result1);
	fclose(result2);

	return 0;
}
