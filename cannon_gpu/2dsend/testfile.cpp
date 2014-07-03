#include <iostream>
#include <math.h>
#include <stdlib.h> 
#include <mpi.h>

using namespace std;

// #define N 10

int **alloc_2d_init(int rows, int cols) {
    int *data = (int *)malloc(rows*cols*sizeof(int));
    int **array= (int **)malloc(rows*sizeof(int*));
    for (int i=0; i<rows; i++)
        array[i] = &(data[cols*i]);

    return array;
}



int main(int argc, char *argv[])
{

	MPI_Init(&argc, &argv);
	int size, rank, cart_rank, left, right, top, bottom;
	MPI_Status status;
	int tagA = 7;
	int tagB = 77;
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);


	int N = 5;

	int **A;
	A = alloc_2d_init(N,N);
	int **B;
	B = alloc_2d_init(N,N);


	if(rank == 0){
		for(unsigned i=0;i<N;i++){
			for(unsigned j=0;j<N;j++){
				A[i][j] = 7;
			}
		}
	}
	else{
		for(unsigned i=0;i<N;i++){
			for(unsigned j=0;j<N;j++){
				B[i][j] = 77;
			}
		}		
	}

	int *sendptr, *recvptr;
	int neigh = MPI_PROC_NULL;

	if (rank == 0) {
		sendptr = &(A[0][0]);
		recvptr = &(B[0][0]);
		neigh = 1;
	}
	else {
		sendptr = &(B[0][0]);
		recvptr = &(A[0][0]);
		neigh = 0;
	}


	MPI_Sendrecv(sendptr, N*N, MPI_INT, neigh, tagA, recvptr, N*N, MPI_INT, neigh, tagA, MPI_COMM_WORLD, &status);

	// if (rank == 0) {
	// 	MPI_Send(&(A[0][0]), N*N, MPI_INT, 1, tagA, MPI_COMM_WORLD);
	// 	MPI_Recv(&(B[0][0]), N*N, MPI_INT, 1, tagB, MPI_COMM_WORLD, &status);
	// }
	// else if (rank == 1) {
	// 	MPI_Recv(&(A[0][0]), N*N, MPI_INT, 0, tagA, MPI_COMM_WORLD, &status);
	// 	MPI_Send(&(B[0][0]), N*N, MPI_INT, 0, tagB, MPI_COMM_WORLD);
	// }

	if(rank == 1){
		cout << "i am rank 1 and i recieved the a matrix" << endl;
		for(unsigned i=0;i<N;i++){
			for(unsigned j=0;j<N;j++){
				cout << A[i][j] << "\t";
			}
			cout << endl;
		}
		cout << endl;
	}
	MPI_Barrier(MPI_COMM_WORLD);
	if(rank == 0){
		cout << "i am rank 0 and i recieved the b matrix " << endl;
		for(unsigned i=0;i<N;i++){
			for(unsigned j=0;j<N;j++){
				cout << B[i][j] << "\t";
			}
			cout << endl;
		}
		cout << endl;
	}
	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Finalize();
}