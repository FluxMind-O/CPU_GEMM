#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

int main() {
    int n = 1024;
    std::vector<float> a(n * n), b(n * n), c(n * n, 0);

    for (int i = 0; i < n * n; i++) {
        a[i] = 1.0f;
        b[i] = 2.0f;
    }

    const int block_size = 256;     //措施1:分块大小改成更合适的256

    double min_seconds = 1e9;
    int run = 20;

    for (; run > 0; run--) {

        std::fill(c.begin(), c.end(), 0.0f);

        auto start = std::chrono::high_resolution_clock::now();

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

        auto end = std::chrono::high_resolution_clock::now();
        double seconds = std::chrono::duration<double>(end - start).count();

        if (seconds < min_seconds) min_seconds = seconds;
    }

    std::cout << "Time: " << min_seconds << " S" << std::endl;
    std::cout << "Tiling的GFLOPS: " << (2.0 * n * n * n / min_seconds / 1e9) << std::endl;

    return 0;
}
