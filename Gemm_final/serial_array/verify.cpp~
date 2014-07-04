#include <iostream>
#include <math.h>
#include <mpi.h>
#include <Eigen/Dense>
#include <vector>
#include <assert.h> 
#include <string>
#include <fstream>

//#define PRINT_DEBUG

using namespace std;

int n; //x and y Dimension of A,B and C
int lr_tag = 7;
int bt_tag = 77;
char timing_file[160];

float **alloc_2d_init(int rows, int cols) {
    float *data = (float *)malloc(rows*cols*sizeof(float));
    float **array= (float **)malloc(rows*sizeof(float*));
    for (int i=0; i<rows; i++)
        array[i] = &(data[cols*i]);

    return array;
}

#include "timer.h"
#include "output.hpp"
#include "matrix_setup.hpp"
#include "send_blocks.hpp"






int main (int argc, char** argv)
{


	MPI_Init(&argc, &argv);
	int size, rank, cart_rank, left, right, top, bottom;
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if(argc != 4){
		if(rank == 0){
			cout << "usage: mpirun -np <num nodes> " << argv[0] << " <size per dimension> <number of outputfile> <blocking(0) / non_blocking(1)>" << endl;
		}

		return 0;
	}

	n = atoi(argv[1]);
	sprintf(timing_file,"timing_%d.csv",atoi(argv[2]));
	bool non_blocking = atoi(argv[3]);



	double m = sqrt(size);
	int number_of_steps = m;
	assert((n%(int)m)== 0) ;//n has to be a multiple of sqrt(n_procs)

	int n_loc = n/m;

	float **A_loc;
	float **B_loc;
	float **C_loc;
	A_loc = alloc_2d_init(n_loc,n_loc);
	B_loc = alloc_2d_init(n_loc,n_loc);
	C_loc = alloc_2d_init(n_loc,n_loc);

	float **A_loc_tmp;
	float **B_loc_tmp;
	A_loc_tmp = alloc_2d_init(n_loc,n_loc);
	B_loc_tmp = alloc_2d_init(n_loc,n_loc);



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


	float **A_glob;
	A_glob = alloc_2d_init(n,n);
	float **B_glob;
	B_glob = alloc_2d_init(n,n);
	float **C_glob;
	C_glob = alloc_2d_init(n,n);
	float **C_correct;
	C_correct = alloc_2d_init(n,n);

	for (int j=0; j<n ; ++j) {
        for (int i=0; i<n; ++i) {
            A_glob[i][j]=1.47;
            B_glob[i][j]=1.74;
        }
	} 


	if(rank == 0){
		for(unsigned i=0;i<n;i++){
			for(unsigned j=0;j<n;j++){
				C_correct[i][j] = 0;
			}
		}
	}
	if(rank == 0){
		for(unsigned i=0;i<n;i++){
			for(unsigned j=0;j<n;j++){
				for(unsigned k=0;k<n;k++){
					C_correct[i][j] += A_glob[i][k] * B_glob[k][j];
				}
			}
		}
	}

	if(rank == 0){
		cout << endl;
		for(unsigned i=0; i<n; i++){
			for(unsigned j=0; j<n; j++){
				cout << A_glob[i][j] << "\t";
			}
			cout << endl;
		}
		cout << endl << endl;
	}	
	if(rank == 0){
		cout << endl;
		for(unsigned i=0; i<n; i++){
			for(unsigned j=0; j<n; j++){
				cout << C_correct[i][j] << "\t";
			}
			cout << endl;
		}
		cout << endl << endl;
	}
	// // Initialisation of the matrix
	// for(int i=0; i< n_loc ; i++)
	// 	for(int j=0; j < n_loc; j++){
	// 		A_loc[i][j]  =1.74;
	// 		B_loc[i][j]  =1.47;
	// 		C_step[i][j] =0;
	// 		C_loc[i][j]  =0;
	// 	}

	scatter_matrix(rank,m,n_loc, A_glob, A_loc, Comm_Cart, status);
	scatter_matrix(rank,m,n_loc, B_glob, B_loc, Comm_Cart, status);


	
	// Initialisation of the matrix
	for(int i=0; i< n_loc ; i++){
		for(int j=0; j < n_loc; j++){
			C_loc[i][j] =0;
		}
	}


	initial_send(Comm_Cart,rank,A_loc_tmp,A_loc,B_loc_tmp,B_loc,status, size,n_loc);
	swap(A_loc,A_loc_tmp);
	swap(B_loc,B_loc_tmp);
	
	//print_abc(A_loc,B_loc,C_step,size,rank, n_loc);
	// initial distirbution correct!
	




	// Doing the actual cannon's alogrithm
	for(int iterations=0; iterations < number_of_steps; ++iterations){
		// C_step = A_loc*B_loc;
		// C_loc = C_loc + C_step;

		for(unsigned i=0;i<n_loc;i++){
			for(unsigned j=0;j<n_loc;j++){
				for(unsigned k=0;k<n_loc;k++){
					C_loc[i][j] += A_loc[i][k] * B_loc[k][j];
				}
			}
		}


		MPI_Barrier(MPI_COMM_WORLD);



		//send_matrices_blocking(status, A_loc, A_loc_tmp, B_loc, B_loc_tmp, Comm_Cart, left, right, top, bottom, n_loc);
		
		if(!non_blocking){
			send_matrices_blocking(status,  A_loc_tmp, A_loc, B_loc_tmp,B_loc, Comm_Cart, left, right, top, bottom, n_loc);
		}
		else{
			send_matrices_non_blocking(mycoords,  A_loc_tmp, A_loc,B_loc_tmp,B_loc,  Comm_Cart, left, right, top, bottom, n_loc);
			if(rank == 0){
				cout << "system.out.println(fak this)" << endl;
			}
		}
		swap(A_loc,A_loc_tmp);
		swap(B_loc,B_loc_tmp);

	}



	gather_matrix(rank,m,n_loc, C_glob, C_loc, Comm_Cart, status);

	// if(rank == 0){
	// 	cout << "Correct c is:\n";
	// 	print_one_matrix(C_correct,n);
	// }
    if (rank == 0) cout <<"after gather: \n\n";
    print_matrix_distribution(rank, size, C_loc, C_glob, n_loc, n);
	print_coordiantes(mycoords, rank, rank, size);




	MPI_Finalize();
}
