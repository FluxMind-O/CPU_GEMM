#include<iostream>
#include<vector>
#include<chrono>

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

        //native_GEMM
        for (int i = 0;i < n; i++)  //遍历前矩阵的每一行
         for (int k = 0;k < n; k++)  //k
          for (int j = 0;j < n;j++) 
           c[i*n+j]+= a[i*n+k]*b[k*n+j];  // 理解成：C[i][j] += A[i][k]*B[k][j]

        auto end=std::chrono::high_resolution_clock::now();
        double seconds=std::chrono::duration<double>(end-start).count();

        if(seconds<min_seconds) min_seconds=seconds;

    }
    
    std::cout<<"Time: "<<min_seconds<<" S"<<std::endl;
    std::cout << "Naive的GFLOPS：" << (2.0 * n * n * n / min_seconds / 1e9) << std::endl;
    
    return 0;  

}