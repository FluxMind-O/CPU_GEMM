# CPU_GEMM

CPU 上矩阵乘法（GEMM）的四个版本实现与性能对比。

## 项目结构

```
.
├── naive_ijk.cpp      # 基础串行实现（i-j-k）
├── naive_ikj.cpp      # 串行缓存优化（i-k-j）
├── openmp.cpp         # 4 线程 OpenMP 并行
├── tiling.cpp         # 分块 + OpenMP + SIMD 优化
├── .gitignore
└── show/
    ├── README.md      # 详细报告与编译运行指南
    └── GEMM_GFLOPS_chart.svg  # 性能对比折线图
```

## 性能概览

| 版本 | 时间 (S) | GFLOPS |
|------|----------|--------|
| Naive(ijk) | 0.692892 | 3.10 |
| Naive(ikj) | 0.066232 | 32.42 |
| OpenMP | 0.035987 | 59.67 |
| Tiling | 0.021683 | 99.04 |

详细报告、折线图和编译运行指南请见 [show/README.md](show/README.md)。
