COMPILER 	= mpiCC
OPTI		= -O3
OMP			= -fopenmp
LOAD_EIGEN	= -I ~/Eigen_lib
HEADERS		= output.hpp matrix_setup.hpp send_blocks.hpp

#final
all: timing

timing: cannon_acc_ready.cpp $(HEADERS) timer.cpp timer.h
	$(COMPILER) $(LOAD_EIGEN) cannon_acc_ready.cpp timer.cpp timer.h -o timing.out

correctness: cannon_array_verfiy.cpp $(HEADERS) timer.cpp timer.h
	$(COMPILER) $(LOAD_EIGEN) cannon_array_verfiy.cpp timer.cpp timer.h -o verify.out

clean:
	rm -f *.out

run_cannon:
	mpirun -np 9 cannon.out 10 0 0

run_verify:
	mpirun -np 4 verify.out 8 0 0

