#ifndef _VTK_WRITER
#define _VTK_WRITER

#include <iostream>
#include <ostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

struct point {
	double x,y,z,val;
	point(double x_, double y_, double z_, double val_) : x(x_),y(y_),z(z_),val(val_)
	{}
};


bool my_cmp(const point& a, const point& b)
{
	if (a.z < b.z) return 1;
	else if (a.z <= b.z && a.y < b.y) return 1;
	else if (a.z <= b.z && a.y <= b.y && a.x<b.x) return 1;
	else return 0;
}

void write_3d(vector<double> & x, vector<double> & y, vector<double> & z, vector<double> & val, int timestep, int dim_x, int dim_y, int dim_z)
{
	
	assert(x.size()==y.size() && y.size()==z.size() && z.size()==val.size());
	vector<point> points;
	
	for (int i=0; i<x.size(); ++i)
	{
		points.push_back(point(x[i],y[i],z[i],val[i]));
	}
/*
	cout <<"unsorted:" << endl;
	for (int i=0; i<points.size(); ++i)
	{
		cout << points[i].x << " " << points[i].y << " " << points[i].z << " " << points[i].val << endl;
	}
*/

	sort(points.begin(), points.end(), my_cmp);
/*
	cout <<"sorted:" << endl;
	for (int i=0; i<points.size();++i)
	{
		cout << points[i].x << " " << points[i].y << " " << points[i].z << " " << points[i].val << endl;
	}
*/


			
	char filename[160];
	sprintf(filename, "./output/diff_%d.vtk",timestep);
	ofstream out(filename);
	out << 	"# vtk DataFile Version 2.0" << endl;
	out << "structured grid legacy vtk file with point scalar data" << endl;
	out << "ASCII" << endl << endl;

	out << "DATASET STRUCTURED_GRID" << endl;
	out << "DIMENSIONS " << dim_x << " " << dim_y << " " << dim_z << endl;
	out << "POINTS " << val.size() << " double" << endl;
	for (int i=0; i<points.size(); ++i)
	{
		out << points[i].x << " " << points[i].y << " " << points[i].z << endl;
	}
	out << endl;
	out << "POINT_DATA " << val.size() << endl;
	out << "SCALARS Temperature double" << endl;
	out << "LOOKUP_TABLE default" << endl;
	for (int i=0; i<points.size(); ++i)
	{
		out << points[i].val << endl;
	}
	out.close();
}

#endif
