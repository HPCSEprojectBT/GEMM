#ifndef _MATRIX_SETUP_
#define _MATRIX_SETUP_

void scatter_matrix(int rank, int m, int n_loc, float** A_glob,  float** A_loc, MPI_Comm & Comm_Cart, MPI_Status & status)
{
		//distribute global matrices over the ranks -------------------------
	
	MPI_Request* reqs =new MPI_Request [m*m];
	MPI_Status* send_status = new MPI_Status[m*m];
		if (rank ==0) {
				float** A_temp;
				A_temp = alloc_2d_init(n_loc,n_loc);
				float* sendptr, *recvptr;
				sendptr = &(A_temp[0][0]);
				recvptr = &(A_loc[0][0]);
				for (int i=0; i<m; ++i){
					for (int j=0; j<m; ++j) {
						int recv_coords[2]={i,j};
						int recv_cart_rank;
						MPI_Cart_rank(Comm_Cart, &recv_coords[0], &recv_cart_rank);
						int ii, jj; //starting block edge
						ii=i*n_loc;
						jj=j*n_loc;
						
						for(unsigned il=0; il<n_loc; il++){
							for(unsigned jl=0; jl<n_loc;jl++){
								A_temp[il][jl] = A_glob[il+ii][jl+jj];
							}
						}
						//A_temp = A_glob.block(ii,jj,n_loc,n_loc);
						
						//cout << "A_temp reads: \n " << A_temp << "\n sneds to " << recv_cart_rank << endl;
						// MPI_Send(&A_temp.data()[0],1,cont_type,recv_cart_rank,77,Comm_Cart);				
						
						MPI_Isend(sendptr,	n_loc*n_loc, 	MPI_FLOAT,	recv_cart_rank,	77,	Comm_Cart, &reqs[recv_cart_rank]);
					//	MPI_Waitall(i*m+j, reqs, send_status); 
					}
				}
				//MPI_Recv(&A_loc.data()[0],1,cont_type,0,77,Comm_Cart,&status);	
				MPI_Irecv(recvptr, 	n_loc*n_loc, 	MPI_FLOAT,	0,	77,	Comm_Cart, &reqs[0]);
		}
		else {
				//MPI_Recv(&A_loc.data()[0],1,cont_type,0,77,Comm_Cart,&status);	
				float* recvptr;
				recvptr = &(A_loc[0][0]);
				MPI_Irecv(recvptr, 	n_loc*n_loc, 	MPI_FLOAT,	0,	77,	Comm_Cart, &reqs[rank]);
		}		
//	MPI_Waitall(m*m,&reqs,&send_status);
	MPI_Barrier(Comm_Cart);
//_END_ matrix distibution-------------------------------------------	
}

void gather_matrix(int rank, int m, int n_loc, float** A_glob,  float** A_loc, MPI_Comm & Comm_Cart, MPI_Status & status)
{
	MPI_Request reqs[4];// =new MPI_Request [m*m];
	MPI_Status send_status[4];// = new MPI_Status[m*m];
	 //gather local matrizes ------------------------------
	float* sendptr;
	sendptr = &(A_loc[0][0]);
	if (rank ==0) {
		MPI_Isend(sendptr,	n_loc*n_loc, 	MPI_FLOAT,	0,	77,	Comm_Cart, &reqs[0]);
		float** A_temp;
		A_temp = alloc_2d_init(n_loc,n_loc);
		float *recvptr;
		recvptr = &(A_temp[0][0]);
		for (int i=0; i<m; ++i){
			for (int j=0; j<m; ++j) {
				int send_coords[2]={i,j};
				int send_cart_rank;
				MPI_Cart_rank(Comm_Cart, &send_coords[0], &send_cart_rank);
				
				int ii, jj; //starting block edge
				ii=i*n_loc;
				jj=j*n_loc;
				MPI_Irecv(recvptr, 	n_loc*n_loc, 	MPI_FLOAT,	send_cart_rank,	77,	Comm_Cart, &reqs[send_cart_rank]);

				for(unsigned il=0; il<n_loc; il++){
					for(unsigned jl=0; jl<n_loc;jl++){
						A_glob[il+ii][jl+jj] = A_temp[il][jl];
					}
				}		
			}
		}
	}
	else {
		MPI_Isend(sendptr,	n_loc*n_loc, 	MPI_FLOAT,	0,	77,	Comm_Cart, &reqs[rank]);
	}
	// _END_ gather ---------------------------------------
	MPI_Waitall(4,reqs,send_status);
	MPI_Barrier(Comm_Cart);

}





void initial_send(MPI_Comm &Comm_Cart,int rank, float **A_tmp, float **A,
					 float **B_tmp,float **B, MPI_Status &status, int size, int n){
	int mycoords[2] ={0,0};
	MPI_Cart_coords(Comm_Cart,rank,2,mycoords);

	int a_left_displ, a_right_displ, b_top_displ, b_bot_displ;

	a_left_displ=a_right_displ=b_top_displ=b_bot_displ=rank;

	// Shifts the initial value of A(i,j) by i steps to the left (in j direction)
	MPI_Cart_shift(Comm_Cart, 0, mycoords[1], &b_top_displ, &b_bot_displ);
	MPI_Cart_shift(Comm_Cart, 1, mycoords[0], &a_left_displ, &a_right_displ);


	float *sendptrA, *recvptrA,*sendptrB, *recvptrB;
	sendptrA = &(A[0][0]);
	recvptrA = &(A_tmp[0][0]);

	sendptrB = &(B[0][0]);
	recvptrB = &(B_tmp[0][0]);


	// Sends initial values of A to the left
	MPI_Sendrecv(sendptrA,n*n, MPI_FLOAT, a_left_displ,  lr_tag,
				 recvptrA,n*n, MPI_FLOAT, a_right_displ, lr_tag,
					Comm_Cart, &status);

	// Sends initial values of B to the top
	MPI_Sendrecv(sendptrB,n*n, MPI_FLOAT, b_top_displ, bt_tag,
				 recvptrB,n*n, MPI_FLOAT, b_bot_displ, bt_tag,
					Comm_Cart, &status);

}
#endif
