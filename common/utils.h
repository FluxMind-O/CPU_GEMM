#pragma once
#include <vector>
#include <chrono>
#include <cmath>
#include <iostream>
#include <algorithm>

inline void init_matrices(std::vector<float>& a, std::vector<float>& b, int n, float av = 1.0f, float bv = 2.0f) {
    for (int i = 0; i < n * n; i++) {
        a[i] = av;
        b[i] = bv;
    }
}

inline bool verify(const std::vector<float>& c, int n, float expected) {
    for (int i = 0; i < n * n; i++) {
        if (std::fabs(c[i] - expected) > 1e-4f) {
            std::cerr << "Mismatch at index " << i << ": got " << c[i] << ", expected " << expected << std::endl;
            return false;
        }
    }
    return true;
}

template<typename Func>
inline double benchmark(Func&& func, int runs = 20) {
    double min_seconds = 1e9;
    for (int r = 0; r < runs; r++) {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        double seconds = std::chrono::duration<double>(end - start).count();
        if (seconds < min_seconds) min_seconds = seconds;
    }
    return min_seconds;
}

inline double compute_gflops(int n, double seconds) {
    return (2.0 * n * n * n / seconds / 1e9);
}
