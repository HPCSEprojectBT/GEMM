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
											
							if(recv_cart_rank !=0){	
								MPI_Send(&A_temp.data()[0],	1, 	cont_type,	recv_cart_rank,	77,	Comm_Cart);
							}
							else{
								A_loc = A_glob.block(ii,jj,n_loc,n_loc);
							}
						}
				}
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
						if (send_cart_rank!=0){
							MPI_Recv(&A_temp.data()[0],1,cont_type,send_cart_rank,77,Comm_Cart,&status);
							//cout << "here" << endl;
							A_glob.block(ii,jj,n_loc,n_loc)=A_temp;			}
						else{
							A_glob.block(ii,jj,n_loc,n_loc) = A_loc;
						}
					}
				}
		}
		else {
				MPI_Send(&A_loc.data()[0],1,cont_type,0,77,Comm_Cart);	
		}
		// _END_ gather ---------------------------------------

}


void initial_send(MPI_Comm &Comm_Cart,int rank, MatrixXd &A_tmp, MatrixXd &A,
					 MatrixXd &B_tmp, MatrixXd &B, MPI_Status &status, int size){
	int mycoords[2] ={0,0};
	MPI_Cart_coords(Comm_Cart,rank,2,mycoords);

	int a_left_displ, a_right_displ, b_top_displ, b_bot_displ;

	a_left_displ=a_right_displ=b_top_displ=b_bot_displ=rank;

	// Shifts the initial value of A(i,j) by i steps to the left (in j direction)
	MPI_Cart_shift(Comm_Cart, 0, mycoords[1], &b_top_displ, &b_bot_displ);
	MPI_Cart_shift(Comm_Cart, 1, mycoords[0], &a_left_displ, &a_right_displ);
#ifdef PRINT_DEBUG
	print_neighbours(rank, a_left_displ, a_right_displ, b_top_displ, b_bot_displ, size);
	//////////////7 added
	print_coordiantes(mycoords, rank, rank, size);
#endif


	// Sends initial values of A to the left
	MPI_Sendrecv(&A.data()[0],1, A_Block_Type,a_left_displ, lr_tag,
			&A_tmp.data()[0],1, A_Block_Type, a_right_displ, lr_tag,
			Comm_Cart, &status);

	// Sends initial values of B to the top
	MPI_Sendrecv(&B.data()[0],1, B_Block_Type,b_top_displ, bt_tag,
			&B_tmp.data()[0],1, B_Block_Type, b_bot_displ, bt_tag,
			Comm_Cart, &status);

}
#endif
