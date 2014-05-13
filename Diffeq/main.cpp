#include <iostream>
#include <mpi.h>
#include "3dgrid.h"

using namespace std;

int main(int argc, char **argv)
{
	double N = 100;
	int dimensions = 3;
	int *periodic = new int[dimensions];
	for(unsigned i=0;i<dimensions;++i){
		periodic[i]=1;
	}
	int reorder = 1;

	MPI_Init(&argc, &argv);

	int size;
	int rank;
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	int dims[3] = {0,0,0};


	MPI_Comm cartesian;
	MPI_Dims_create(size,3,dims);

	if(rank == 0){
		cout << dims[0] << "\t " << dims[1] << "\t" << dims[2] << endl;
	}
	MPI_Cart_create(MPI_COMM_WORLD, 3, dims, periodic, reorder, &cartesian);

	int left, right, top, bot, front, back;
	MPI_Cart_shift(cart_comm, 0, 1, &left, &right);
	MPI_Cart_shift(cart_comm, 1, 1, &bottom, &top);
	MPI_Cart_shift(cart_comm, 2, 1, &front, &back);


	cout << "rank " << rank << " has neighbours: " << left << "\t" << right << endl;

	grid3d<int> mygrid(4);

	for(unsigned i=1;i<3;i++){
		for(unsigned j=1;j<3;j++){
			for(unsigned z=1;z<3;z++){
				grid(i,j,z)=rank;
			}
		}
	}

	


	MPI_Finalize();
	
	return 0;
}