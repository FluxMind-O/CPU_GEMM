#include<iostream>
#include<vector>

#include "common/utils.h"
#include"naive_g.cuh"

int main(){
      
    const int N=1024;
    std::vector<float> h_a(N*N), h_b(N*N), h_c(N*N);
    const float expected=2.0f*N;  
    init_matrices(h_a,h_b,N);
    const size_t M=static_cast<size_t>(N)*N*sizeof(float);

    float *d_a ,*d_b ,d_c;
    cudaMalloc(&d_a,M);
    cudaMalloc(&d_b,M);
    cudaMalloc(&d_c,M);

    cudaMemcpy(d_a,h_a.data(),M,cudaMemcpyHostToDevice);
    cudaMemcpy(d_b,h_b.data(),M,cudaMemcpyHostToDevice);



    
    


}

