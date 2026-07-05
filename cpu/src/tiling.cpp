#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>
#include "cpu/include/tiling.h"

void gemm_tiling(const float* a, const float* b, float* c, int n) {
    const int block_size = 256;     //措施1:分块大小改成更合适的256

    #pragma omp parallel for num_threads(4) schedule(static)
    for (int i = 0; i < n; i += block_size)
    for (int k = 0; k < n; k += block_size)
    for (int j = 0; j < n; j += block_size)
    {
        int i_end = i + block_size;
        int k_end = k + block_size;
        int j_end = j + block_size;

        for (int ii = i; ii < i_end; ii++)
        for (int kk = k; kk < k_end; kk++)
        {
            float a_val = a[ii * n + kk];    //措施2:把a的元素从内存提到寄存器
            #pragma omp simd                 //措施3:强制开启SIMD向量化优化
            for (int jj = j; jj < j_end; jj++)
                c[ii * n + jj] += a_val * b[kk * n + jj];   
        }
    }
}