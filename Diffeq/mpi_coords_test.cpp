#include <iostream>
#include <mpi.h>
#include "3dhpcmatrix.hpp"
#include <math.h>

using namespace std;

int main(int argc, char **argv)
{
	double N = 3;
	double N_new;
	double L = 1;
	int dimensions = 3;
	vector<double> deltax(3,0);
	vector<double> localsize(3,0);

	vector<double> dxvals;
	vector<double> dyvals;
	vector<double> dzvals;
	vector<double> fvals;

	int *periodic = new int[dimensions];
	for(unsigned i=0;i<dimensions;++i){
		periodic[i]=1;
	}
	int reorder = 1;

	MPI_Init(&argc, &argv);

	int size;
	int rank;
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	int dims[3] = {0,0,0};


	MPI_Comm cartesian;
	MPI_Dims_create(size,3,dims);

	if(rank == 0){
		cout << dims[0] << "\t " << dims[1] << "\t" << dims[2] << endl;
	}
	MPI_Cart_create(MPI_COMM_WORLD, 3, dims, periodic, reorder, &cartesian);
	int tag = 777;

	/*************** Create sizes and offsets *********************************/
	if(1 || rank==0){
		int nx,ny,nz;
		double dx,dy,dz;
		localsize[0]=nx=ceil(N/dims[0]);
		localsize[1]=ny=ceil(N/dims[1]);
		localsize[2]=nz=ceil(N/dims[2]);

		deltax[0]=dx=L/(nx*dims[0]);
		deltax[1]=dy=L/(ny*dims[1]);
		deltax[2]=dz=L/(nz*dims[2]);

		N_new = nx*ny*nz*size;

		cout << "the local sizes are: " << nx << "\t" << ny << "\t" << nz << endl;
		cout << "the meshwidth is: " 	<< deltax[0] << "\t" << deltax[1] << "\t" << deltax[2] << endl;
		cout << "the new problem size is: " << N_new << endl;

		dxvals.resize(N_new);
		dyvals.resize(N_new);
		dzvals.resize(N_new);
		fvals.resize(N_new);

	}

	MPI_Barrier( MPI_COMM_WORLD );




	matrix<int> mygrid(localsize[0]+2,localsize[1]+2,localsize[2]+2);

	for(unsigned i=0;i<mygrid.num_x();i++){
		for(unsigned j=0;j<mygrid.num_y();j++){
			for(unsigned z=0;z<mygrid.num_z();z++){
				mygrid(i,j,z)=rank;
			}
		}
	}


	for( int rankcnt = 0; rankcnt < size; ++rankcnt ) {
		MPI_Barrier( MPI_COMM_WORLD );
		if ( rankcnt == rank ) {
			cout << "this is the matrix stored in rank " << rank << endl;
			int mysize=localsize[0]*localsize[1]*localsize[2];
			vector<double> ldxvals(mysize);
			vector<double> ldyvals(mysize);
			vector<double> ldzvals(mysize);
			vector<double> lfvals(mysize);

			int mycoords[3] ={0,0,0};

			MPI_Cart_coords(cartesian,rank,3,mycoords);

			cout << "my coords are: " << mycoords[0] << "\t" <<mycoords[1] << "\t" << mycoords[2] << endl;

			double offsetx, offsety, offsetz;
			offsetx = mycoords[0]*(localsize[0])*deltax[0];
			offsety = mycoords[1]*(localsize[1])*deltax[1];
			offsetz = mycoords[2]*(localsize[2])*deltax[2];

			double ldx, ldy, ldz;

			ldx=deltax[0];
			ldy=deltax[1];
			ldz=deltax[2];

			cout << "my offsets are: " << offsetx << "\t" << offsety << "\t" << offsetz << endl;


 			int cnt=0;
			for(double i=1; i<=(localsize[0]); i++){
				for(double j=1;j<=(localsize[1]); j++){
					for(double z=1; z<=(localsize[2]); z++){
						ldxvals[cnt] = offsetx+(i-1)*ldx;
						ldyvals[cnt] = offsety+(j-1)*ldy;
						ldzvals[cnt] = offsetz+(z-1)*ldz;
						lfvals[cnt]	 = mygrid(i,j,z);
						cnt++;
					}
				}
			}

			cout << "output is written, now showing the pairs" << endl;
			for(unsigned i=0; i<mysize; i++){
				cout << "Value " << i << " , xcord: " << ldxvals[i] << "\tycoord: " << ldyvals[i] << "\tzcoord: " << ldzvals[i] << endl;
			}

		}
	}
	MPI_Barrier( MPI_COMM_WORLD );





	MPI_Finalize();


	
	return 0;
}