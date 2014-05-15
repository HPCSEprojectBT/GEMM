#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "vtk_writer.hpp"

using namespace std;

int main ()
{
	double n = 5;
	vector<double> x(n*n*n);
	vector<double> y(n*n*n);
	vector<double> z(n*n*n);
	vector<double> val(n*n*n);
	srand(777);

	double dx = 1./n;
	int index =0;
	for (int i=0; i<n; ++i){
		for (int j=0; j<n; ++j){
			for (int k=0; k<n; ++k) {
				x[index] = dx*i;
				y[index] = dx*j;
				z[index] = dx*k;
				index++;
			}
		}
	}


	for (int t=0; t<100; ++t)
	{
		for (int i=0; i<val.size(); ++i) {
			val[i]=rand()%10;
		}
		write_3d(x,y,z,val,t);
	}

}
