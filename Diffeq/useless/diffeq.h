#include "3dgrid.h"

class diffeq
{
public:
	diffeq(size_t N_,int scheme_);

	void timestep();

private:
	unsigned N;

	vector<grid3d<double> >  data;

	unsigned current;

	int scheme;

	double dx, dt;


};