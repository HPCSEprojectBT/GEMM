COMPILER 	= mpiCC
OPTI		= -O3
OMP			= -fopenmp
HEADERS		= aligned_allocator.hpp 3dhpcmatrix.hpp vtk_writer.hpp output.hpp

all: final

final: diffusion_final.cpp timer.cpp timer.h $(HEADERS)
	$(COMPILER) $(OMP) $(OPTI) diffusion_final.cpp timer.cpp -o diffusion.out


testcases: hybrid_t matrix_t mpi_t vtk_t correctness_t benchmark_t

correctness_t: testcases/diffusion.cpp $(HEADERS)
	$(COMPILER) $(OPTI) testcases/diffusion.cpp -o testcases/correctness.out

benchmark_t: testcases/diffusion_timing.cpp timer.cpp timer.h $(HEADERS)
	$(COMPILER) $(OPTI) testcases/diffusion_timing.cpp timer.cpp -o testcases/benchmark.out

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

out_clean:
	rm -f output/*
	rm -f testcases/output/*
	rm -f *.csv
	
clean:
	rm -f *.out
	rm -f testcases/*.out
	rm -f output/*
	rm -f testcases/output/*
	rm -f *.csv
