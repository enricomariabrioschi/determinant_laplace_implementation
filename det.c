#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <time.h>

typedef struct{
	int n;
	double** M; 
} mat;

void printMat(mat A){
	int ii, jj;
	for(ii = 0; ii < A.n; ii++){
		for(jj = 0; jj < A.n; jj++){
			printf("%g\t", A.M[ii][jj]);
		}
		printf("\n");
	}
}

int PM(int a, int b){
	if((a + b) % 2 == 0){
		return 1;
	}else{
		return -1;
	}
}

double sumVect(double* v, int n){
	int ii;
	double X;
	X = 0;
	for(ii = 0; ii < n; ii++){
		X = X + v[ii];
	}
	return X;
}

mat removeAB(mat A, int a, int b){
	int ii, jj;
	mat B;
	B.n = A.n - 1;
	B.M = calloc(B.n, sizeof(double*));
	for(ii = 0; ii < B.n; ii++){
		B.M[ii] = calloc(B.n, sizeof(double));
	}
	for(ii = 0; ii < B.n; ii++){
		for(jj = 0; jj < B.n; jj++){
			B.M[ii][jj] = 0;
		}
	}
	for(ii = 0; ii < a; ii++){
		for(jj = 0; jj < b; jj++){
			B.M[ii][jj] = A.M[ii][jj];
		}
	}
	for(ii = 0; ii < a; ii++){
		for(jj = b + 1; jj < A.n; jj++){
			B.M[ii][jj - 1] = A.M[ii][jj];
		}
	}
	for(ii = a + 1; ii < A.n; ii++){
		for(jj = 0; jj < b; jj++){
			B.M[ii - 1][jj] = A.M[ii][jj];
		}
	}
	for(ii = a + 1; ii < A.n; ii++){
		for(jj = b + 1; jj < A.n; jj++){
			B.M[ii - 1][jj - 1] = A.M[ii][jj];
		}
	}
	return B;
}

int maxIndex(int* v, int n){
	int ii, X;
	X = 0;
	for(ii = 0; ii < n; ii++){
		if(v[ii] > v[X]){
			X = ii;
		}
	}
	return X;
}

int max(int* v, int n){
	int ii, X;
	X = v[0];
	for(ii = 0; ii < n; ii++){
		if(v[ii] > X){
			X = v[ii];
		}
	}
	return X;
}

int indexZeroRow(mat A){
	int ii, jj, X;
	int* v;
	v = calloc(A.n, sizeof(int));
	for(ii = 0; ii < A.n; ii++){
		X = 0;
		for(jj = 0; jj < A.n; jj++){
			if(A.M[ii][jj] == 0){
				X++;
			}
		}
		v[ii] = X;
	}
	return maxIndex(v, A.n);
}

int indexZeroColumn(mat A){
	int ii, jj, X;
	int* v;
	v = calloc(A.n, sizeof(int));
	for(jj = 0; jj < A.n; jj++){
		X = 0;
		for(ii = 0; ii < A.n; ii++){
			if(A.M[ii][jj] == 0){
				X++;
			}
		}
		v[jj] = X;
	}
	return maxIndex(v, A.n);
}

int rowOrColumn(mat A){
	int* v;
	int* w;
	int ii, jj, X, Y;
	v = calloc(A.n, sizeof(int));
	w = calloc(A.n, sizeof(int));
	for(ii = 0; ii < A.n; ii++){
		X = 0;
		for(jj = 0; jj < A.n; jj++){
			if(A.M[ii][jj] == 0){
				X++;
			}
		}
		v[ii] = X;
	}
	for(jj = 0; jj < A.n; jj++){
		Y = 0;
		for(ii = 0; ii < A.n; ii++){
			if(A.M[ii][jj] == 0){
				Y++;
			}
		}
		w[jj] = Y; 
	}
	if(max(v, A.n) > max(w, A.n)){
		return 1;
	}else{
		return 0;
	}
}

double det(mat A){
	int ii, X;
	double* v;
	if(A.n == 1){
		return A.M[0][0];
	}else{
		v = calloc(A.n, sizeof(double));
		if(rowOrColumn(A) == 1){
			X = indexZeroColumn(A);
			for(ii = 0; ii < A.n; ii++){
				if(A.M[ii][X] == 0){
					v[ii] = 0;
				}else{
					v[ii] = PM(ii + 1, X + 1) * A.M[ii][X] * det(removeAB(A, ii, X));
				}
			}
			return sumVect(v, A.n);
		}else{
			X = indexZeroRow(A);
			for(ii = 0; ii < A.n; ii++){
				if(A.M[X][ii] == 0){
					v[ii] = 0;
				}else{
					v[ii] = PM(X + 1, ii + 1) * A.M[X][ii] * det(removeAB(A, X, ii));
				}
			}
			return sumVect(v, A.n);
		}
	}
}

int main(void){
	srand(time(NULL));
	int ii, jj;
	mat A;
	printf("type integer\n");
	scanf("%d", &(A.n));
	A.M = calloc(A.n, sizeof(double*));
	for(ii = 0; ii < A.n; ii++){
		A.M[ii] = calloc(A.n, sizeof(double));
	}
	for(ii = 0; ii < A.n; ii++){
		for(jj = 0; jj < A.n; jj++){
			A.M[ii][jj] = rand() % 10;
		}
	}
	printf("matrix\n");
	printMat(A);
	printf("determinant:\t%g\n", det(A));
	/*free(&A);*/
	return 0;
}
