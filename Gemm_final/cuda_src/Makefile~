CUDA_COMPILER = nvcc
COMPILER = CC
EIGEN_PATH = ~/libs/eigen
HEADERS = gemm.h gemm.cuh

all: gemm_test

gemm_test: gemm.cu main_cuda_eigen.cpp $(HEADERS)
	$(CUDA_COMPILER) -c gemm.cu 
	$(COMPILER) -I $(EIGEN_PATH) -o gemm.x main_cuda_eigen.cpp gemm.o

gemm_test_2d: gemm.cu main_cuda_2d.cpp $(HEADERS)
	$(CUDA_COMPILER) -c gemm.cu 
	$(COMPILER) -I $(EIGEN_PATH) -o gemm.x main_cuda_2d.cpp gemm.o

clean: 
	rm -f *.x 
	rm -f core
	rm -f *.o
clean_slurm:
	rm -f slurm*

batch:
	sbatch  batch_cuda.txt
