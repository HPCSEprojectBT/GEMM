#ifndef _OUTP_
#define _OUTP_
void print_matrices(matrix<double> & m, int size, int rank)
{
	for( int i = 0; i < size; ++i ) {
		MPI_Barrier( MPI_COMM_WORLD );
		if ( i == rank ) {
			cout << "this is the matrix stored in rank " << rank << endl;
			cout << m;
		}
	}
}

void print_cartesian_dims(int * dims, int rank, int print_rank = 0)
{
	if(rank == print_rank){
		cout << dims[0] << "\t " << dims[1] << "\t" << dims[2] << endl;
	}
}

void print_neighbours(int rank, int left, int right, int top, int bottom, int front, int back)
{
	std::cout <<  "Rank " << rank  << " has neighbours " 
		<< left << ", " << right << ", "
		<< top << ", " << bottom << ", "
		<< front << ", " << back << std::endl;	
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




#endif
