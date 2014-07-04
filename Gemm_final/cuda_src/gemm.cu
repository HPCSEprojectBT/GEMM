#include "gemm.h"
#include "gemm.cuh"


#define BLOCK_SIZE_X 16
#define BLOCK_SIZE_Y 16

// Matrix multiplication - Host code
// Matrix dimensions are assumed to be multiples of BLOCK_SIZE
//extern "C"
void MatMul(float * a, float * b, float * c, unsigned n) {
		// Load A and B to device memory
		//Matrix d_A;
		//d_A.width = A.width;
		//d_A.height = A.height;
		//size_t size = A.width * A.height * sizeof(float);
/*
		Matrix d_A;
		d_A.width = n;
		d_A.height = n;
		size_t size = n*n * sizeof(float);

		cudaError_t err = cudaMalloc(&d_A.elements, size);
		printf("CUDA malloc A matrix: %s\n",cudaGetErrorString(err));
*/
		float * ad;
		float * bd;
		float * cd;
		const int array_size = n*n*sizeof(float);

		cudaError_t err = cudaMalloc((void**)&ad, array_size);
		printf("CUDA malloc A: %s\n",cudaGetErrorString(err));

		err = cudaMemcpy(ad, a, array_size, cudaMemcpyHostToDevice);
		printf("Copy A to device: %s\n",cudaGetErrorString(err));

		err = cudaMalloc((void**)&bd, array_size);
		printf("CUDA malloc B: %s\n",cudaGetErrorString(err));

		err = cudaMemcpy(bd, b, array_size, cudaMemcpyHostToDevice);
		printf("Copy B to device: %s\n",cudaGetErrorString(err));

		err = cudaMalloc((void**)&cd, array_size);
		printf("CUDA malloc C: %s\n",cudaGetErrorString(err));

		err = cudaMemcpy(cd, c, array_size, cudaMemcpyHostToDevice);
		printf("Copy C to device: %s\n",cudaGetErrorString(err));
	
		//printf("cd[7] reads %f\n",cd[7]);
		//printf("ad[7] reads %f\n",ad[7]);
		//printf("bd[7] reads %f\n",bd[7]);
		//printf("c[7] reads %f\n",c[7]);
		//printf("a[7] reads %f\n",a[7]);
		//printf("b[7] reads %f\n",b[7]);

		/*
		Matrix d_B;
		d_B.width = B.width;
		d_B.height = B.height;
		size = B.width * B.height * sizeof(float);

		err = cudaMalloc(&d_B.elements, size);
		printf("CUDA malloc B: %s\n",cudaGetErrorString(err));

		err = cudaMemcpy(d_B.elements, B.elements, size, cudaMemcpyHostToDevice);
		printf("Copy B to device: %s\n",cudaGetErrorString(err));
		
		// Allocate C in device memory
		Matrix d_C;
		d_C.width = C.width;
		d_C.height = C.height;
		size = C.width * C.height * sizeof(float);

		err = cudaMalloc(&d_C.elements, size);
		printf("CUDA malloc C: %s\n",cudaGetErrorString(err));
		*/
		// Invoke kernel
		dim3 dimBlock(BLOCK_SIZE_X, BLOCK_SIZE_Y);
		dim3 dimGrid((n + dimBlock.x - 1) / dimBlock.x,
						(n + dimBlock.y - 1) / dimBlock.y);
		MatMulKernel<<<dimGrid, dimBlock>>>(ad, bd, cd,n);

		err = cudaThreadSynchronize();
		printf("Run kernel: %s\n", cudaGetErrorString(err));
		
		// Read C from device memory
		err = cudaMemcpy(c, cd, array_size, cudaMemcpyDeviceToHost);
		printf("Copy C off of device: %s\n",cudaGetErrorString(err));
		
		//printf("cd[7] reads %f\n",cd[7]);
		//printf("ad[7] reads %f\n",ad[7]);
		//printf("bd[7] reads %f\n",bd[7]);
		//printf("c[7] reads %f\n",c[7]);
		//printf("a[7] reads %f\n",a[7]);
		//printf("b[7] reads %f\n",b[7]);
		// Free device memory
		cudaFree(ad);
		cudaFree(bd);
		// cudaFree(d_C.elements);
}
// Matrix multiplication kernel called by MatMul()
__global__ void MatMulKernel(float * ad, float * bd, float * cd, unsigned n) {
		// Each thread computes one element of C
		// by accumulating results into Cvalue
		float Cvalue = 0.0;
		int row = blockIdx.y * blockDim.y + threadIdx.y;
		int col = blockIdx.x * blockDim.x + threadIdx.x;
		if(row > n || col > n) return;
		for (int e = 0; e < n; ++e)
			Cvalue += (ad[row+e*n]) * (bd[e + col*n]);
		cd[row + col*n] = Cvalue;
}
