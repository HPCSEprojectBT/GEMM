COMPILER 	= mpiCC
OPTI		= -O3
OMP		= -fopenmp
LOAD_EIGEN	= -I ../array_src/EIGEN
HEADERS		= ../array_src/output.hpp ../array_src/matrix_setup.hpp ../array_src/send_blocks.hpp ../timer/timer.h

#final
all: clean timing verify

timing: timing.cpp $(HEADERS)
	$(COMPILER) $(OMP) $(OPTI) timing.cpp -o timing.out

verify: verify.cpp $(HEADERS)
	$(COMPILER) $(OMP) $(OPTI) verify.cpp -o verify.out

clean:
	rm -f *.out
	rm -f *.csv

run:
	mpirun -np 4 verify.out 8 0 0
