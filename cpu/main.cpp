#include<iostream>
#include<vector>
#include<chrono>
#include<algorithm>
#include "common/utils.h"
#include "cpu/include/naive_ijk.h"
#include "cpu/include/naive_ikj.h"
#include "cpu/include/openmp.h"
#include "cpu/include/tiling.h"

int main(){

    int n=1024;
    std::vector<float> a(n*n), b(n*n), c(n*n);
    float expected=2.0f*n;  //a=1.0,b=2.0 => c[i][j]=sum(1.0*2.0)=2.0*n(验证结果是否正确)
    init_matrices(a,b,n);

    //Naive(ijk)                 （四个版本都是函数模板+lambda表达式)
    double t=benchmark([&](){
        std::fill(c.begin(),c.end(),0.0f);//刷新
        gemm_naive_ijk(a.data(),b.data(),c.data(),n);
    });
    std::cout<<"Time: "<<t<<" S"<<std::endl;
    std::cout<<"Naive(ijk)的GFLOPS："<<(2.0*n*n*n/t/1e9)<<std::endl<<std::endl;

    //Naive(ikj)
    t=benchmark([&](){
        std::fill(c.begin(),c.end(),0.0f);//刷新
        gemm_naive_ikj(a.data(),b.data(),c.data(),n);
    });
    std::cout<<"Time: "<<t<<" S"<<std::endl;
    std::cout<<"Naive(ikj)的GFLOPS："<<(2.0*n*n*n/t/1e9)<<std::endl<<std::endl;

    //OpenMP
    t=benchmark([&](){
        std::fill(c.begin(),c.end(),0.0f);//刷新
        gemm_openmp(a.data(),b.data(),c.data(),n);
    });
    std::cout<<"Time: "<<t<<" S"<<std::endl;
    std::cout<<"OpenMP的GFLOPS："<<(2.0*n*n*n/t/1e9)<<std::endl<<std::endl;

    //Tiling
    t=benchmark([&](){
        std::fill(c.begin(),c.end(),0.0f);//刷新
        gemm_tiling(a.data(),b.data(),c.data(),n);
    });
    std::cout<<"Time: "<<t<<" S"<<std::endl;
    std::cout<<"Tiling的GFLOPS："<<(2.0*n*n*n/t/1e9)<<std::endl<<std::endl;

    return 0;
}
