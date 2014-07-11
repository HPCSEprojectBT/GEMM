#ifndef SEND_BLOCKS
#define SEND_BLOCKS

void send_matrix_blocks(MPI_Status status, MatrixXf &A_loc, MatrixXf &A_loc_tmp, MatrixXf &B_loc, MatrixXf &B_loc_tmp, MPI_Comm & Comm_Cart, int left, int right, int top, int bottom)
{
	// Sends to the left, recieve from right
	MPI_Sendrecv(&A_loc.data()[0],1, Matrix_Block_Type,left, lr_tag,
		&A_loc_tmp.data()[0],1, Matrix_Block_Type, right, lr_tag,
		Comm_Cart, &status);

	// Sends to the top, recieve from bot
	MPI_Sendrecv(&B_loc.data()[0],1, Matrix_Block_Type,top, bt_tag,
		&B_loc_tmp.data()[0],1, Matrix_Block_Type, bottom, bt_tag,
		Comm_Cart, &status);
}
#endif //SEND_BLOCKS

