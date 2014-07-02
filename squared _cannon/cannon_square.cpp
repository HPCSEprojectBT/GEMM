#include <iostream>
#include <math.h>
#include <mpi.h>
#include <Eigen/Dense>
#include <vector>
#include <assert.h> 

#define PRINT_DEBUG

using namespace std;
using Eigen::MatrixXd;

#include "timer.h"
#include "output.hpp"

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
	print_neighbours(rank, left, right, top, bottom);
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

	//distribute global matrices over the ranks
	MPI_Datatype block_type, cont_type;
	MPI_Type_vector(n_loc,n_loc,n_loc*dims[0],MPI_DOUBLE, & block_type);
	MPI_Type_contiguous(n_loc*n_loc,MPI_DOUBLE, & cont_type);
	MPI_Datatype cont2_type;
	MPI_Type_contiguous(n_loc,MPI_DOUBLE, & cont2_type);
	

	MPI_Type_commit(&block_type);
	MPI_Type_commit(&cont_type);

	MPI_Scatter(&A_glob.block(0,0,2,2).data()[0],1,cont_type,&A_loc.data()[0],1,cont_type,0,Comm_Cart);
	for (int i=0; i<size; ++i) {
		MPI_Barrier(MPI_COMM_WORLD);
		if (rank==i) {
			if(rank ==0) cout <<"A_glob = " << endl << A_glob << endl;
			cout << "Rank " << rank << " stores A=" << endl;
			cout << A_loc << endl;
		}
	
	}

	


	MPI_Finalize();
}
