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

    auto start=std::chrono::high_resolution_clock::now();

    //native_GEMM
    for (int i = 0;i < n; i++)  //遍历前矩阵的每一行
     for (int j = 0;j < n; j++)  //遍历后矩阵的每一列
       for (int k = 0;k < n;k++) 
        c[i*n+j]+= a[i*n+k]*b[k*n+j];  // 理解成：C[i][j] += A[i][k]+B[k][j]

    auto end=std::chrono::high_resolution_clock::now();
    double seconds=std::chrono::duration<double>(end-start).count();

    std::cout<<"Time: "<<seconds<<" S"<<std::endl;
    std::cout << "GFLOPS: " << (2.0 * n * n * n / seconds / 1e9) << std::endl;
    
    return 0;  

}