#include "diffeq.h"
#include <algorithm>

diffeq::diffeq(size_t N_,int scheme_)
	: N(N_), data(2,grid3d<double> (N_)), current(0), scheme(scheme_), dx(10.0/N_), dt(0.000001)
{ }

void diffeq::timestep()
{
	cout << "hoi" << endl;
	int next;
	if(current==0){
		next=1;
	}
	else if(current==1){
		next=0;
	}
	if(scheme==0){ // Forward Üler
		for(unsigned i=0; i<N ; ++i){
			for(unsigned j=0; j<N; ++j){
				for(unsigned k=0; k<N; ++k){
					grid[]
				}
			}
		}
	}

	if(current==0){
		current++
	}
	else if(current==1){
		current--;
	}
	else{
		cout << "fatal error !" << endl;		
	}
}