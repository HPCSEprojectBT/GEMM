#ifndef _MATRIX_SETUP_
#define _MATRIX_SETUP_

void scatter_matrix(int rank, int m, int n_loc, MatrixXd & A_glob, MatrixXd & A_loc, MPI_Comm & Comm_Cart, MPI_Status & status)
{
		//distribute global matrices over the ranks -------------------------
	
		if (rank ==0) {
				MatrixXd A_temp(n_loc,n_loc);
				for (int i=0; i<m; ++i){
						for (int j=0; j<m; ++j) {
								int recv_coords[2]={i,j};
								int recv_cart_rank;
								MPI_Cart_rank(Comm_Cart, &recv_coords[0], &recv_cart_rank);
								int ii, jj; //starting block edge
								ii=i*n_loc;
								jj=j*n_loc;
								A_temp = A_glob.block(ii,jj,n_loc,n_loc);
								//cout << "A_temp reads: \n " << A_temp << "\n sneds to " << recv_cart_rank << endl;
								MPI_Send(&A_temp.data()[0],1,cont_type,recv_cart_rank,77,Comm_Cart);				
						}
				}
				MPI_Recv(&A_loc.data()[0],1,cont_type,0,77,Comm_Cart,&status);	
		}
		else {
				MPI_Recv(&A_loc.data()[0],1,cont_type,0,77,Comm_Cart,&status);	
		}		
//_END_ matrix distibution-------------------------------------------	
}

void gather_matrix(int rank, int m, int n_loc, MatrixXd & A_glob, MatrixXd & A_loc, MPI_Comm & Comm_Cart, MPI_Status & status)
{
	 //gather local matrizes ------------------------------
		if (rank ==0) {
				MPI_Send(&A_loc.data()[0],1,cont_type,0,77,Comm_Cart);	
				MatrixXd A_temp(n_loc,n_loc);
				for (int i=0; i<m; ++i){
						for (int j=0; j<m; ++j) {
								int send_coords[2]={i,j};
								int send_cart_rank;
								MPI_Cart_rank(Comm_Cart, &send_coords[0], &send_cart_rank);
								
								int ii, jj; //starting block edge
								ii=i*n_loc;
								jj=j*n_loc;
								//A_temp = A_glob.block(ii,jj,n_loc,n_loc);
								//cout << "A_temp reads: \n " << A_temp << "\n sneds to " << recv_cart_rank << endl;
								MPI_Recv(&A_temp.data()[0],1,cont_type,send_cart_rank,77,Comm_Cart,&status);
								//cout << "here" << endl;
								A_glob.block(ii,jj,n_loc,n_loc)=A_temp;				
						}
				}
		}
		else {
				MPI_Send(&A_loc.data()[0],1,cont_type,0,77,Comm_Cart);	
		}
		// _END_ gather ---------------------------------------

}
#endif
