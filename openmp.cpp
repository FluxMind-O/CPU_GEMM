#include<iostream>
#include<vector>
#include<chrono>
#include<omp.h>

int main(){

    int n=1024;
    std::vector<float> a(n*n),b(n*n),c(n*n,0);

    for (int i = 0; i < n*n; i++)
    {
        a[i]=1.0;
        b[i]=2.0;
    }

    double min_seconds=1e9;
    int run=20;   //跑20次，取最小值

    for(;run>0;run--){

        std::fill(c.begin(), c.end(), 0.0f);//刷新
        
        auto start=std::chrono::high_resolution_clock::now();

        //openmp_GEMM
        #pragma omp parallel for num_threads(4) schedule(static)   //工作共享结构for; 常用子句num_threads() schedule(); (有的还要在后面接同步结构) 
        for (int i = 0;i < n; i++)  
         for (int k = 0;k < n; k++)  
          for (int j = 0;j < n;j++) 
           c[i*n+j]+= a[i*n+k]*b[k*n+j];  

        auto end=std::chrono::high_resolution_clock::now();
        double seconds=std::chrono::duration<double>(end-start).count();

        if(seconds<min_seconds) min_seconds=seconds;
    }
    
    std::cout<<"Time: "<<min_seconds<<" S"<<std::endl;
    std::cout<<"OpenMp的GFLOPS："<< (2.0 * n * n * n / min_seconds / 1e9) <<std::endl;

    return 0;  

}
