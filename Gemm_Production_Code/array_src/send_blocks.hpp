#ifndef SEND_BLOCKS
#define SEND_BLOCKS

void send_matrices_non_blocking(int * mycoords, float **A_tmp, float **A,
					 float **B_tmp,float **B, MPI_Comm & Comm_Cart
					 , int left, int right, int top, int bottom, int n_loc)
{

	MPI_Request reqs[4];
	MPI_Status send_status[4];

	float *sendptrA, *recvptrA,*sendptrB, *recvptrB;
	sendptrA = &(A[0][0]);
	recvptrA = &(A_tmp[0][0]);

	sendptrB = &(B[0][0]);
	recvptrB = &(B_tmp[0][0]);

	//send left and right	
	if (mycoords[0]%2==0){
		MPI_Isend(sendptrA,	n_loc*n_loc, 	MPI_FLOAT,	left,	lr_tag,	Comm_Cart, &reqs[0]);
		MPI_Irecv(recvptrA,	n_loc*n_loc, 	MPI_FLOAT,	right,	lr_tag,	Comm_Cart, &reqs[1]);	
	}
	else {	
		MPI_Irecv(recvptrA,	n_loc*n_loc, 	MPI_FLOAT,	right,	lr_tag,	Comm_Cart, &reqs[0]);	
		MPI_Isend(sendptrA,	n_loc*n_loc, 	MPI_FLOAT,	left,	lr_tag,	Comm_Cart, &reqs[1]);
	}
	//BT send/recv
	if (mycoords[1]%2==0){
		MPI_Isend(sendptrB,	n_loc*n_loc, 	MPI_FLOAT,	top,	bt_tag,	Comm_Cart, &reqs[2]);
		MPI_Irecv(recvptrB,	n_loc*n_loc, 	MPI_FLOAT,	bottom,	bt_tag,	Comm_Cart, &reqs[3]);	
	}
	else {	
		MPI_Irecv(recvptrB,	n_loc*n_loc, 	MPI_FLOAT,	bottom,	bt_tag,	Comm_Cart, &reqs[2]);	
		MPI_Isend(sendptrB,	n_loc*n_loc, 	MPI_FLOAT,	top,	bt_tag,	Comm_Cart, &reqs[3]);
	}

	MPI_Waitall(4,reqs,send_status);
}


void send_matrices_blocking(MPI_Status status, float **A_tmp, float **A,
					 float **B_tmp,float **B, MPI_Comm & Comm_Cart, int a_left_displ, int a_right_displ, int b_top_displ, int b_bot_displ, int n_loc)
{
	float *sendptrA, *recvptrA,*sendptrB, *recvptrB;
	sendptrA = &(A[0][0]);
	recvptrA = &(A_tmp[0][0]);

	sendptrB = &(B[0][0]);
	recvptrB = &(B_tmp[0][0]);

	// Sends initial values of A to the left
	MPI_Sendrecv(sendptrA, n_loc*n_loc, MPI_FLOAT, a_left_displ,  lr_tag,
				 recvptrA, n_loc*n_loc, MPI_FLOAT, a_right_displ, lr_tag,
					Comm_Cart, &status);

	// Sends initial values of B to the top
	MPI_Sendrecv(sendptrB,n_loc*n_loc, MPI_FLOAT, b_top_displ, bt_tag,
				 recvptrB,n_loc*n_loc, MPI_FLOAT, b_bot_displ, bt_tag,
					Comm_Cart, &status);
}

#endif //SEND_BLOCKS

