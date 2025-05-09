Here's a basic CUDA program for the two tasks you mentioned: **Addition of Two Large Vectors** and **Matrix Multiplication using CUDA**.

### 1. **Addition of Two Large Vectors**

This program adds two large vectors element-wise using CUDA.

```cpp
#include <iostream>
#include <cuda_runtime.h>

#define N 1024  // Size of the vectors

// CUDA kernel for vector addition
__global__ void vectorAdd(int *A, int *B, int *C) {
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    if (index < N) {
        C[index] = A[index] + B[index];
    }
}

int main() {
    int *A, *B, *C;           // Host pointers
    int *d_A, *d_B, *d_C;      // Device pointers

    size_t size = N * sizeof(int);

    // Allocate memory on the host
    A = (int*)malloc(size);
    B = (int*)malloc(size);
    C = (int*)malloc(size);

    // Allocate memory on the device
    cudaMalloc((void**)&d_A, size);
    cudaMalloc((void**)&d_B, size);
    cudaMalloc((void**)&d_C, size);

    // Initialize vectors A and B with some values
    for (int i = 0; i < N; i++) {
        A[i] = i;
        B[i] = i * 2;
    }

    // Copy data from host to device
    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);

    // Define number of threads per block and number of blocks per grid
    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;

    // Launch kernel
    vectorAdd<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C);

    // Copy result from device to host
    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);

    // Print the result (optional, for small N)
    for (int i = 0; i < 10; i++) {
        std::cout << C[i] << " ";  // Print first 10 elements
    }
    std::cout << std::endl;

    // Free memory
    free(A);
    free(B);
    free(C);
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}
```

### 2. **Matrix Multiplication Using CUDA**

This program multiplies two matrices using CUDA.

```cpp
#include <iostream>
#include <cuda_runtime.h>

#define N 16  // Size of the matrix (N x N)

// CUDA kernel for matrix multiplication
__global__ void matrixMul(int *A, int *B, int *C, int width) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < width && col < width) {
        int value = 0;
        for (int k = 0; k < width; k++) {
            value += A[row * width + k] * B[k * width + col];
        }
        C[row * width + col] = value;
    }
}

int main() {
    int *A, *B, *C;           // Host pointers
    int *d_A, *d_B, *d_C;      // Device pointers

    size_t size = N * N * sizeof(int);

    // Allocate memory on the host
    A = (int*)malloc(size);
    B = (int*)malloc(size);
    C = (int*)malloc(size);

    // Allocate memory on the device
    cudaMalloc((void**)&d_A, size);
    cudaMalloc((void**)&d_B, size);
    cudaMalloc((void**)&d_C, size);

    // Initialize matrices A and B with some values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = i + j;
            B[i * N + j] = i - j;
        }
    }

    // Copy data from host to device
    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);

    // Define number of threads per block and number of blocks per grid
    dim3 threadsPerBlock(16, 16);
    dim3 blocksPerGrid((N + threadsPerBlock.x - 1) / threadsPerBlock.x, 
                        (N + threadsPerBlock.y - 1) / threadsPerBlock.y);

    // Launch kernel
    matrixMul<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);

    // Copy result from device to host
    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);

    // Print the result (optional, for small N)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << C[i * N + j] << " ";
        }
        std::cout << std::endl;
    }

    // Free memory
    free(A);
    free(B);
    free(C);
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}
```

### Explanation:

1. **Vector Addition**:

   * Each thread computes one element of the resulting vector `C` by adding the corresponding elements from vectors `A` and `B`.
   * We define the grid and block sizes, where each thread handles one vector element.

2. **Matrix Multiplication**:

   * Each thread computes one element of the resulting matrix `C` by performing a dot product of the corresponding row of matrix `A` and column of matrix `B`.
   * We use a 2D block and grid structure to efficiently handle matrix elements.

### How to Run:

1. Install CUDA Toolkit on your system if you don't have it already.
2. Compile using `nvcc`:

   ```bash
   nvcc vector_add.cu -o vector_add
   nvcc matrix_mul.cu -o matrix_mul
   ```
3. Run the program:

   ```bash
   ./vector_add
   ./matrix_mul
   ```


### 1. **Vector Addition Using CUDA**

**Goal**: Add two large vectors element-wise.

* **Kernel**: The CUDA kernel `vectorAdd` is used to perform the addition of the two vectors (`A` and `B`) element by element.

  * Each thread handles a single element of the resulting vector `C`, calculating `C[i] = A[i] + B[i]`.

* **CUDA Blocks and Threads**:

  * We define `threadsPerBlock = 256`, meaning each block will have 256 threads.
  * The number of blocks is determined by dividing the total number of elements (`N`) by the number of threads per block.

* **Memory Transfer**:

  * We allocate memory for the vectors `A`, `B`, and `C` on both the host (CPU) and device (GPU).
  * After initializing the vectors, we copy the data from the host to the device, perform the computation on the device, and then copy the result back to the host.

* **Execution**: The kernel is launched with `vectorAdd<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C)`, where `blocksPerGrid` is the calculated number of blocks and `threadsPerBlock` is 256.

### 2. **Matrix Multiplication Using CUDA**

**Goal**: Perform matrix multiplication of two matrices `A` and `B` to produce matrix `C`.

* **Kernel**: The CUDA kernel `matrixMul` computes one element of the resulting matrix `C` by performing the dot product of the row from matrix `A` and the column from matrix `B`.

  * Each thread calculates a single element of `C`: `C[i, j] = sum(A[i, k] * B[k, j] for all k)`.

* **CUDA Blocks and Threads**:

  * The kernel uses a 2D grid of blocks. Each block is of size `16 x 16`, meaning there are 16 threads along both the x and y axes within each block.
  * The number of blocks is calculated based on the matrix size `N` and the number of threads per block.

* **Memory Transfer**:

  * Like the vector addition program, memory is allocated on both the host and the device. The matrices are copied to the device before the computation begins, and the result is copied back to the host after computation.

* **Execution**: The kernel is launched with `matrixMul<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N)`, where `blocksPerGrid` is the grid size calculated based on the matrix dimensions.

### Summary of Key Concepts:

* **CUDA Kernel**: A function executed by each thread in parallel on the GPU.
* **Grid and Blocks**: Threads are organized into blocks, and blocks are organized into a grid.
* **Memory Management**: Data is transferred between host (CPU) memory and device (GPU) memory.
* **Parallelism**: Each thread runs in parallel and handles part of the computation (like one element of the vector or matrix).
