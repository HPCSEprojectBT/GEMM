COMPILER 	= mpiCC
OPTI		= -O3
OMP		= -fopenmp
LOAD_EIGEN	= -I ../eigen_src/EIGEN
HEADERS		= ../eigen_src/output.hpp ../eigen_src/matrix_setup.hpp ../eigen_src/send_blocks.hpp ../timer/timer.h

#final
all: timing verify

timing: timing.cpp $(HEADERS)
	$(COMPILER) $(LOAD_EIGEN) $(OPTI) timing.cpp -o timing.out

verify: verify.cpp $(HEADERS)
	$(COMPILER) $(LOAD_EIGEN) $(OPTI) verify.cpp -o verify.out

clean:
	rm -f *.out
	rm -f *.csv

run:
	mpirun -np 4 verify.out 8 0 0
