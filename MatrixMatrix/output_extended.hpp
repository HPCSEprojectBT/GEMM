#ifndef _OUTP_
#define _OUTP_


void print_cartesian_dims(int * dims, int rank, int print_rank = 0)
{
		if(rank == print_rank){
				cout << dims[0] << "\t " << dims[1] << endl;
		}
}

void print_neighbours(int rank, int left, int right, int top, int bottom)
{
		std::cout <<  "Rank " << rank  << " has neighbours " 
				<< left << ", " << right << ", "
				<< top << ", " << bottom
				<< std::endl;	
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

void gather_Matrix(vector<int> sizes_new, vector<int> local_sizes, int offset, MPI_Datatype A_Block_Type, MatrixXd A, int rank, int size, MPI_Comm Comm_Cart, string name){
		MatrixXd A_glob_temp (sizes_new[0+offset],sizes_new[1+offset] );
		MatrixXd A_glob (sizes_new[0+offset],sizes_new[1+offset] );
		MPI_Gather(&A.data()[0],1, A_Block_Type,&A_glob_temp.data()[0],1,A_Block_Type,0,MPI_COMM_WORLD); //gathers in A_glob_temp with column-row ordering

		MPI_Barrier(MPI_COMM_WORLD);

		/*
		if(rank == 0)
		{
				cout << "global matrix after gather: " << endl;
				cout << A_glob_temp << endl;
		}*/
		if (rank ==0){
				for (int p=0; p<size; ++p)
				{
						int coords[2]; //coords of process in cart grid
						int nm = local_sizes[0+offset]*local_sizes[1+offset]; //number of local matrix entrues
						MPI_Cart_coords(Comm_Cart, p, 2, coords); 
						MatrixXd local_block(local_sizes[0+offset],local_sizes[1+offset]);
						memcpy(&local_block.data()[0], &A_glob_temp.data()[p*nm],nm*sizeof(double));//converts column-row data to a small block matrix
						//cout << "local Block: " << endl;
						//cout << local_block << endl;
						if (offset == 0) {
						A_glob.block(coords[0]*local_sizes[0+offset],coords[1]*local_sizes[1+offset],local_sizes[0+offset],local_sizes[1+offset]) = local_block; // arranges small blocks to big matrix A_glob
						}
						else if (offset == 1) {
							//cout << "my coords are:" << endl;
							//cout << coords[0] << "\t" << coords[1] << endl;
							//cout << "ls 0+off " << local_sizes[0+offset] << endl;
							//cout << "ls 1+off " << local_sizes[1+offset] << endl;
							//cout << "coords " << coords[0] << "\t" << coords[1] << endl;
							A_glob.block(coords[1]*local_sizes[0+offset],coords[0]*local_sizes[1+offset],local_sizes[0+offset],local_sizes[1+offset]) = local_block; // arranges small blocks to big matrix A_glob
						}
						else cout << "unknown offset" << endl;
				}
				cout << "The global matrix " << name << " reads:" <<endl;
				cout << A_glob << endl;
				//cout << "dims of A_glob:" << sizes_new[0] << "\t" << sizes_new[1] << endl;	
		}
}





#endif
