CUDA_COMPILER = nvcc
COMPILER = CC
EIGENPATH = ../eigen_src/EIGEN
CUHEADERS = ../cuda_src/gemm.h ../cuda_src/gemm.cuh
HEADERS		= ../array_src/output.hpp ../array_src/matrix_setup.hpp ../array_src/send_blocks.hpp ../timer/timer.h
OPTI = -O3

all: timing

timing: timing.cpp $(HEADERS) $(CUHEADERS)
	$(CUDA_COMPILER) -c ../cuda_src/gemm.cu 
	$(COMPILER) -I $(EIGENPATH) $(OPTI) timing.cpp gemm.o -o gemm.x

clean: 
	rm -f *.x 
	rm -f core
	rm -f *.o
clean_slurm:
	rm -f slurm*
	rm -f output_thread_*
run:
	sbatch batch.txt

run2: clean clean_slurm all run
