#include <stdio.h>
// Matrices are stored in col-major order:

__global__ void MatMulKernel(float * ad, float * bd, float *cd, unsigned n);
