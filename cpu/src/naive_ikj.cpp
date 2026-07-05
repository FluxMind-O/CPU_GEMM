#include<iostream>
#include<vector>
#include<chrono>
#include "cpu/include/naive_ikj.h"

void gemm_naive_ikj(const float* a, const float* b, float* c, int n){

    //native_GEMM
    for (int i = 0;i < n; i++)  //遍历前矩阵的每一行
     for (int k = 0;k < n; k++)  //k
      for (int j = 0;j < n;j++) 
       c[i*n+j]+= a[i*n+k]*b[k*n+j];  // 理解成：C[i][j] += A[i][k]*B[k][j]

}