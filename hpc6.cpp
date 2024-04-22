vectorAdd.cu
#include <cstdlib>
#include <iostream>
#define checkCudaErrors(call)
\
 do {
\
 cudaError_t err = call;
\
 if (err != cudaSuccess) {
\
 print("CUDA error at %s %d: %s\n",
__FILE__, __LINE__, cudaGetErrorString(err)); \
 exit(EXIT_FAILURE);
\
 }
\
 } while (0)
using namespace std;
// VectorAdd parallel funcƟon
__global__ void vectorAdd(int *a, int *b, int
*result, int n) {
 int Ɵd = threadIdx.x + blockIdx.x * blockDim.x;
 if (Ɵd < n) {
 result[Ɵd] = a[Ɵd] + b[Ɵd];
 }
}
int main() {
 int *a, *b, *c;
 int *a_dev, *b_dev, *c_dev;
 int n = 1 << 4;
 a = new int[n];
 b = new int[n];
 c = new int[n];
 int *d = new int[n];
 int size = n * sizeof(int);
 checkCudaErrors(cudaMalloc(&a_dev, size));
 checkCudaErrors(cudaMalloc(&b_dev, size));
 checkCudaErrors(cudaMalloc(&c_dev, size));
 // Array iniƟalizaƟon..You can use Randon
funcƟon to assign values
 for (int i = 0; i < n; i++) {
 a[i] = rand() % 1000;
 b[i] = rand() % 1000;
 d[i] = a[i] + b[i]; // calculaƟng serial addiƟon
 }
 cout << "Given array A is =>\n";
 for (int i = 0; i < n; i++) {
 cout << a[i] << ", ";
 }
 cout << "\n\n";
 cout << "Given array B is =>\n";
 for (int i = 0; i < n; i++) {
 cout << b[i] << ", ";
 }
 cout << "\n\n";
 cudaEvent_t start, end;
 checkCudaErrors(cudaEventCreate(&start));
 checkCudaErrors(cudaEventCreate(&end));
 checkCudaErrors(cudaMemcpy(a_dev, a, size,
cudaMemcpyHostToDevice));
 checkCudaErrors(cudaMemcpy(b_dev, b, size,
cudaMemcpyHostToDevice));
 int threads = 1024;
 int blocks = (n + threads - 1) / threads;
 checkCudaErrors(cudaEventRecord(start));
 // Parallel addiƟon program
 vectorAdd<<<blocks, threads>>>(a_dev, b_dev,
c_dev, n);
 checkCudaErrors(cudaEventRecord(end));
 checkCudaErrors(cudaEventSynchronize(end));
 float Ɵme = 0.0;
 checkCudaErrors(cudaEventElapsedTime(&Ɵme,
start, end));
 checkCudaErrors(cudaMemcpy(c, c_dev, size,
cudaMemcpyDeviceToHost));
 // Calculate the error term.
 cout << "CPU sum is =>\n";
 for (int i = 0; i < n; i++) {
 cout << d[i] << ", ";
 }
 cout << "\n\n";
 cout << "GPU sum is =>\n";
 for (int i = 0; i < n; i++) {
 cout << c[i] << ", ";
 }
 cout << "\n\n";
 int error = 0;
 for (int i = 0; i < n; i++) {
 error += d[i] - c[i];
 if (0 != (d[i] - c[i])) {
 cout << "Error at (" << i << ") => GPU: " <<
c[i] << ", CPU: " << d[i] << "\n";
 }
 }
 cout << "\nError : " << error;
 cout << "\nTime Elapsed: " << Ɵme;
 return 0;
}
