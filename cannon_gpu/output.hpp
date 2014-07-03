#ifndef _OUTP_
#define _OUTP_



void print_cartesian_dims(int * dims, int rank, int print_rank = 0)
{
	if(rank == print_rank){
		cout << dims[0] << "\t " << dims[1] << endl;
	}
}

void print_neighbours(int rank, int left, int right, int top, int bottom, int size)
{
	MPI_Barrier( MPI_COMM_WORLD);
	for(unsigned i=0; i< size; i++){
		if(i==rank){
		std::cout <<  "Rank " << rank  << " has neighbours (l,r,t,b) " 
			<< left << ", " << right << ", "
			<< top << ", " << bottom
			<< std::endl;	
		}
		MPI_Barrier( MPI_COMM_WORLD);
	}	
}

void print_center(int rank, int * center,int centerrank, int print_rank=0)
{
	if(rank==print_rank){
		cout << "the center rank is: " << centerrank << endl;
		cout << "cartesian coords of centerrank: " << center[0] << "\t" << center[1] << "\t" << center[2] << endl;
	}
}

void print_offsets(int rank,int size, double offsetx, double offsety, double offsetz)
{
	for(unsigned i=0; i< size; i++){
		if(i==rank){
			cout << "i am rank " << rank << endl;
			cout << "my local offsets are: " << offsetx << "\t" << offsety << "\t" << offsetz << endl;
		}
		MPI_Barrier( MPI_COMM_WORLD);
	}	
}


void print_stepcount(int iterations, int rank){
	MPI_Barrier( MPI_COMM_WORLD);
	if(rank==0){
		cout << "\n\n\n" << "Starting new step (" << iterations << ")" << endl << endl;
	}
	MPI_Barrier( MPI_COMM_WORLD);
}


void print_one_matrix(float** matrix, int matrix_size){
	cout << endl;
	for(unsigned i=0; i<matrix_size; i++){
		for(unsigned j=0; j<matrix_size; j++){
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl << endl;
}

void print_abc(float** A,float** B, float** C_step, int size, int rank, int n_loc){
	for(unsigned i=0; i< size; i++){
		MPI_Barrier( MPI_COMM_WORLD);
		if(i==rank){
			cout << "i am rank " << rank << endl;
			cout << "my A Matrix is: ";
			print_one_matrix(A,n_loc);
			cout << "my B Matrix is: ";
			print_one_matrix(B,n_loc);
			cout << "my C Matrix is: ";
			print_one_matrix(C_step,n_loc);
		}
		MPI_Barrier( MPI_COMM_WORLD);
	}
}

void print_sizes(vector<int> & sizes, vector<int> & sizes_new, vector<int> & local_sizes,int rank){
	MPI_Barrier( MPI_COMM_WORLD);
		if(rank == 0 ){
		cout << "global size is: " << sizes[0] << "x" << sizes[1] << "\t";
		cout << sizes[1] << "x" << sizes[2] << endl << endl;

		cout << "reshaped size is: " << sizes_new[0] << "x" << sizes_new[1] << "\t";
		cout << sizes_new[1]  << "x" << sizes_new[2] << endl << endl;

		cout << "local sizes are: "  <<  local_sizes[0]  << "x";
		cout << local_sizes[1]  << "\t" << local_sizes[1]  << "x" << local_sizes[2] << endl;
	}
	MPI_Barrier( MPI_COMM_WORLD);
}

void print_coordiantes(int * mycoords, int rank, int cart_rank, int size){
	for(unsigned i=0; i< size; i++){
		MPI_Barrier( MPI_COMM_WORLD);
		if(i==rank){
			cout << "Global Rank " << rank <<" has cart rank " <<cart_rank << "and cartesian coordinates (" << mycoords[0] << "," << mycoords[1] <<")" << endl; 
		}
		MPI_Barrier( MPI_COMM_WORLD);
	}
}



void print_matrix_distribution(int rank, int size, float**  A_loc, float**  A_glob, int n_loc, int n) {
    //print matrix destribution
    for (int i=0; i<size; ++i) {
        MPI_Barrier(MPI_COMM_WORLD);
        if (rank==i) {
            if(rank ==0){
	        	cout <<"A_glob = ";
	        	print_one_matrix(A_glob,n);
            }
            cout << "Rank " << rank << " stores A=";
            print_one_matrix(A_loc,n_loc);
        }
    }
} 





#endif
