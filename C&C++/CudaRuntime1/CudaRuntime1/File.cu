#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>


#define THREAD_NUM 128  // CUDA kernel should generate 128 threads per block

__global__ void stencil1D(int* a, int* c, int vec_size, int radius) {
    //a
    int* temp = (int*)malloc(vec_size * sizeof(int));
    temp[threadIdx.x] = a[threadIdx.x];
    int result = 0;
    /*
    if (threadIdx.x + offset < 0)
    {
        for (offset = 0; offset <= radius; offset++)
            result += temp[threadIdx.x + offset];
    }
    else if (vec_size < threadIdx.x + radius)
    {
        for (offset = 0; threadIdx.x + radius <= vec_size; offset++)
            result += temp[threadIdx.x + offset];
    }
    else
    {
        for (offset = -radius; offset <= radius; offset++)
            result += temp[threadIdx.x + offset];
    }
    */

    __syncthreads();

    
    for (int offset = -radius; offset <= radius; offset++) {
        if (threadIdx.x + offset < 0 || vec_size < threadIdx.x + offset)
            continue;
        else
            result += a[threadIdx.x + offset];
    }
    c[threadIdx.x] = result;

}

void vector_init(int* x, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        x[i] = i;
    }
}



int main(void)
{
    int N, Radius, * a, * c, * d_a, * d_c;
    printf("vector size, and radius of stencil :");
    scanf("%d %d", &N, &Radius); // get the size of vectors as a keyboard input

  //b
    // Alloc space for device copies
    cudaMalloc((void**)&d_a, N);
    cudaMalloc((void**)&d_c, N);

    a = (int*)malloc(N * sizeof(int)); vector_init(a, N);
    c = (int*)malloc(N * sizeof(int));

    //c
    // Copy to device
    cudaMemcpy(d_a, a, N, cudaMemcpyHostToDevice);
    cudaMemcpy(d_c, c, N, cudaMemcpyHostToDevice);

   //d stencil1D
    //stencil1D << <N, N >> > (d_a, d_c, 20, 4);
    stencil1D<<<1, N>>>(d_a, d_c, N, Radius);
    //e
    // Copy result back to host
    cudaMemcpy(c, d_c, N, cudaMemcpyDeviceToHost);

    for (int i=0;i<N;i++) printf("a[%d]=%d , c[%d]=%d\n",i,a[i],i,c[i]);       
    free(a); free(c); cudaFree(d_a); cudaFree(d_c);
    return 0;





}
