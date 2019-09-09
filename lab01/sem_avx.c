#include <stdlib.h>
#include <stdio.h>

float *sub_arr(int n, float *va, float *vb){
	float *res = (float*)malloc(sizeof(float)*n);
	for(int i = 0; i < n; i++){
		res[i] = va[i] - vb[i];
	}
	return res;
}

float *create_odds(int n){
	float *res = (float*)malloc(sizeof(float)*n);
	res[0] = 1;
	for(int i = 1; i < n; i++)
	{
		res[i] = res[i-1] + 2;
	}
	return res;
}

float *create_evens(int n){
	float *res = (float*)malloc(sizeof(float)*n);
	res[0] = 0;
	for(int i = 1; i < n; i++)
	{
		res[i] = res[i-1] + 2;
	}
	return res;
}

int get_n(){
	int n;
	printf("Array size: ");
	scanf("%d", &n);
	return n;	
}

void print_arr(int n, float *v){
	for(int i = 0; i < n; i++){
		printf("%.2f", v[i])
	}
	printf("\n");
}

int main(){
	int n = get_n();
	float *vO = 

}

