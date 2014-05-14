// Example codes for HPC course
// (c) 2012 Andreas Hehn and Matthias Troyer, ETH Zurich

// a stripped-down matrix class for the examples of the HPC course
#ifndef xyz_HPC_MATRIX_HPP
#define xyz_HPC_MATRIX_HPP
#include <cassert>
#include <iostream>
#include <vector>
#include "aligned_allocator.hpp"


struct column_major {
	static unsigned int size1(unsigned int n_x, unsigned int n_y, unsigned int n_z) {
		return n_x;
	}
	static unsigned int size2(unsigned int n_x, unsigned int n_y, unsigned int n_z) {
		return n_y;
	}
	static unsigned int size3(unsigned int n_x, unsigned int n_y, unsigned int n_z) {
		return n_z;
	}
	static std::size_t index(unsigned int n_x, unsigned int n_y, unsigned n_z, unsigned int i, unsigned int j, unsigned int k)
	{
		return n_x*n_y*k+n_x*j+i;
	}
	
		
	
};

/*
   struct row_major{
   static unsigned int size1(unsigned int n_rows, unsigned int n_cols) {
   return n_cols;
   }
   static unsigned int size2(unsigned int n_rows, unsigned int n_cols) {
   return n_rows;
   }
   static std::size_t index(unsigned int n_rows, unsigned int n_cols, unsigned int i, unsigned int j)
   {
   return n_cols*i+j;
   }
   };*/

template <typename T, typename Ordering = column_major, typename Allocator = hpc12::aligned_allocator<T,64> >
class matrix {
	public:
		typedef T value_type;
		explicit matrix(unsigned int n_x = 0, unsigned int n_y = 0, unsigned int n_z=0, T init = T())
			: data_(n_x*n_y*n_z,init)
			  , n_x_(n_x)
			  , n_y_(n_y)
			  , n_z_(n_z)
	{
	}

		unsigned int num_x() const {
			return n_x_;
		}

		unsigned int num_y() const {
			return n_y_;
		}

		unsigned int num_z() const {
			return n_z_;
		}

		unsigned int num_xy() const { //returns number of elements in xy plane
			return n_x_*n_y_;		
		}

		unsigned int num_yz() const { //returns number of elements in yz plane
			return n_y_*n_z_;		
		}

		unsigned int num_xz() const { //returns number of elements in xz plane
			return n_x_*n_z_;		
		}

		unsigned int blocklength_xy(){ //returns the blocklength of elements in data array
			return n_x_*n_y_;
		}

		unsigned int blocklength_yz(){ //returns the blocklength of elements in data array
			return 1;
		}

		unsigned int blocklength_xz(){ //returns the blocklength of elements in data array
			return n_x_;
		}

		unsigned int stride_xy(){
			return n_x_*n_y_;
		}

		unsigned int stride_yz(){
			return n_x_;
		}

		unsigned int stride_xz(){
			return n_x_*n_y_;
		}

		unsigned int size1() const {
			return Ordering::size1(n_x_,n_y_,n_z_);
		}

		unsigned int size2() const {
			return Ordering::size2(n_x_,n_y_,n_z_);
		}

		unsigned int size3() const {
			return Ordering::size3(n_x_,n_y_,n_z_);
		}


		unsigned int leading_dimension() const {
			return size1();
		}

		// Element access
		value_type& operator()(unsigned int i, unsigned int j, unsigned int k) {
			assert( i < n_x_);
			assert( j < n_y_);
			assert( k < n_z_);
			return data_[Ordering::index(n_x_,n_y_,n_z_,i,j,k)];
		}

		value_type const& operator()(unsigned int i, unsigned int j, unsigned int k) const {
			assert( i < n_x_);
			assert( j < n_y_);
			assert( k < n_z_);
			return data_[Ordering::index(n_x_,n_y_,n_z_,i,j,k)];
		}

		value_type const* data() const {
			return data_.empty() ? 0 : &data_.front();
		}

		value_type* data() {
			return data_.empty() ? 0 : &data_.front();
		}
		
		void print_val_vec() {
			for (int i=0; i<data_.size(); ++i) std::cout << data_[i] << ",";
			std::cout << std::endl;
		}

		friend void swap(matrix& a, matrix& b) {
			using std::swap;
			swap(a.data_,   b.data_);
			swap(a.n_x_, b.n_x_);
			swap(a.n_y_, b.n_y_);
			swap(a.n_z_, b.n_z_);
		}
	private:
		std::vector<value_type,Allocator> data_;
		unsigned int n_x_;
		unsigned int n_y_;
		unsigned int n_z_;
};


// Get number of rows/colums
template <typename T, typename Ordering, typename Allocator>
unsigned int num_x(matrix<T,Ordering,Allocator> const& m) {
	return m.num_x();
}

template <typename T, typename Ordering, typename Allocator>
unsigned int num_y(matrix<T,Ordering,Allocator> const& m) {
	return m.num_y();
}

template <typename T, typename Ordering, typename Allocator>
unsigned int num_z(matrix<T,Ordering,Allocator> const& m) {
	return m.num_z();
}


template <typename T, typename Ordering, typename Allocator>
unsigned int leading_dimension(matrix<T,Ordering,Allocator> const& m) {
	return m.leading_dimension();
}


// A nice operator for the output (to write std::cout << matrix )
template <typename T, typename Ordering, typename Allocator>
std::ostream& operator << (std::ostream& os, matrix<T,Ordering,Allocator> const& m) {
	std::cout << "[";
	for(unsigned int k=0; k < num_z(m); ++k) {
		if(k > 0)
			std::cout << "," << std::endl;
		std::cout << "[";
		for(unsigned int j=0; j < num_y(m); ++j) {
			if(j > 0)
				std::cout << "," ;
			std::cout << "[";
			for(unsigned int i=0; i < num_x(m); ++i) {
				if(i > 0)
					std::cout << ", ";
				std::cout << m(i,j,k);
			}
			std::cout << "]";
		}
		std::cout << "]" ;
	}
	std::cout << "]" << std::endl;
	return os;
}

#endif 
