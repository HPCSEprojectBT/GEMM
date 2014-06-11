#include <iostream>
#include <math.h>
#include <mpi.h>
#include <Eigen/Dense>

using namespace std;
using Eigen::MatrixXd;
using Eigen::Matrix;

#include "output.hpp"
#include <vector>

MPI_Datatype A_Block_Type, B_Block_Type;
int lr_tag = 7;
int bt_tag = 77;

int nsteps;

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

	sizes[0] = 5;
	sizes[1] = 3;
	sizes[2] = 1;

	int dims[2]={0,0};




	MPI_Comm Comm_Cart; //communicator with topology
	MPI_Dims_create(size,2,dims); //fills the dims array automatically

	if(rank == 0){
		cout << dims[0] << "\t " << dims[1] << endl;
	}

	int periodic[2]={1,1};
	int reorder = 1;

	MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periodic, reorder, &Comm_Cart); //creates the communicator
	int left, right, bottom, top, local_rank;
	MPI_Comm_rank(Comm_Cart,&local_rank); //new_rank is the rank in the cartesian communicator

	MPI_Cart_shift(Comm_Cart, 0, 1, &left, &right);
	MPI_Cart_shift(Comm_Cart, 1, 1, &bottom, &top);

	 print_neighbours(rank, left, right, top, bottom);

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


	if(rank == 0 ){
		cout << "global size is: " << sizes[0] << "x" << sizes[1] << "\t";
		cout << sizes[1] << "x" << sizes[2] << endl << endl;

		cout << "reshaped size is: " << sizes_new[0] << "x" << sizes_new[1] << "\t";
		cout << sizes_new[1]  << "x" << sizes_new[2] << endl << endl;

		cout << "local sizes are: "  <<  local_sizes[0]  << "x";
		cout << local_sizes[1]  << "\t" << local_sizes[1]  << "x" << local_sizes[2] << endl;
	}

	nsteps = dims[0];


	for(int i=0; i< local_sizes[0] ; i++)
		for(int j=0; j < local_sizes[1]; j++){
			A(i,j) = rank+1;
		}


	for(int i=0; i< local_sizes[1] ; i++)
		for(int j=0; j < local_sizes[2]; j++){
			B(i,j) = (rank+1)*100;
		}

	C= A*B;


	int mycoords[2] ={0,0};
	MPI_Cart_coords(Comm_Cart,rank,2,mycoords);

	for(int xcoord = 0; xcoord < dims[0]; xcoord++){
		for(int ycoord = 0; ycoord < dims[1]; ycoord++){
			MPI_Barrier(MPI_COMM_WORLD);
			// if(rank == 0)
			// 	cout << "tada" << endl;

			if(mycoords[0]==xcoord && mycoords[1]==ycoord){
				cout << "i am rank: " << rank << endl;
				cout << "my coords are: " << mycoords[0] << "\t" << mycoords[1] << endl;
				cout << C << endl << endl;
			}

			MPI_Barrier(MPI_COMM_WORLD);
		}
	}

	MPI_Finalize();
}
