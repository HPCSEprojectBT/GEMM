COMPILER 	= mpiCC
OPTI		= -O3
OMP		= -fopenmp
LOAD_EIGEN	= -I ../eigen_src/EIGEN
HEADERS		= ../array_src/output.hpp ../array_src/matrix_setup.hpp ../array_src/send_blocks.hpp ../timer/timer.h


all: timing

timing: timing.cpp $(HEADERS)
	$(COMPILER) $(LOAD_EIGEN) $(OPTI) timing.cpp -o timing.out

verify: verify_old.cpp $(HEADERS)
	$(COMPILER) $(LOAD_EIGEN) $(OPTI) verify_old.cpp -o verify.out

clean:
	rm -f *.out
	rm -f *.csv

run:
	sbatch batch.txt

run_local:
	mpirun -np 4 timing.out 9090 0 1
