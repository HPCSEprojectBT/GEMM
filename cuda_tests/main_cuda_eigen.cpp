#include <iostream>
#include <Eigen/Dense>
#include "gemm.h"

using namespace std;
using Eigen::MatrixXf;

int main (int argc, char** argv)
{
	int n = 10;
	double val = 1.;
	MatrixXf A(n,n);
	MatrixXf B(n,n);
	MatrixXf C(n,n);

	for (int i=0; i<n; ++i){
		for (int j=0; j<n; ++j){
			A(i,j)=val;
			B(i,j)=10*val++;
			C(i,j)=0;
		}
	}
	cout << "initial A,B,C:" << A << endl << B << endl << C << endl;

	float * a = &A.data()[0];
	float * b = &B.data()[0];
	float * c = &C.data()[0];

	cout <<"correct result for A*B=C is C=" << A*B << endl;

	MatMul(a,b,c,n);

	cout << "CUDA result for C= :" << C << endl;	
}
