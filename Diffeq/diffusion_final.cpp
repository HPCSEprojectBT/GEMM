#include <iostream>
#include <math.h>
#include <mpi.h>

#include "3dhpcmatrix.hpp"
#include "vtk_writer.hpp"
#include "timer.h"
#include "output.hpp"

//#define _print_results

using namespace std;

unsigned t_max; //number of timesteps
unsigned max_runs; //number of timing runs
unsigned N; //target global number of DOFS in each direction
unsigned num_threads; //opmp threads used per rank
bool print_results;
bool non_blocking_communication;
char timing_filename[160];

double init_heat = 777777776;
int print = 1000;
double L = 1.0;
double dt;

//MPI TYPES AND STUFF--------------------------
//send left and right
int lr_tag = 12;
int rl_tag = 21;
int bt_tag = 13;
int tb_tag = 31;
int fb_tag = 14;
int bf_tag = 41;

MPI_Datatype LR_TYPE, BT_TYPE, FB_TYPE;


void send_ghostcells_non_blocking(int * mycoords, MPI_Request * reqs, MPI_Status * status, matrix<double> & u, MPI_Comm & Comm_Cart, int left, int right, int top, int bottom, int front, int back)
{
	//send left and right	
	if (mycoords[0]%2==0){
		MPI_Isend(&u.data_[1],1,LR_TYPE,left,lr_tag,Comm_Cart,&reqs[0]); //send left bound to left
		MPI_Irecv(&u.data_[0],1,LR_TYPE,left,lr_tag,Comm_Cart, &reqs[1]); //recieve right boundary from left as left boundary
		MPI_Isend(&u.data_[u.num_x()-2],1,LR_TYPE, right, lr_tag,Comm_Cart, &reqs[2]); //send right bound to right
		MPI_Irecv(&u.data_[u.num_x()-1],1,LR_TYPE,right,lr_tag,Comm_Cart, &reqs[3]);  //recieve left boundary from right as right boundary		
	}
	else {
		MPI_Irecv(&u.data_[u.num_x()-1],1,LR_TYPE,right,lr_tag,Comm_Cart, &reqs[0]);  
		MPI_Isend(&u.data_[u.num_x()-2],1,LR_TYPE, right, lr_tag,Comm_Cart, &reqs[1]); 
		MPI_Irecv(&u.data_[0],1,LR_TYPE,left,lr_tag,Comm_Cart, &reqs[2]); 
		MPI_Isend(&u.data_[1],1,LR_TYPE,left,lr_tag,Comm_Cart,&reqs[3]); 
	}
	//BT send/recv
	if (mycoords[1]%2==0){
		MPI_Isend(&u.data_[u.num_xy()],1,BT_TYPE,top,bt_tag,Comm_Cart,&reqs[4]); 
		MPI_Irecv(&u.data_[0],1,BT_TYPE,top,bt_tag,Comm_Cart, &reqs[5]); 
		MPI_Isend(&u.data_[u.num_xy()*(u.num_z()-2)],1,BT_TYPE, bottom, bt_tag,Comm_Cart, &reqs[6]);
		MPI_Irecv(&u.data_[u.num_xy()*(u.num_z()-1)],1,BT_TYPE,bottom,bt_tag,Comm_Cart, &reqs[7]); 
	}
	else {
		MPI_Irecv(&u.data_[u.num_xy()*(u.num_z()-1)],1,BT_TYPE,bottom,bt_tag,Comm_Cart, &reqs[4]);
		MPI_Isend(&u.data_[u.num_xy()*(u.num_z()-2)],1,BT_TYPE, bottom, bt_tag,Comm_Cart, &reqs[5]);
		MPI_Irecv(&u.data_[0],1,BT_TYPE,top,bt_tag,Comm_Cart, &reqs[6]);
		MPI_Isend(&u.data_[u.num_xy()],1,BT_TYPE,top,bt_tag,Comm_Cart,&reqs[7]); 
	}
	//FB send/recv
	if (mycoords[2]%2==0){
		MPI_Isend(&u.data_[u.num_x()],1,FB_TYPE,front,fb_tag,Comm_Cart,&reqs[8]); 
		MPI_Irecv(&u.data_[0],1,FB_TYPE,front,fb_tag,Comm_Cart, &reqs[9]); 
		MPI_Isend(&u.data_[u.num_xy()-2*u.num_x()],1,FB_TYPE, back, fb_tag,Comm_Cart, &reqs[10]); 
		MPI_Irecv(&u.data_[u.num_xy()-u.num_x()],1,FB_TYPE,back,fb_tag,Comm_Cart, &reqs[11]);  
	}
	else {
		MPI_Irecv(&u.data_[u.num_xy()-u.num_x()],1,FB_TYPE,back,fb_tag,Comm_Cart, &reqs[11]); 
		MPI_Isend(&u.data_[u.num_xy()-2*u.num_x()],1,FB_TYPE, back, fb_tag,Comm_Cart, &reqs[10]); 
		MPI_Irecv(&u.data_[0],1,FB_TYPE,front,fb_tag,Comm_Cart, &reqs[9]); 
		MPI_Isend(&u.data_[u.num_x()],1,FB_TYPE,front,fb_tag,Comm_Cart,&reqs[8]); 
	}
}

