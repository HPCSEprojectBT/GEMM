#ifndef _VTK_WRITER
#define _VTK_WRITER

#include <iostream>
#include <ostream>
#include <fstream>
#include <cassert>
#include <vector>

using namespace std;

void write_3d(vector<double> & x, vector<double> & y, vector<double> & z, vector<double> & val, int timestep)
{
	assert(x.size()==y.size() && y.size()==z.size() && z.size()==val.size());
	char filename[160];
	sprintf(filename, "./output/diff_%d.vtk",timestep);
	ofstream out(filename);
	out << 	"# vtk DataFile Version 2.0" << endl;
	out << "unstructured grid legacy vtk file with point scalar data" << endl;
	out << "ASCII" << endl << endl;

	out << "DATASET UNSTRUCTURED_GRID" << endl;
	out << "POINTS " << val.size() << " double" << endl;
	for (int i=0; i<x.size(); ++i)
	{
		out << x[i] << " " << y[i] << " " << z[i] << endl;
	}
	out << endl;
	out << "POINT_DATA " << val.size() << endl;
	out << "SCALARS Temperature double" << endl;
	out << "LOOKUP_TABLE default" << endl;
	for (int i=0; i<x.size(); ++i)
	{
		out << val[i] << endl;
	}
	out.close();
}

#endif
