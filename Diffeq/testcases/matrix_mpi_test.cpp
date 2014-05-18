#include <iostream>
#include <mpi.h>
#include "3dhpcmatrix.hpp"

using namespace std;

void print_matrices(matrix<int> & m, int size, int rank)
{
	for( int i = 0; i < size; ++i ) {
		MPI_Barrier( MPI_COMM_WORLD );
		if ( i == rank ) {
			cout << "this is the matrix stored in rank " << rank << endl;
			cout << m;
		}
	}
}

int main (int argc, char **argv)
{
	int world_dim=3;
	int dims[3]={0,0,0};

	MPI_Init(&argc, &argv);
	int size;
	int rank;
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	MPI_Comm Comm_Cart; //communicator with topology
	MPI_Dims_create(size,world_dim,dims); //fills the dims array automatically

	int *periodic = new int[world_dim];
	for(unsigned i=0;i<world_dim;++i) periodic[i]=1;
	int reorder = 1;

	MPI_Cart_create(MPI_COMM_WORLD, world_dim, dims, periodic, reorder, &Comm_Cart); //creates the communicator
	int left, right, bottom, top, front, back, newrank; 
	MPI_Comm_rank(Comm_Cart,&newrank); //new_rank is the rank in the cartesian communicator

	MPI_Cart_shift(Comm_Cart, 0, 1, &left, &right);
	MPI_Cart_shift(Comm_Cart, 2, 1, &bottom, &top);
	MPI_Cart_shift(Comm_Cart, 1, 1, &front, &back);

	//uncomment for testing neighbor distribution
	std::cout <<  "Rank " << rank << " has new rank " << newrank << " and neighbors " 
		<< left << ", " << right << ", "
		<< top << ", " << bottom << ", "
		<< front << ", " << back << std::endl;



	int local_dim = 3;
	matrix<int> localMatrix(local_dim,local_dim,local_dim);
	//matrix<int> recv(local_dim,local_dim,local_dim);
	int val = 0;
	for (int k=0; k<local_dim; ++k) {
		for (int j=0; j<local_dim; ++j) {
			for (int i=0; i<local_dim; ++i) {
				localMatrix(i,j,k) = newrank*100+val;
				val++;
			}
		}
	}

	if (rank==0) cout << "Initial Matrices :" << endl;
	print_matrices(localMatrix, size, rank);

	MPI_Barrier( MPI_COMM_WORLD );

	//send left and right
	int lr_tag = 12;
	int rl_tag = 21;
	MPI_Datatype LR_TYPE;

	//LR send/recv
	MPI_Type_vector(localMatrix.num_yz(),localMatrix.blocklength_yz(),localMatrix.stride_yz(), MPI_INT, &LR_TYPE); //prepare type for left/right sends
	MPI_Type_commit(&LR_TYPE);

	// Send to the left, recieve from the right
	MPI_Sendrecv(&localMatrix.data_[1],1,LR_TYPE,left,lr_tag,
			&localMatrix.data_[localMatrix.num_x()-1],1,LR_TYPE,right,lr_tag,
			Comm_Cart, &status);

	// Send to the right, recieve from the left
	MPI_Sendrecv(&localMatrix.data_[localMatrix.num_x()-2],1,LR_TYPE,right,rl_tag,
			&localMatrix.data_[0],1,LR_TYPE,left,rl_tag,
			Comm_Cart, &status);


	//BT send/recv
	int bt_tag = 12;
	int tb_tag = 21;
	MPI_Datatype BT_TYPE;

	MPI_Type_contiguous(localMatrix.num_xy(),MPI_INT, &BT_TYPE); //prepare type for bottom/top sends
	MPI_Type_commit(&BT_TYPE);

	// Send to top, recieve from bottom
	MPI_Sendrecv(&localMatrix.data_[localMatrix.num_xy()],1,BT_TYPE,top,bt_tag,
			&localMatrix.data_[localMatrix.num_xy()*(localMatrix.num_z()-1)],1,BT_TYPE,bottom,bt_tag,
			Comm_Cart, &status);

	// Send to bottom, recieve from top
	MPI_Sendrecv(&localMatrix.data_[localMatrix.num_xy()*(localMatrix.num_z()-2)],1,BT_TYPE,bottom,tb_tag,
			&localMatrix.data_[0],1,BT_TYPE,top,tb_tag,
			Comm_Cart, &status);



	for( int i = 0; i < size; ++i ) {
		MPI_Barrier( MPI_COMM_WORLD );
		if ( i == rank ) {
			cout << "BT send: this is the matrix stored in rank " << rank << endl;
			cout << localMatrix;
		}
	}


	//FB send/recv
	int fb_tag = 12;
	int bf_tag = 21;
	MPI_Datatype FB_TYPE;

	MPI_Type_vector(localMatrix.num_z(),localMatrix.blocklength_xz(),localMatrix.stride_xz(), MPI_INT, &FB_TYPE); //prepare type for front/back sends

	MPI_Type_commit(&FB_TYPE);

	// Send to front, recieve from back

	MPI_Sendrecv(&localMatrix.data_[localMatrix.num_x()],1,FB_TYPE,front,fb_tag,
			&localMatrix.data_[localMatrix.num_xy()-localMatrix.num_x()],1,FB_TYPE,back,fb_tag,
			Comm_Cart, &status);

	// Send to back, recieve from front

	MPI_Sendrecv(&localMatrix.data_[localMatrix.num_xy()-2*localMatrix.num_x()],1,FB_TYPE,back,fb_tag,
			&localMatrix.data_[0],1,FB_TYPE,front,fb_tag,
			Comm_Cart, &status);

	if(rank==0) cout << "Final matrices after send/recieve in all 3 dimensions" << endl;
	print_matrices(localMatrix, size, rank);


	MPI_Finalize();

}
