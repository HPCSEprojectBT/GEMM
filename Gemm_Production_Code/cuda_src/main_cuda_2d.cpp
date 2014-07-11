#include <iostream>
#include "gemm.h"

using namespace std;

float **alloc_2d_init(int rows, int cols) {
	float *data = (float *)malloc(rows*cols*sizeof(float));
	float **array= (float **)malloc(rows*sizeof(float*));
	for (int i=0; i<rows; i++)
		array[i] = &(data[cols*i]);

	return array;
}

int main (int argc, char** argv)
{
	int n = 10;
	double val = 1.;
	//MatrixXf A(n,n);
	//MatrixXf B(n,n);
	//MatrixXf C(n,n);

	float ** A, **C, **B, **C_correct;

	A= alloc_2d_init(n,n);
	C= alloc_2d_init(n,n);
	B= alloc_2d_init(n,n);
	C_correct = alloc_2d_init(n,n);

	for (int i=0; i<n; ++i){
		for (int j=0; j<n; ++j){
			A[i][j]=val;
			B[i][j]=10*val++;
			C[i][j]=0;
		}
	}

	for(unsigned i=0;i<n;i++){
		for(unsigned j=0;j<n;j++){
			C_correct[i][j] = 0;
		}
	}

	for(unsigned i=0;i<n;i++){
		for(unsigned j=0;j<n;j++){
			for(unsigned k=0;k<n;k++){
				C_correct[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	cout << endl;


	cout << endl;
	for(unsigned i=0; i<n; i++){
		for(unsigned j=0; j<n; j++){
			cout << C_correct[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl << endl;


	//cout << "initial A,B,C:" << A << endl << B << endl << C << endl;

	float * a = &A[0][0];
	float * b = &B[0][0];
	float * c = &C[0][0];

	//cout <<"correct result for A*B=C is C=" << C[7][7] << endl;

	MatMul(a,b,c,n);

	cout << "CUDA result for C= :"  << endl;	
	for(unsigned i=0; i<n; i++){
		for(unsigned j=0; j<n; j++){
			cout << C[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl << endl;
}
