#include <iostream>
#include <algorithm>
#include "3dhpcmatrix.hpp"



void test_column_major() {

	std::cout<<"Testing matrix (column major)"<<std::endl;
	matrix<double> m(3,3,3);

	// Test num_rows(), num_cols()
	std::cout << "Num rows:" << num_x(m) << ", size1: " << m.size1() << std::endl;
	std::cout << "Num cols:" << num_y(m) << ", size2: " << m.size2() << std::endl;
	std::cout << "Num zdir:" << num_z(m) << ", size3: " << m.size3() << std::endl;

	std::cout << "Leading dimension: " << leading_dimension(m) <<std::endl;

	// Test element access
	/*
	m(0,0,0) = 1.0;
	m(0,0,2) = 2.0;
	m(0,1,2) = 0.1;
	m(1,1,1) = 1.1;
	m(2,2,0) = 0.2;*/
	double value = 0;
	for (int k=0; k<3; ++k){
		for (int j=0;j<3; ++j){
			for (int i=0; i<3;++i){
				m(i,j,k)=value;
				value += 1.;
			}
		}
	}
	m.print_val_vec();

	//  Test ostream
	std::cout << m << std::endl;

	//  Test access to data pointer
	//std::transform( m.data(), m.data() + (num_rows(m)*num_cols(m)), m.data(), [](double v){ return v + 5;} );

	//  Test copy constructor
	matrix<double> a(m);
	std::cout << a << std::endl;

	// Test swap
	matrix<double> b(3,3,3);
	swap(b,m);
	std::cout <<"m = " << m << std::endl;
	std::cout <<"b = " << b << std::endl;

	// Test assignment
	m = b;

	std::cout <<"m = " << m << std::endl;
	std::cout <<"b = " << b << std::endl;
}


int main() {
	test_column_major();
	return 0;
}