void send_ghostcells_blocking(MPI_Status status, matrix<double> & u, MPI_Comm & Comm_Cart, int left, int right, int top, int bottom, int front, int back)
{
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

}


int main (int argc, char** argv)
{
	//get input arguments
	if (argc < 6) {
		cout << "usage: mpirun -np <num_nodes> " << argv[0] << " dofs_per_site num_timesteps num_runs omp_threads_per_node nonblocking out_number " << endl;
		return 1;
	}
	if (argc == 6) {
		N = atoi(argv[1]);
		t_max = atoi(argv[2]);
		max_runs = atoi(argv[3]);
		num_threads = atoi(argv[4]);
		if(num_threads<=16) omp_set_num_threads(num_threads);
		else omp_set_num_threads(16);
		non_blocking_communication = atoi(argv[5]);
		sprintf(timing_filename,"timing.csv");
	}
	
	else {
		N = atoi(argv[1]);
		t_max = atoi(argv[2]);
		max_runs = atoi(argv[3]);
		num_threads = atoi(argv[4]);
		if(num_threads<=16) omp_set_num_threads(num_threads);
		else omp_set_num_threads(16);
		non_blocking_communication = atoi(argv[5]);
		sprintf(timing_filename,"timing_%d.csv",atoi(argv[6]));
	}

	//MPI Init and CartComm creationy
	MPI_Init(&argc, &argv);
	int size;
	int rank;
	MPI_Status status;
	MPI_Request reqs[12];
	MPI_Status send_status[12];
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	int dims[3]={0,0,0};
	int N_new; //total global number of DOFS after rounding
	int N_x, N_y, N_z; //DOFS per direction after rounding
	vector<double> dx(3,0); //discrete spacing in each direction
	vector<double> n(3,0); //local number of DOFS in x,y,z direction
	int local_dofs; //number of local dofs per matrix
	//char timing_filename[160];
	Timer T;

	//sprintf(timing_filename, filename);
	ofstream timing_out(timing_filename, ios::app);


	MPI_Comm Comm_Cart; //communicator with topology
	MPI_Dims_create(size,3,dims); //fills the dims array automatically

	// print_cartesian_dims(&dims, rank);

	int *periodic = new int[3];
	for(unsigned i=0;i<3;++i) periodic[i]=1;
	int reorder = 1;

	MPI_Cart_create(MPI_COMM_WORLD, 3, dims, periodic, reorder, &Comm_Cart); //creates the communicator
	int left, right, bottom, top, front, back, newrank; 
	MPI_Comm_rank(Comm_Cart,&newrank); //new_rank is the rank in the cartesian communicator

	MPI_Cart_shift(Comm_Cart, 0, 1, &left, &right);
	MPI_Cart_shift(Comm_Cart, 2, 1, &bottom, &top);
	MPI_Cart_shift(Comm_Cart, 1, 1, &front, &back);

	// print_neighbours(rank, left, right, top, bottom, front, back);

	//compute (local) sizes and offsets:
	for (int i=0; i<3; ++i){ //compute local matrix setting
		n[i]=ceil(double(N)/dims[i]);
		dx[i]=L/(n[i]*dims[i]);
	}

	//choose stable timestep
	dt = (dx[0]*dx[1]*dx[2])/10.;

	N_new = n[0]*n[1]*n[2]*size; //round up N
	N_x = n[0]*dims[0];
	N_y = n[1]*dims[1];
	N_z = n[2]*dims[2];

	matrix<double> u(n[0]+2,n[1]+2,n[2]+2); //local matrix including ghost plains
	matrix<double> u_old(n[0]+2,n[1]+2,n[2]+2);//local matrix including ghost plains

	// find the rank closest to the middle
	int center[3] = {0,0,0};
	center[0] = round(double(dims[0])/2.0)-1;
	center[1] = round(double(dims[1])/2.0)-1;
	center[2] = round(double(dims[2])/2.0)-1;
	int centerrank;
	MPI_Cart_rank(Comm_Cart,center,&centerrank);

	// print_center(rank, &center, centerrank);



	MPI_Type_vector(u.num_yz(),u.blocklength_yz(),u.stride_yz(), MPI_DOUBLE, &LR_TYPE); //prepare type for left/right sends
	MPI_Type_commit(&LR_TYPE);
	MPI_Type_contiguous(u.num_xy(),MPI_DOUBLE, &BT_TYPE); //prepare type for bottom/top sends
	MPI_Type_commit(&BT_TYPE);
	MPI_Type_vector(u.num_z(),u.blocklength_xz(),u.stride_xz(), MPI_DOUBLE, &FB_TYPE); //prepare type for front/back sends
	MPI_Type_commit(&FB_TYPE);
	//----------------------------------------------

	//get coordinates of the process in cartesian grid
	int mycoords[3] ={0,0,0};
	MPI_Cart_coords(Comm_Cart,rank,3,mycoords);


	//compute global index vectors, offsets
	//local vectors per local matrix
	local_dofs = n[0]*n[1]*n[2];
	vector<double> ldxvals(local_dofs);
	vector<double> ldyvals(local_dofs);
	vector<double> ldzvals(local_dofs);
	vector<double> lfvals(local_dofs);


	//compute the offsets of the local coordinates w.r.t. global coords
	double offsetx, offsety, offsetz;
	offsetx = mycoords[0]*(n[0])*dx[0];
	offsety = mycoords[1]*(n[1])*dx[1];
	offsetz = (dims[2]-1-mycoords[2])*(n[2])*dx[2];

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
	//print_offsets(rank,size,offsetx, offsety, offsetz);

	//------------------------START TIMESTEPPING -----------------------------------------------
	//------------------------------------------------------------------------------------------
	int print_counter = 0;
	vector<double> dxvals(N_new);
	vector<double> dyvals(N_new);
	vector<double> dzvals(N_new);
	vector<double> fvals(N_new);	

	//==================================================================================
	//----------------------------do several runs from here on -------------------------
	//==================================================================================

	if (rank==0) timing_out << size << "\t" << N_new << "\t";
	for (int run=0; run<max_runs; run++) { //RUN LOOP
		if (rank==0) cout << "performing run " << run << endl;

		//generate initial local matrizes without ghost cells
		for (int k=1; k<=n[2]; ++k) {
			for (int j=1; j<=n[1]; ++j) {
				for (int i=1; i<=n[0]; ++i) {
					if (rank == centerrank) u(i,j,k) = init_heat; //inital heat field
					else u(i,j,k) = 0;
				}
			}
		}

		// print_matrices(u,size, rank);

		//initial ghost cell distribution:
		send_ghostcells_non_blocking(mycoords,reqs,send_status,u,Comm_Cart,left,right,top,bottom,front,back);
		MPI_Waitall(12,reqs,send_status);	
		u_old=u;

		MPI_Barrier(MPI_COMM_WORLD);

		unsigned ln0 = n[0];
		unsigned ln1 = n[1];
		unsigned ln2 = n[2];
		double f;

		//-------- START TTIMING ------------------------------
		if (rank==0) T.tic(); //start timing
		for (int t=0; t<t_max; ++t){//TIMESTEP LOOP
#ifdef _print_results
			if(t%print==0){

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


				if (rank ==0) write_3d(dxvals, dyvals, dzvals, fvals, print_counter,N_x, N_y, N_z);
				print_counter++;
				//Gather all the local data into global data for printing the solution
				if(rank==0) cout << "print finished at timestep :" << t << endl;
			}
			MPI_Barrier( MPI_COMM_WORLD );
#endif

			if (t!=0){
				if(non_blocking_communication){
					send_ghostcells_non_blocking(mycoords,reqs,send_status,u,Comm_Cart,left,right,top,bottom,front,back);
				}
				else {
					send_ghostcells_blocking(status,u,Comm_Cart,left,right,top,bottom,front,back);	
				}
			}

			if(non_blocking_communication){
				//compute interior diffusion values
#pragma omp parallel for collapse(3) shared(ln0, ln1, ln2, dx, u, u_old) private(f)
				for(unsigned i=2; i<ln0; i++){
					for(unsigned j=2;j<ln1; j++){
						for(unsigned k=2; k<ln2; k++){
							f=1./dx[0]*(-2.*u(i,j,k)+u(i+1,j,k)+u(i-1,j,k));
							f+=1./dx[1]*(-2.*u(i,j,k)+u(i,j+1,k)+u(i,j-1,k));
							f+=1./dx[2]*(-2.*u(i,j,k)+u(i,j,k+1)+u(i,j,k-1));
							//cout << "f = " << f << endl; 
							u_old(i,j,k)=u(i,j,k)+dt*f;				
						}
					}
				}

				MPI_Waitall(12,reqs,send_status);

				//compute boundary diffusion values
				//update left right boundary values
				for(unsigned i=1; i<=ln0; i+=(ln0-1)){
#pragma omp parallel for collapse(2) shared(ln1, ln2, dx, u, u_old) private(f)
					for(unsigned j=1;j<=ln1; j++){
						for(unsigned k=1; k<=ln2; k++){
							f=1./dx[0]*(-2.*u(i,j,k)+u(i+1,j,k)+u(i-1,j,k));
							f+=1./dx[1]*(-2.*u(i,j,k)+u(i,j+1,k)+u(i,j-1,k));
							f+=1./dx[2]*(-2.*u(i,j,k)+u(i,j,k+1)+u(i,j,k-1));
							//cout << "f = " << f << endl; 
							u_old(i,j,k)=u(i,j,k)+dt*f;	
						}
					}
				}

				//update front back boundary values
				for(unsigned j=1;j<=(ln1); j+=(ln1-1)){
#pragma omp parallel for collapse(2) shared(ln0, ln2, dx, u, u_old) private(f)
					for(unsigned i=1; i<=(ln0); i++){
						for(unsigned k=1; k<=(ln2); k++){
							f=1./dx[0]*(-2.*u(i,j,k)+u(i+1,j,k)+u(i-1,j,k));
							f+=1./dx[1]*(-2.*u(i,j,k)+u(i,j+1,k)+u(i,j-1,k));
							f+=1./dx[2]*(-2.*u(i,j,k)+u(i,j,k+1)+u(i,j,k-1));
							//cout << "f = " << f << endl; 
							u_old(i,j,k)=u(i,j,k)+dt*f;	
						}
					}
				}


				//update bottom top boundary values
				for(unsigned k=1; k<=(ln2); k+=(ln2-1)){
#pragma omp parallel for collapse(2) shared(ln0, ln1, dx, u, u_old) private(f)
					for(unsigned i=1; i<=(ln0); i++){
						for(unsigned j=1;j<=(ln1); j++){
							f=1./dx[0]*(-2.*u(i,j,k)+u(i+1,j,k)+u(i-1,j,k));
							f+=1./dx[1]*(-2.*u(i,j,k)+u(i,j+1,k)+u(i,j-1,k));
							f+=1./dx[2]*(-2.*u(i,j,k)+u(i,j,k+1)+u(i,j,k-1));
							//cout << "f = " << f << endl; 
							u_old(i,j,k)=u(i,j,k)+dt*f;
						}
					}
				}
			}
			else { //blocking
#pragma omp parallel for collapse(3) shared(ln0, ln1, ln2, dx, u, u_old) private(f)
				for(unsigned i=1; i<=ln0; i++){
					for(unsigned j=1;j<=ln1; j++){
						for(unsigned k=1; k<=ln2; k++){
							f=1./dx[0]*(-2.*u(i,j,k)+u(i+1,j,k)+u(i-1,j,k));
							f+=1./dx[1]*(-2.*u(i,j,k)+u(i,j+1,k)+u(i,j-1,k));
							f+=1./dx[2]*(-2.*u(i,j,k)+u(i,j,k+1)+u(i,j,k-1));
							//cout << "f = " << f << endl; 
							u_old(i,j,k)=u(i,j,k)+dt*f;						
						}
					}
				}


			}
			swap(u,u_old);
		}
		MPI_Barrier(MPI_COMM_WORLD);
		if (rank==0){
			timing_out << T.toc();		
			if (run < max_runs -1 ) timing_out << "\t";
		}		
	}
	if (rank==0) timing_out << endl;
	MPI_Finalize();
}
