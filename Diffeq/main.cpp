#include <iostream>
#include <mpi.h>
#include "3dgrid.h"
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


	/********************** Testing neighbours **********************************************/
	int left, right, top, bot, front, back;														
	MPI_Cart_shift(cartesian, 0, 1, &left, &right);																			
	MPI_Cart_shift(cartesian, 1, 1, &bot, &top);											
	MPI_Cart_shift(cartesian, 2, 1, &front, &back);												
	//cout << "rank " << rank << " has neighbours: " << left << "\t" << right << endl;			
	int rl, rr, rt, rbo, rf, rba;																
	/*****************************************************************************************/
	int send = rank;
	int tag = 777;

	// Send to the left, recieve from the right
	MPI_Sendrecv(&send,1,MPI_INT,left,tag,
				 &rr,1,MPI_INT,right,tag,
				 MPI_COMM_WORLD, &status);
	// Sent to the right, recieve from the left
	MPI_Sendrecv(&send,1,MPI_INT,right,tag,
				 &rl,1,MPI_INT,left,tag,
				 MPI_COMM_WORLD, &status);
	// Send to the top, recieve from the bottom
	MPI_Sendrecv(&send,1,MPI_INT,top,tag,
				 &rbo,1,MPI_INT,bot,tag,
				 MPI_COMM_WORLD, &status);
	// Send to the bottom, recieve from the top
	MPI_Sendrecv(&send,1,MPI_INT,bot,tag,
				 &rt,1,MPI_INT,top,tag,
				 MPI_COMM_WORLD, &status);
	// Send to the front, recieve from the back
	MPI_Sendrecv(&send,1,MPI_INT,front,tag,
				 &rba,1,MPI_INT,back,tag,
				 MPI_COMM_WORLD, &status);
	// Send to the back, recieve from the front
	MPI_Sendrecv(&send,1,MPI_INT,back,tag,
				 &rf,1,MPI_INT,front,tag,
				 MPI_COMM_WORLD, &status);
	

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

	for(unsigned i=1;i<3;i++){
		for(unsigned j=1;j<3;j++){
			for(unsigned z=1;z<3;z++){
				mygrid(i,j,z)=rank;
			}
		}
	}

	unsigned i=0;
	unsigned j,z;
	for(j=1;j<3;j++){
		for(z=1;z<3;z++){
			mygrid(i,j,z)=rl;
		}
	}
	i=3;
	for(j=1;j<3;j++){
		for(z=1;z<3;z++){
			mygrid(i,j,z)=rr;
		}
	}
	j=0;
	for(i=1;i<3;i++){
		for(z=1;z<3;z++){
			mygrid(i,j,z)=rf;
		}
	}
	j=3;
	for(i=1;i<3;i++){
		for(z=1;z<3;z++){
			mygrid(i,j,z)=rba;
		}
	}
	z=0;
	for(i=1;i<3;i++){
		for(j=1;j<3;j++){
			mygrid(i,j,z)=rt;
		}
	}
	z=3;
	for(i=1;i<3;i++){
		for(j=1;j<3;j++){
			mygrid(i,j,z)=rbo;
		}
	}


	if(rank == 0){
		cout <<"i am rank " << rank << " , and my matrix is now: " << endl << mygrid << endl;
	}








	MPI_Finalize();
	
	return 0;
}