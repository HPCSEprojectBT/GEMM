COMPILER 	= mpiCC
OPTI		= -O3
OMP			= -fopenmp
HEADERS		= aligned_allocator.hpp 3dhpcmatrix.hpp vtk_writer.hpp

all: correctness benchmark

correctness: diffusion.cpp $(HEADERS)
	$(COMPILER) $(OPTI) diffusion.cpp -o correctness.out

benchmark: diffusion_timing.cpp timer.cpp $(HEADERS)
	$(COMPILER) $(OPTI) diffusion_timing.cpp timer.cpp -o benchmark.out

testcases: hybrid_t matrix_t mpi_t vtk_t

hybrid_t: testcases/diffusion_hybrid_test.cpp testcases/hybrid_test.cpp $(HEADERS)
	$(COMPILER) $(OMP) $(OPTI) testcases/hybrid_test.cpp -o testcases/hybr_vector.out
	$(COMPILER) $(OMP) $(OPTI) testcases/diffusion_hybrid_test.cpp -o testcases/hybr_diff.out

matrix_t: testcases/matrix_mpi_test.cpp testcases/matrix_test.cpp $(HEADERS)
	$(COMPILER) $(OPTI) testcases/matrix_mpi_test.cpp -o testcases/matrix_mpi_test.out
	$(COMPILER) $(OPTI) testcases/matrix_test.cpp -o testcases/matrix_test.out

mpi_t: testcases/mpi_coords_test.cpp testcases/mpi_vectors_testcase.cpp $(HEADERS)
	$(COMPILER) $(OPTI) testcases/mpi_coords_test.cpp -o testcases/mpi_coords_test.out
	$(COMPILER) $(OPTI) testcases/mpi_vectors_testcase.cpp -o testcases/mpi_vectors_testcase.out

vtk_t:testcases/test_vtk.cpp $(HEADERS)
	$(COMPILER) $(OPTI) testcases/test_vtk.cpp -o testcases/test_vtk.out

	
clean:
	rm *.out
	rm testcases/*.out
	rm output/*
