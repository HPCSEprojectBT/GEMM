#include <iostream>
#include <math.h>
#include <mpi.h>
#include <Eigen/Dense>
#include <vector>
#include <assert.h> 

//#define PRINT_DEBUG

using namespace std;
using Eigen::MatrixXd;

const int n = 6; //x and y Dimension of A,B and C
MPI_Datatype A_Block_Type, B_Block_Type, cont_type;
int lr_tag = 7;
int bt_tag = 77;


#include "../timer/timer.h"
#include "../eigen_src/output.hpp"
#include "../eigen_src/matrix_setup.hpp"
#include "../eigen_src/send_blocks.hpp"




int main (int argc, char** argv)
{

	MPI_Init(&argc, &argv);
	int size, rank, cart_rank, left, right, top, bottom;
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	double m = sqrt(size);
	//////////////////////////////added
	int number_of_steps = m;
	assert((n%(int)m)== 0) ;//n has to be a multiple of sqrt(n_procs)


	MatrixXd A_glob(n,n);
	MatrixXd B_glob(n,n);
	MatrixXd C_glob(n,n);
	////////////////////////////// Do div by m
	int n_loc = n/m;
	MatrixXd A_loc(n_loc,n_loc);
	MatrixXd B_loc(n_loc,n_loc);
	MatrixXd C_loc(n_loc,n_loc);
	MatrixXd A_loc_tmp(n_loc,n_loc);
	MatrixXd B_loc_tmp(n_loc,n_loc);
	MatrixXd C_step(n_loc,n_loc);

	MatrixXd C_correct(n,n);

	MPI_Type_contiguous(n_loc*n_loc,MPI_DOUBLE, &A_Block_Type); //prepare type for bottom/top sends
	MPI_Type_commit(&A_Block_Type);
	MPI_Type_contiguous(n_loc*n_loc,MPI_DOUBLE, &B_Block_Type); //prepare type for bottom/top sends
	MPI_Type_commit(&B_Block_Type);
	MPI_Type_contiguous(n_loc*n_loc,MPI_DOUBLE, & cont_type);
    MPI_Type_commit(&cont_type); 



	//create cartesian grid topology
	int dims[2] = {0,0};
	MPI_Dims_create(size,2,dims); //fills the dims array automatically
	MPI_Comm Comm_Cart;
	int periodic[2]={1,1};
	int reorder = 1;
	MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periodic, reorder, &Comm_Cart); //creates the communicator
	
	MPI_Comm_rank(Comm_Cart,&cart_rank); //cart_rank is the rank in the cartesian communicator
	int mycoords[2] ={0,0};
	MPI_Cart_coords(Comm_Cart,rank,2,mycoords);

	MPI_Cart_shift(Comm_Cart, 0, -1, &bottom, &top);
	MPI_Cart_shift(Comm_Cart, 1, 1, &left, &right);

	#ifdef PRINT_DEBUG
	print_neighbours(rank, left, right, top, bottom, size);
	//////////////7 added
	print_coordiantes(mycoords, rank, cart_rank, size);
	#endif

	//create initial global matrices
	double val = 1;
	for (int j=0; j<n ; ++j) {
	        for (int i=0; i<n; ++i) {
	                A_glob(i,j)=val;
	                B_glob(i,j)=100*val;
	                val++;
	        }
	} 

	if(rank == 0){

		C_correct = A_glob*B_glob;
	}

	scatter_matrix(rank,m,n_loc, A_glob, A_loc, Comm_Cart, status);
    if (rank == 0) cout <<"after scatter: \n\n";


    print_matrix_distribution(rank, size, A_loc, A_glob);


    scatter_matrix(rank,m,n_loc, B_glob, B_loc, Comm_Cart, status);
    if (rank == 0) cout <<"after scatter: \n\n";

    print_matrix_distribution(rank, size, B_loc, B_glob);

	// Initialisation of the matrix
	for(int i=0; i< n_loc ; i++)
		for(int j=0; j < n_loc; j++){
			C_step(i,j)=0;
			C_loc(i,j) =0;
		}


	// for(int i=0; i< n_loc ; i++)
	// 	for(int j=0; j < n_loc; j++){
	// 		B_loc(i,j) = rank;
	// 	}

	initial_send(Comm_Cart,rank,A_loc_tmp,A_loc,B_loc_tmp,B_loc,status, size);
	A_loc_tmp.swap(A_loc);
	B_loc_tmp.swap(B_loc);
	
#ifdef PRINT_DEBUG	
	print_abc(A_loc,B_loc, C_step, size, rank);
#endif

	// Doing the actual cannon's alogrithm
	for(int iterations=0; iterations < number_of_steps; ++iterations){
		print_stepcount(iterations, rank);
		C_step = A_loc*B_loc;
		C_loc = C_loc + C_step;
#ifdef PRINT_DEBUG
		print_abc(A_loc,B_loc, C_step, size, rank);
#endif		

		MPI_Barrier(MPI_COMM_WORLD);

		bool non_blocking =1;
		if(!non_blocking){
			send_ghostcells_blocking(status, A_loc, A_loc_tmp, B_loc, B_loc_tmp, Comm_Cart, left, right, top, bottom);
		}
		else{
			send_ghostcells_non_blocking(mycoords, A_loc, A_loc_tmp, B_loc, B_loc_tmp, Comm_Cart, left, right, top, bottom);
			if(rank == 0){
				cout << "system.out.println(fak this)" << endl;
			}
		}
	
		A_loc_tmp.swap(A_loc);
		B_loc_tmp.swap(B_loc);

	}



	gather_matrix(rank,m,n_loc, C_glob, C_loc, Comm_Cart, status);

	if(rank == 0){
		cout << "Correct c is:\n";
		cout << C_correct << endl;
	}
    if (rank == 0) cout <<"after gather: \n\n";
    print_matrix_distribution(rank, size, C_loc, C_glob);

	



	MPI_Finalize();
}
