COMPILER 	= CC
OPTI		= -O3
OMP		= -fopenmp
#===LOAD_EIGEN	= -I ../array_src/EIGEN
HEADERS		= ../array_src/output.hpp ../array_src/matrix_setup.hpp ../array_src/send_blocks.hpp ../timer/timer.h

#final
all: timing

timing: timing.cpp $(HEADERS)
	$(COMPILER) $(OPTI) timing.cpp -o timing.out

verify: verify_old.cpp $(HEADERS)
	$(COMPILER) $(OPTI) verify_old.cpp -o verify.out

clean:
	rm -f *.out
	rm -f *.csv

run:
	sbatch batch.txt
