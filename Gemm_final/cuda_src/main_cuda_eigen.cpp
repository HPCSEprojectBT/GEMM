#include <iostream>
#include <mpi.h>
#include <Eigen/Dense>
#include "gemm.h"
#include <fstream>

using namespace std;
using Eigen::MatrixXf;

int main (int argc, char** argv)
{
		
	MPI_Init(&argc, &argv);
	int size, rank;
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	ofstream outfiles[size];
	
	int n = 17;
	double val = 1.;
	
	MatrixXf A(n,n);
	MatrixXf B(n,n);
	MatrixXf C(n,n);

	for (int i=0; i<n; ++i){
		for (int j=0; j<n; ++j){
			A(i,j)=1.;
			B(i,j)=rank;
			C(i,j)=0;
		}
	}
	
	for (int i =0; i<size; ++i){
		MPI_Barrier(MPI_COMM_WORLD);
		if(rank == i) {
			char filename[160];
			sprintf(filename, "output_thread_%u",i);
			outfiles[i].open(filename, ios::app);
			outfiles[i] << "initial A,B,C:" <<endl << A << endl << B << endl << C << endl;
		}
		MPI_Barrier(MPI_COMM_WORLD);
	}

	float * a = &A.data()[0];
	float * b = &B.data()[0];
	float * c = &C.data()[0];

	//cout <<"correct result for A*B=C is C=" << A*B << endl;
	for (int i=0; i<n; ++i){
		for (int j=0; j<n; ++j){
			//A(i,j)=1.;
			//B(i,j)=rank;
			C(i,j)=0;
		}
	}

	MatMul(a,b,c,n);
	MPI_Barrier(MPI_COMM_WORLD);
	for (int i =0; i<size; ++i){
		MPI_Barrier(MPI_COMM_WORLD);
		if(rank == i) {
			char filename[160];
			sprintf(filename, "output_thread_%u",i);
			//outfiles[i].open(filename, ios::app);
			outfiles[i] << "CUDA result for C after first mult= :" <<endl<< C << endl;
			//outfiles[i].close();	
		}
		MPI_Barrier(MPI_COMM_WORLD);
	}
	
	MatMul(a,b,c,n);
	MPI_Barrier(MPI_COMM_WORLD);
	for (int i =0; i<size; ++i){
		MPI_Barrier(MPI_COMM_WORLD);
		if(rank == i) {
			char filename[160];
			sprintf(filename, "output_thread_%u",i);
			//outfiles[i].open(filename, ios::app);
			outfiles[i] << "CUDA result for C after second mult= :" <<endl<< C << endl;
			//outfiles[i].close();	
		}
		MPI_Barrier(MPI_COMM_WORLD);
	}
}
