#ifndef SEND_BLOCKS
#define SEND_BLOCKS

void send_ghostcells_non_blocking(int * mycoords, MatrixXd &A_loc, MatrixXd &A_loc_tmp, MatrixXd &B_loc, MatrixXd &B_loc_tmp, MPI_Comm & Comm_Cart, int left, int right, int top, int bottom)
{

	MPI_Request reqs[4];
	MPI_Status send_status[4];
	//send left and right	
	if (mycoords[0]%2==0){
		MPI_Isend(&A_loc.data()[0]   ,1  ,A_Block_Type   ,left   ,lr_tag,Comm_Cart, &reqs[0]);
		MPI_Irecv(&A_loc_tmp.data()[0],1 ,A_Block_Type   ,right  ,lr_tag,Comm_Cart, &reqs[1]);	
	}
	else {		
		MPI_Irecv(&A_loc_tmp.data()[0],1 ,A_Block_Type   ,right  ,lr_tag,Comm_Cart, &reqs[0]);
		MPI_Isend(&A_loc.data()[0]   ,1  ,A_Block_Type   ,left   ,lr_tag,Comm_Cart, &reqs[1]);
	}
	//BT send/recv
	if (mycoords[1]%2==0){
		MPI_Isend(&B_loc.data()[0]   ,1  ,B_Block_Type   ,top     ,bt_tag,Comm_Cart, &reqs[2]);
		MPI_Irecv(&B_loc_tmp.data()[0],1 ,B_Block_Type   ,bottom  ,bt_tag,Comm_Cart, &reqs[3]);	
	}
	else {		
		MPI_Irecv(&B_loc_tmp.data()[0],1 ,B_Block_Type   ,bottom  ,bt_tag,Comm_Cart, &reqs[2]);
		MPI_Isend(&B_loc.data()[0]   ,1  ,B_Block_Type   ,top     ,bt_tag,Comm_Cart, &reqs[3]);
	}

	MPI_Waitall(4,reqs,send_status);
}


void send_ghostcells_blocking(MPI_Status status, MatrixXd &A_loc, MatrixXd &A_loc_tmp, MatrixXd &B_loc, MatrixXd &B_loc_tmp, MPI_Comm & Comm_Cart, int left, int right, int top, int bottom)
{
	// Sends to the left, recieve from right
	MPI_Sendrecv(&A_loc.data()[0],1, A_Block_Type,left, lr_tag,
		&A_loc_tmp.data()[0],1, A_Block_Type, right, lr_tag,
		Comm_Cart, &status);

	// Sends to the top, recieve from bot
	MPI_Sendrecv(&B_loc.data()[0],1, B_Block_Type,top, bt_tag,
		&B_loc_tmp.data()[0],1, B_Block_Type, bottom, bt_tag,
		Comm_Cart, &status);
}

#endif //SEND_BLOCKS