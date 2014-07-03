#include <iostream>
#include <math.h>
#include <mpi.h>
#include <Eigen/Dense>
#include <vector>
#include <assert.h> 

#define PRINT_DEBUG

using namespace std;
using Eigen::MatrixXd;
MPI_Datatype cont_type;

#include "timer.h"
#include "output.hpp"
#include "matrix_setup.hpp"

const int n = 6; //x and y Dimension of A,B and C



int main (int argc, char** argv)
{

		MPI_Init(&argc, &argv);
		int size, rank, cart_rank, left, right, top, bottom;
		MPI_Status status;
		MPI_Comm_size(MPI_COMM_WORLD,&size);
		MPI_Comm_rank(MPI_COMM_WORLD,&rank);
		double m = sqrt(size);
		assert((n%(int)m)== 0) ;//n has to be a multiple of sqrt(n_procs)

		MatrixXd A_glob(n,n);
		MatrixXd B_glob(n,n);
		MatrixXd C_glob(n,n);
		int n_loc = n/sqrt(size);
		MatrixXd A_loc(n_loc,n_loc);
		MatrixXd B_loc(n_loc,n_loc);
		MatrixXd C_loc(n_loc,n_loc);

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
		print_neighbours(rank, left, right, top, bottom,size);
		cout << "Global Rank " << rank <<" has cart rank " <<cart_rank << "and cartesian coordinates (" << mycoords[0] << "," << mycoords[1] <<")" << endl; 
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

		scatter_matrix(rank,m,n_loc, A_glob, A_loc, Comm_Cart, status);
		if (rank == 0) cout <<"after scatter: \n\n";


    	print_matrix_distribution(rank, size, A_loc, A_glob);
	
		//change local matrices
		A_loc=2*A_loc;

		gather_matrix(rank,m,n_loc, A_glob, A_loc, Comm_Cart, status);

		if (rank == 0) cout <<"after gather: \n\n";
		print_matrix_distribution(rank, size, A_loc, A_glob);
		

		MPI_Finalize();
}
