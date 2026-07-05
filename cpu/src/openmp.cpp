#include<iostream>
#include<vector>
#include<chrono>
#include<omp.h>
#include "cpu/include/openmp.h"

void gemm_openmp(const float* a, const float* b, float* c, int n){

    //openmp_GEMM
    #pragma omp parallel for num_threads(4) schedule(static)   //工作共享结构for; 常用子句num_threads() schedule(); (有的还要在后面接同步结构) 
    for (int i = 0;i < n; i++)  
     for (int k = 0;k < n; k++)  
      for (int j = 0;j < n;j++) 
       c[i*n+j]+= a[i*n+k]*b[k*n+j];  

}