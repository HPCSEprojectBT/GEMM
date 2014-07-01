#include <iostream>
#include <math.h>
#include <mpi.h>
#include <Eigen/Dense>

using namespace std;
using Eigen::MatrixXd;
using Eigen::Matrix;

#include "output.hpp"
#include "timer.h"


MPI_Datatype A_Block_Type, B_Block_Type;
int lr_tag = 7;
int bt_tag = 77;

int nsteps;


#define PRINT_DEBUG




void initial_send(MPI_Comm &Comm_Cart,int rank, MatrixXd &A_tmp, MatrixXd &A,
					 MatrixXd &B_tmp, MatrixXd &B, MPI_Status &status){
	int mycoords[2] ={0,0};
	MPI_Cart_coords(Comm_Cart,rank,2,mycoords);

	int left_displ, right_displ, top_displ, bot_disp;

	left_displ=right_displ=top_displ=bot_disp=rank;

	// Shifts the initial value of A(i,j) by i steps to the left (in j direction)
	MPI_Cart_shift(Comm_Cart, 0, mycoords[1], &left_displ, &right_displ);
	MPI_Cart_shift(Comm_Cart, 1, mycoords[0], &top_displ, &bot_disp);

	// Sends initial values of A to the left
	MPI_Sendrecv(&A.data()[0],1, A_Block_Type,left_displ, lr_tag,
			&A_tmp.data()[0],1, A_Block_Type, right_displ, lr_tag,
			Comm_Cart, &status);

	// Sends initial values of B to the top
	MPI_Sendrecv(&B.data()[0],1, B_Block_Type,top_displ, bt_tag,
			&B_tmp.data()[0],1, B_Block_Type, bot_disp, bt_tag,
			Comm_Cart, &status);

}

int main (int argc, char** argv)
{

	//MPI Init and CartComm creationy
	MPI_Init(&argc, &argv);
	int size;
	int rank;
	MPI_Status status;
	MPI_Request reqs[12];
	MPI_Status send_status[12];
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	// First Matix size N x M, 2nd Matrix size M x N2
	// sizes[0] = N, sizes[1] = M, sizes[2] = N2
	vector<double> sizes (3,0);
	vector<double> sizes_new (3,0);
	vector<int> local_sizes (3,0);
	// Delete if we get marix or get info from argv
	sizes[0] = 4;
	sizes[1] = 2;
	sizes[2] = 3;




	int dims[2]={0,0};

	Timer T;

	T.tic();



	MPI_Comm Comm_Cart; //communicator with topology
	MPI_Dims_create(size,2,dims); //fills the dims array automatically

#ifdef PRINT_DEBUG
	print_cartesian_dims(dims,rank);
#endif

	int periodic[2]={1,1};
	int reorder = 1;

	MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periodic, reorder, &Comm_Cart); //creates the communicator
	int left, right, bottom, top, local_rank;
	MPI_Comm_rank(Comm_Cart,&local_rank); //new_rank is the rank in the cartesian communicator

	MPI_Cart_shift(Comm_Cart, 0, 1, &left, &right);
	MPI_Cart_shift(Comm_Cart, 1, -1, &bottom, &top);

#ifdef PRINT_DEBUG
	print_neighbours(rank, left, right, top, bottom);
#endif

	// Find Size of the marix, if it cannot be distributed equally, we add 0 rows / cols
	for(int i=0; i<2; i++){
		local_sizes[i] = ceil( double (sizes[i]) / dims[i] );
		sizes_new[i] = local_sizes[i] * dims[i];
	}
	local_sizes[2] = ceil ( double (sizes[2]) / dims[0]);

	sizes_new[2] = local_sizes[2] * dims[0];


	MatrixXd A (local_sizes[0], local_sizes[1] );
	MatrixXd A_tmp (local_sizes[0], local_sizes[1] );
	MatrixXd B (local_sizes[1], local_sizes[2] );
	MatrixXd B_tmp (local_sizes[1], local_sizes[2] );
	MatrixXd C (local_sizes[0], local_sizes[2] );
	MatrixXd C_step(local_sizes[0], local_sizes[2] );

#ifdef PRINT_DEBUG
	print_sizes(sizes, sizes_new,local_sizes,rank);
#endif

	nsteps = dims[1];




	// Initialisation of the matrix
	for(int i=0; i< local_sizes[0] ; i++)
		for(int j=0; j < local_sizes[1]; j++){
			A(i,j) = rank;
		}


	for(int i=0; i< local_sizes[1] ; i++)
		for(int j=0; j < local_sizes[2]; j++){
			B(i,j) = rank;
		}


	int mycoords[2] ={0,0};
	MPI_Cart_coords(Comm_Cart,rank,2,mycoords);



	// Perparing Types to send the matrices around
	int nm = local_sizes[0]*local_sizes[1];
	int mn2 = local_sizes[1]*local_sizes[2];
	MPI_Type_contiguous(nm,MPI_DOUBLE, &A_Block_Type); //prepare type for bottom/top sends
	MPI_Type_commit(&A_Block_Type);
	MPI_Type_contiguous(mn2,MPI_DOUBLE, &B_Block_Type); //prepare type for bottom/top sends
	MPI_Type_commit(&B_Block_Type);


	initial_send(Comm_Cart,rank,A_tmp,A,B_tmp,B,status);
	A_tmp.swap(A);
	B_tmp.swap(B);
	



	// Doing the actual cannon's alogrithm
	for(int iterations=0; iterations < nsteps; ++iterations){
		stepcount(iterations, rank);
		C_step = A*B;
		C = C + C_step;
#ifdef PRINT_DEBUG
		print_abc(A,B, C_step, size, rank);
#endif		

		MPI_Barrier(MPI_COMM_WORLD);

		// Sends to the left, recieve from right
		MPI_Sendrecv(&A.data()[0],1, A_Block_Type,left, lr_tag,
			&A_tmp.data()[0],1, A_Block_Type, right, lr_tag,
			Comm_Cart, &status);

		// Sends to the top, recieve from bot
		MPI_Sendrecv(&B.data()[0],1, B_Block_Type,top, bt_tag,
			&B_tmp.data()[0],1, B_Block_Type, bottom, bt_tag,
			Comm_Cart, &status);
	
		A_tmp.swap(A);
		B_tmp.swap(B);

	}




	print_solution(sizes_new, local_sizes, C_Block_Type, C, rank, size,Comm_Cart);


	MPI_Finalize();
}
