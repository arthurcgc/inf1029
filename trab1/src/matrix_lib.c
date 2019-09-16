#include "matrix_lib.h"

int scalar_matrix_mult(float scalar_value, Matrix *m)
{
	long unsigned int i;
	long unsigned int h;
	long unsigned int w;

	h = m->height;
	w = m->width;

	if (m == NULL || m->height != m->width || m->height % 8 != 0 || m->width == 0)
		return 0;

	__m256 vec_scalar = _mm256_set1_ps(scalar_value);

	float *nxt_rows = m->rows;
	for (i = 0; i < h * w; i += 8, nxt_rows += 8)
	{
		__m256 vec_rows = _mm256_load_ps(nxt_rows);
		__m256 vec_result = _mm256_mul_ps(vec_scalar, vec_rows);
		_mm256_store_ps(nxt_rows, vec_result);
	}

	return 1;
}

int matrix_matrix_mult(Matrix *mA, Matrix *mB, Matrix *mC)
{
	unsigned long int i, j, k;

	if (mA == NULL || mB == NULL || mC == NULL)
		return 0;

	if (mA->height * mA->width != mB->width * mB->height || mA->height*mA->width == 0)
	{
		printf("Column x Row mismatch\n");
		return 0;
	}

	float *nxt_rowA = mA->rows;
	float *nxt_rowB = mB->rows;
	float *nxt_rowC = mC->rows;

	__m256 vec_c = _mm256_setzero_ps();
	for (i = 0; i < mA->width * mA->height; i++)
	{
		if (i % mA->width == 0)
			nxt_rowB = mB->rows;

		__m256 vec_aij = _mm256_set1_ps(nxt_rowA[i]);
		nxt_rowC = mC->rows + mB->width * (i / mA->width);

		for (j = 0; j < mB->width; j += 8, nxt_rowB += 8, nxt_rowC += 8)
		{
			__m256 vec_b = _mm256_load_ps(nxt_rowB);
			__m256 vec_c = _mm256_load_ps(nxt_rowC);
			__m256 result = _mm256_fmadd_ps(vec_aij, vec_b, vec_c);

			_mm256_store_ps(nxt_rowC, result);
		}
	}

	return 1;
}