#include "gemm.h"
#include "gemm.cuh"


#define BLOCK_SIZE_X 7
#define BLOCK_SIZE_Y 3

// Matrix multiplication - Host code
// Matrix dimensions are assumed to be multiples of BLOCK_SIZE
//extern "C"
void MatMul( float * a, float * b, float * c, unsigned n) {
		cudaError_t err = cudaSetDeviceFlags(cudaDeviceScheduleBlockingSync);
		printf("set flag: %s\n",cudaGetErrorString(err));
		
		float * ad;
		float * bd;
		float * cd;
		const int array_size = n*n*sizeof(float);

		err = cudaMalloc((void**)&ad, array_size);
		printf("CUDA malloc A: %s\n",cudaGetErrorString(err));

		err = cudaMemcpy(ad, a, array_size, cudaMemcpyHostToDevice);
		printf("Copy A to device: %s\n",cudaGetErrorString(err));

		err = cudaMalloc((void**)&bd, array_size);
		printf("CUDA malloc B: %s\n",cudaGetErrorString(err));

		err = cudaMemcpy(bd, b, array_size, cudaMemcpyHostToDevice);
		printf("Copy B to device: %s\n",cudaGetErrorString(err));

		err = cudaMalloc((void**)&cd, array_size);
		printf("CUDA malloc C: %s\n",cudaGetErrorString(err));

		//err = cudaMemcpy(cd, c, array_size, cudaMemcpyHostToDevice);
		//printf("Copy C to device: %s\n",cudaGetErrorString(err));
	
		// Invoke kernel
		dim3 dimBlock(BLOCK_SIZE_X, BLOCK_SIZE_Y);
		dim3 dimGrid((n + dimBlock.x - 1) / dimBlock.x,
						(n + dimBlock.y - 1) / dimBlock.y);
		
		MatMulKernel<<<dimGrid,dimBlock >>>(ad, bd, cd,n);

		err = cudaDeviceSynchronize();
		printf("Run kernel: %s\n", cudaGetErrorString(err));
		
		// Read C from device memory
		err = cudaMemcpy(c, cd, array_size, cudaMemcpyDeviceToHost);
		printf("Copy C off of device: %s\n",cudaGetErrorString(err));
		
		//err = cudaDeviceSynchronize();
		//printf("Run kernel: %s\n", cudaGetErrorString(err));
		
		cudaFree(ad);
		cudaFree(bd);
		cudaFree(cd);
}
// Matrix multiplication kernel called by MatMul()
__global__ void MatMulKernel(float * ad, float * bd, float * cd, unsigned n) {
		// Each thread computes one element of C
		// by accumulating results into Cvalue
		float Cvalue = 0.0;
		int row = blockIdx.y * blockDim.y + threadIdx.y;
		int col = blockIdx.x * blockDim.x + threadIdx.x;
		if(row >= n || col >= n) return;
		for (int e = 0; e < n; ++e)
			Cvalue += (ad[row+e*n]) * (bd[e + col*n]);
		cd[row + col*n] = Cvalue;
}
