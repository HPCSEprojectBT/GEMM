#include <iostream>
#include <mpi.h>
#include "3dhpcmatrix.hpp"

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
	int tag = 777;
	

/*************** Testing block environment **************************************
*	MPI_Comm blocks;															*
*	int rdims[3] = {MPI_Sendrecv(&send,1,MPI_INT,left,tag
				 &rr,1,MPI_INT,right,tag,
				 MPI_COMM_WORLD, &status);
	MPI_Sendrecv(&send,1,MPI_INT,left,tag
				 &rr,1,MPI_INT,right,tag,
				 MPI_COMM_WORLD, &status);
	0,0,1};														*	
*																				*
*	MPI_Cart_sub(cartesian,rdims,&blocks);										*	
*																				*				
*	int newrank;																*		
*	MPI_Comm_rank(blocks,&newrank);												*
*	cout << "my old rank was " << rank << ", and now i'm " << newrank << endl;	*
********************************************************************************/							




	matrix<int> mygrid(4,4,4);

	for(unsigned i=0;i<4;i++){
		for(unsigned j=0;j<4;j++){
			for(unsigned z=0;z<4;z++){
				mygrid(i,j,z)=rank;
			}
		}
	}

	vector<int> sendvals(64);
	vector<int> recvals(164);
	for(unsigned i=0; i < 64; i++){
		sendvals[i] = i + rank*64;
		recvals[i] = 0;
	}

	



	MPI_Datatype MYTYPE;
	MPI_Type_vector(16,1,mygrid.stride_yz(),MPI_INT,&MYTYPE);
	MPI_Type_commit(&MYTYPE);

	if(rank==0){
		MPI_Sendrecv(&sendvals.front(),1,MYTYPE,1,tag,&recvals.at(7),1,MYTYPE,1,tag, MPI_COMM_WORLD, &status);
	}
	else if(rank==1){
		MPI_Sendrecv(&sendvals.front(),1,MYTYPE,0,tag,&recvals.at(7),1,MYTYPE,0,tag, MPI_COMM_WORLD, &status);	
	}


	if(rank==0){
		cout << "i am rank " << rank << " and my array is :" << endl;
		for(unsigned i=0;i<64;i++){
			cout << recvals[i] << "\t";
		}
	}
	cout << endl;


	MPI_Finalize();


	
	return 0;
}