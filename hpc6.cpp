Write a CUDA Program for :
1. Addition of two large vectors
2. Matrix Multiplication using CUDA C
 Practical 4
!nvcc --version
nvcc: NVIDIA (R) Cuda compiler driver
Copyright (c) 2005-2023 NVIDIA Corporation
Built on Tue_Aug_15_22:02:13_PDT_2023
Cuda compilation tools, release 12.2, V12.2.140
Build cuda_12.2.r12.2/compiler.33191640_0
!pip install git+https://github.com/afnan47/cuda.git
%load_ext nvcc_plugin
Collecting git+https://github.com/afnan47/cuda.git
 Cloning https://github.com/afnan47/cuda.git to /tmp/pip-req-build-u12yi4kr
 Running command git clone --filter=blob:none --quiet https://github.com/afnan47/cuda.git /tmp/pip
 Resolved https://github.com/afnan47/cuda.git to commit aac710a35f52bb78ab34d2e52517237941399eff
 Preparing metadata (setup.py) ... done
directory /content/src already exists
Out bin /content/result.out
 Addition of two large vectors
%%cu
#include <iostream>
using namespace std;
__global__ void add(int* A, int* B, int* C, int size) {
int tid = blockIdx.x * blockDim.x + threadIdx.x;
if (tid < size) {
C[tid] = A[tid] + B[tid];
}
}
void initialize(int* vector, int size) {
for (int i = 0; i < size; i++) {
vector[i] = rand() % 10;
}
}
void print(int* vector, int size) {
for (int i = 0; i < size; i++) {
cout << vector[i] << " ";
}
cout << endl;
}
int main() {
int N = 4;
int* A, * B, * C;
int vectorSize = N;
size_t vectorBytes = vectorSize * sizeof(int);
A = new int[vectorSize];
B = new int[vectorSize];
C = new int[vectorSize];
initialize(A, vectorSize);
initialize(B, vectorSize);
cout << "Vector A: ";
print(A, N);
cout << "Vector B: ";
print(B, N);
int* X, * Y, * Z;
cudaMalloc(&X, vectorBytes);
cudaMalloc(&Y, vectorBytes);
cudaMalloc(&Z, vectorBytes);
cudaMemcpy(X, A, vectorBytes, cudaMemcpyHostToDevice);
cudaMemcpy(Y, B, vectorBytes, cudaMemcpyHostToDevice);
int threadsPerBlock = 256;
int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;
add<<<blocksPerGrid, threadsPerBlock>>>(X, Y, Z, N);
cudaMemcpy(C, Z, vectorBytes, cudaMemcpyDeviceToHost);
cout << "Addition: ";
print(C, N);
delete[] A;
delete[] B;
delete[] C;
cudaFree(X);
cudaFree(Y);
cudaFree(Z);
return 0;
}
