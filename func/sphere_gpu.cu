#include "sphere_gpu.h"

// vetor de entrada armazenado na GPU
real *d_x;

// dimensionalidade do vetor de entrada
int dim;

// funcoes utilitarias
inline real* allocateRealsDev(int n)
{
    real *res;

    if (cudaMalloc((void**) &res, n * sizeof(real)) != cudaSuccess) {
        return NULL;
    }

    return res;
}

// inicializa o armazenamento na GPU
bool init_gpu(int n)
{
    d_x = allocateRealsDev(n);
    if (d_x == NULL)
        return false;

    dim = n;
    return true;
}

void finalize_gpu()
{
    if (d_x != NULL) {
        cudaFree(d_x);
        d_x = NULL;
    }
}


// kernels
__global__ void square_kernel(real *d_x, real *d_res)
{
    int tid = threadIdx.x;
    real x = d_x[tid];

    d_res[tid] = x * x;
}

__global__ void reduction_kernel(real *vec, int span)
{
    int tid = threadIdx.x * span;

    vec[tid] = vec[tid] + vec[tid + span/2];
}

real reduce_sum(int n, real *d_vec)
{
    real *h_vec;
    real sum = 0.0;

    h_vec = (real*) malloc(n * sizeof(real));
    if (h_vec == NULL)
        return 0.0;
    cudaMemcpy(h_vec, d_vec, n * sizeof(real), cudaMemcpyDeviceToHost);
    for (int i = 0; i < n; ++i)
        sum += h_vec[i];

    free(h_vec);
    return sum;
}

real sphere_gpu(real *x)
{
    real res;
    real *d_res;

    d_res = allocateRealsDev(dim);
    if (d_res == NULL)
        return -1.0f;

    // transfere vetor para GPU
    cudaMemcpy(d_x, x, dim * sizeof(real), cudaMemcpyHostToDevice);

    square_kernel<<<1, dim>>>(d_x, d_res);

    // reducao
    res = reduce_sum(dim, d_res);

    cudaFree(d_res);

    return res;
}
