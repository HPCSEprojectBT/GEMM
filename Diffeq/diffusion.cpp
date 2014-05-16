#include <iostream>
#include <mpi.h>
#include "3dhpcmatrix.hpp"
#include "vtk_writer.hpp"
#include <math.h>

using namespace std;

const int t_max = 100000;
double dt = 0.00001;

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

int main (int argc, char **argv)
{
	//-------------driver params----------------------------
	int world_dim=3;
	int dims[3]={0,0,0};
	int N = 5; //target global number of DOFS in each direction
	int N_new; //global number of DOFS in each direction after rounding 
	double L = 1.; //edgelength of simulated cube
	vector<double> dx(3,0); //discrete spacing in each direction
	vector<double> n(3,0); //local number of DOFS in x,y,z direction
	int local_dofs; //number of local dofs per matrix
	double init_heat = 77777777;
	int print = 1000;
	//--------------------------------------------------------

	//MPI Init and CartComm creationy
	MPI_Init(&argc, &argv);
	int size;
	int rank;
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	MPI_Comm Comm_Cart; //communicator with topology
	MPI_Dims_create(size,world_dim,dims); //fills the dims array automatically
	if(rank == 0){
		cout << dims[0] << "\t " << dims[1] << "\t" << dims[2] << endl;
	}

	int *periodic = new int[world_dim];
	for(unsigned i=0;i<world_dim;++i) periodic[i]=1;
	int reorder = 1;

	MPI_Cart_create(MPI_COMM_WORLD, world_dim, dims, periodic, reorder, &Comm_Cart); //creates the communicator
	int left, right, bottom, top, front, back, newrank; 
	MPI_Comm_rank(Comm_Cart,&newrank); //new_rank is the rank in the cartesian communicator

	MPI_Cart_shift(Comm_Cart, 0, 1, &left, &right);
	MPI_Cart_shift(Comm_Cart, 2, 1, &bottom, &top);
	MPI_Cart_shift(Comm_Cart, 1, 1, &front, &back);

	//uncomment for testing neighbor distribution
	std::cout <<  "Rank " << rank << " has new rank " << newrank << " and neighbors " 
		<< left << ", " << right << ", "
		<< top << ", " << bottom << ", "
		<< front << ", " << back << std::endl;

	//compute (local) sizes and offsets:
	for (int i=0; i<world_dim; ++i){ //compute local matrix setting
		n[i]=ceil(double(N)/dims[i]);
		dx[i]=L/(n[i]*dims[i]);
	}
	N_new = n[0]*n[1]*n[2]*size; //round up N

	matrix<double> u(n[0]+2,n[1]+2,n[2]+2); //local matrix including ghost plains
	matrix<double> u_old(n[0]+2,n[1]+2,n[2]+2);//local matrix including ghost plains


	// find the rank closest to the middle

	int center[3] = {0,0,0};
	center[0] = round(double(dims[0])/2.0)-1;
	center[1] = round(double(dims[1])/2.0)-1;
	center[2] = round(double(dims[2])/2.0)-1;
	int centerrank;
	MPI_Cart_rank(Comm_Cart,center,&centerrank);
	if(rank==0){
		cout << "the center rank is: " << centerrank << endl;
		cout << "center: " << center[0] << "\t" << center[1] << "\t" << center[2] << endl;
	}

	//generate initial local matrizes without ghost cells
	for (int k=1; k<=n[2]; ++k) {
		for (int j=1; j<=n[1]; ++j) {
			for (int i=1; i<=n[0]; ++i) {
				if (rank == centerrank) u(i,j,k) = init_heat; //inital heat field
				else u(i,j,k) = 0;
			}
		}
	}

	//print initial matrix settup
	if (rank==0) cout << "Initial Matrices :" << endl;
	print_matrices(u, size, rank);

	MPI_Barrier( MPI_COMM_WORLD );
	if(rank==0) cout << "local Matrix creation done" << endl;

	//MPI TYPES AND STUFF--------------------------
	//send left and right
	int lr_tag = 12;
	int rl_tag = 21;
	int bt_tag = 13;
	int tb_tag = 31;
	int fb_tag = 14;
	int bf_tag = 41;
	
	MPI_Datatype LR_TYPE;
	MPI_Datatype BT_TYPE;
	MPI_Datatype FB_TYPE;

	MPI_Type_vector(u.num_yz(),u.blocklength_yz(),u.stride_yz(), MPI_DOUBLE, &LR_TYPE); //prepare type for left/right sends
	MPI_Type_commit(&LR_TYPE);
	MPI_Type_contiguous(u.num_xy(),MPI_DOUBLE, &BT_TYPE); //prepare type for bottom/top sends
	MPI_Type_commit(&BT_TYPE);
	MPI_Type_vector(u.num_z(),u.blocklength_xz(),u.stride_xz(), MPI_DOUBLE, &FB_TYPE); //prepare type for front/back sends
	MPI_Type_commit(&FB_TYPE);
	//----------------------------------------------

	// initial ghost cell distribution ----------------------------------------
	//---------------------------------------------------------------------------------------------------
	
	//LR send/recv
	// Send to the left, recieve from the right
	MPI_Sendrecv(&u.data_[1],1,LR_TYPE,left,lr_tag,
			&u.data_[u.num_x()-1],1,LR_TYPE,right,lr_tag,
			Comm_Cart, &status);

	// Send to the right, recieve from the left
	MPI_Sendrecv(&u.data_[u.num_x()-2],1,LR_TYPE,right,rl_tag,
			&u.data_[0],1,LR_TYPE,left,rl_tag,
			Comm_Cart, &status);


	//BT send/recv

	// Send to top, recieve from bottom
	MPI_Sendrecv(&u.data_[u.num_xy()],1,BT_TYPE,top,bt_tag,
			&u.data_[u.num_xy()*(u.num_z()-1)],1,BT_TYPE,bottom,bt_tag,
			Comm_Cart, &status);

	// Send to bottom, recieve from top
	MPI_Sendrecv(&u.data_[u.num_xy()*(u.num_z()-2)],1,BT_TYPE,bottom,tb_tag,
			&u.data_[0],1,BT_TYPE,top,tb_tag,
			Comm_Cart, &status);

	//FB send/recv
	
	// Send to front, recieve from back

	MPI_Sendrecv(&u.data_[u.num_x()],1,FB_TYPE,front,fb_tag,
			&u.data_[u.num_xy()-u.num_x()],1,FB_TYPE,back,fb_tag,
			Comm_Cart, &status);

	// Send to back, recieve from front

	MPI_Sendrecv(&u.data_[u.num_xy()-2*u.num_x()],1,FB_TYPE,back,fb_tag,
			&u.data_[0],1,FB_TYPE,front,fb_tag,
			Comm_Cart, &status);

	u_old = u;

	if (rank==0) cout << "Initial Matrices after ghost cell shifting :" << endl;
	print_matrices(u, size, rank);
	//print_matrices(u_old, size, rank);



	//---------------------------------------------END OF SENDING AND RECIEVING---------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------------------------------

	//compute global index vectors
	//local vectors per local matrix
	local_dofs = n[0]*n[1]*n[2];
	vector<double> ldxvals(local_dofs);
	vector<double> ldyvals(local_dofs);
	vector<double> ldzvals(local_dofs);
	vector<double> lfvals(local_dofs);

	//get coordinates of the process in cartesian grid
	int mycoords[3] ={0,0,0};
	MPI_Cart_coords(Comm_Cart,rank,3,mycoords);

	//compute the offsets of the local coordinates w.r.t. global coords
	double offsetx, offsety, offsetz;
	offsetx = mycoords[0]*(n[0])*dx[0];
	offsety = mycoords[1]*(n[1])*dx[1];
	offsetz = mycoords[2]*(n[2])*dx[2];

	//compute global x,y,z values for each process
	int cnt=0;
	for(double i=1; i<=(n[0]); i++){
		for(double j=1;j<=(n[1]); j++){
			for(double k=1; k<=(n[2]); k++){
				ldxvals[cnt] = offsetx+(i-1)*dx[0];
				ldyvals[cnt] = offsety+(j-1)*dx[1];
				ldzvals[cnt] = offsetz+(k-1)*dx[2];
				cnt++;
			}
		}
	}


	//------------------------START TIMESTEPPING -----------------------------------------------
	//------------------------------------------------------------------------------------------

	int print_counter = 0;
	vector<double> dxvals(N_new);
	vector<double> dyvals(N_new);
	vector<double> dzvals(N_new);
	vector<double> fvals(N_new);


	for (int t=0; t<t_max; ++t){

		if(t<10 || t%print==0){

			//compute global heat values for output
			//local vectors per local matrix

			//compute global heat vals for each process
			int cnt=0;
			for(double i=1; i<=(n[0]); i++){
				for(double j=1;j<=(n[1]); j++){
					for(double k=1; k<=(n[2]); k++){
						lfvals[cnt] = u(i,j,k);
						//cout << lfvals[cnt] << endl;
						cnt++;
					}
				}
			}

			MPI_Barrier( MPI_COMM_WORLD );
			//Gather all the local data into global data for printing the solution
			if(rank==0) cout << "start gathering at timestep :" << t << endl;


			MPI_Gather(&ldxvals[0],ldxvals.size(), MPI_DOUBLE, &dxvals[0], ldxvals.size(), MPI_DOUBLE, 0, MPI_COMM_WORLD);
			MPI_Gather(&ldyvals[0],ldyvals.size(), MPI_DOUBLE, &dyvals[0], ldyvals.size(), MPI_DOUBLE, 0, MPI_COMM_WORLD);
			MPI_Gather(&ldzvals[0],ldzvals.size(), MPI_DOUBLE, &dzvals[0], ldzvals.size(), MPI_DOUBLE, 0, MPI_COMM_WORLD);
			MPI_Gather(&lfvals[0],lfvals.size(), MPI_DOUBLE, &fvals[0], lfvals.size(), MPI_DOUBLE, 0, MPI_COMM_WORLD);

			MPI_Barrier( MPI_COMM_WORLD );
			//Gather all the local data into global data for printing the solution
			if(rank==0) cout << "finished gathering at timestep :" << t << endl;


			if (rank ==0) write_3d(dxvals, dyvals, dzvals, fvals, print_counter);
			print_counter++;
			//Gather all the local data into global data for printing the solution
			if(rank==0) cout << "print finished at timestep :" << t << endl;


		}
		MPI_Barrier( MPI_COMM_WORLD );


		//update local matrix (timestep)---------------------------
		//if(rank==0) cout << "compute timestep update: " << t << endl;
		double f = 0;
		//cout << "i am rank " << rank << "with f=" << f << endl;
		for(double i=1; i<=(n[0]); i++){
			for(double j=1;j<=(n[1]); j++){
				for(double k=1; k<=(n[2]); k++){
					f=1./dx[0]*(-2.*u(i,j,k)+u(i+1,j,k)+u(i-1,j,k));
					f+=1./dx[1]*(-2.*u(i,j,k)+u(i,j+1,k)+u(i,j-1,k));
					f+=1./dx[2]*(-2.*u(i,j,k)+u(i,j,k+1)+u(i,j,k+1));
					//cout << "f = " << f << endl; 
					u_old(i,j,k)=u(i,j,k)+dt*f;						
				}
			}
		}
		swap(u,u_old);


		//send ghost cells arround
		//---------------------------------------------------------------------------------------------------
		//send left and right
	
		// Send to the left, recieve from the right
		MPI_Sendrecv(&u.data_[1],1,LR_TYPE,left,lr_tag,
				&u.data_[u.num_x()-1],1,LR_TYPE,right,lr_tag,
				Comm_Cart, &status);

		// Send to the right, recieve from the left
		MPI_Sendrecv(&u.data_[u.num_x()-2],1,LR_TYPE,right,rl_tag,
				&u.data_[0],1,LR_TYPE,left,rl_tag,
				Comm_Cart, &status);


		//BT send/recv
		// Send to top, recieve from bottom
		MPI_Sendrecv(&u.data_[u.num_xy()],1,BT_TYPE,top,bt_tag,
				&u.data_[u.num_xy()*(u.num_z()-1)],1,BT_TYPE,bottom,bt_tag,
				Comm_Cart, &status);

		// Send to bottom, recieve from top
		MPI_Sendrecv(&u.data_[u.num_xy()*(u.num_z()-2)],1,BT_TYPE,bottom,tb_tag,
				&u.data_[0],1,BT_TYPE,top,tb_tag,
				Comm_Cart, &status);

		//FB send/recv
		// Send to front, recieve from back

		MPI_Sendrecv(&u.data_[u.num_x()],1,FB_TYPE,front,fb_tag,
				&u.data_[u.num_xy()-u.num_x()],1,FB_TYPE,back,fb_tag,
				Comm_Cart, &status);

		// Send to back, recieve from front

		MPI_Sendrecv(&u.data_[u.num_xy()-2*u.num_x()],1,FB_TYPE,back,fb_tag,
				&u.data_[0],1,FB_TYPE,front,fb_tag,
				Comm_Cart, &status);

	}
	MPI_Finalize();

}
