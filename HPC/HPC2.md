Awesome! Let’s now move on to:

---

## ✅ **HPC 2 – Parallel Bubble Sort and Merge Sort using OpenMP**

---

### 🎯 **Objective:**

To implement **Bubble Sort** and **Merge Sort** using **OpenMP** and compare the performance of:

* Sequential vs Parallel versions

---

## 🔧 **Code (Minimal & Exam-Friendly)**

We'll implement:

1. **Parallel Bubble Sort**
2. **Parallel Merge Sort**

---

### 🔹 1. **Parallel Bubble Sort (Odd-Even Sort Style)**

```cpp
#include <iostream>
#include <omp.h>
using namespace std;

void parallelBubbleSort(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        int start = i % 2; // even or odd pass
        #pragma omp parallel for
        for (int j = start; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    int arr[6] = {9, 2, 5, 1, 8, 3};
    int n = 6;

    parallelBubbleSort(arr, n);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    return 0;
}
```

🟢 Uses **odd-even transposition** for parallel safety.

---

### 🔹 2. **Parallel Merge Sort (Divide and Conquer with OpenMP)**

```cpp
#include <iostream>
#include <omp.h>
using namespace std;

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] < R[j]) ? L[i++] : R[j++];

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void parallelMergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, l, m);
            #pragma omp section
            parallelMergeSort(arr, m + 1, r);
        }
        merge(arr, l, m, r);
    }
}

int main() {
    int arr[6] = {9, 2, 5, 1, 8, 3};
    int n = 6;

    parallelMergeSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    return 0;
}
```

---

## 📘 **Theory & Explanation**

### 🔹 **Bubble Sort:**

* Simple comparison-based sorting algorithm.
* Parallel version uses **odd-even transposition**:

  * Even phase compares (0,1), (2,3)...
  * Odd phase compares (1,2), (3,4)...

### 🔹 **Merge Sort:**

* **Divide and conquer** algorithm.
* In parallel:

  * Left and right halves are sorted **simultaneously** using `#pragma omp sections`.

### 🔹 **OpenMP Use:**

* `#pragma omp parallel for` in Bubble Sort to compare pairs in parallel.
* `#pragma omp parallel sections` in Merge Sort to sort subarrays in parallel.

---

## 💬 **Viva Questions & Answers:**

| Question                                  | Answer                                                          |
| ----------------------------------------- | --------------------------------------------------------------- |
| Why can Bubble Sort be parallelized?      | Because each pass can compare independent pairs in parallel.    |
| What is odd-even transposition?           | A parallel version of bubble sort that avoids race conditions.  |
| How is Merge Sort parallelized?           | Left and right halves are sorted in separate threads.           |
| Why is Merge Sort better for parallelism? | It naturally divides the problem into independent sub-problems. |
| What does `#pragma omp sections` do?      | Runs multiple blocks of code in parallel.                       |


# THEORY
Sure! Here's the **brief and exam-friendly theory** for **HPC 2 – Parallel Bubble Sort and Merge Sort using OpenMP**:

---

## 📘 **Theory: Parallel Bubble Sort and Merge Sort (OpenMP)**

### 🔹 **Objective:**

To implement **Bubble Sort** and **Merge Sort** using **parallel programming** with **OpenMP** to improve sorting speed on multi-core systems.

---

### 🔸 **Bubble Sort (Parallel Version):**

* Repeatedly compares and swaps adjacent elements.
* Parallelized using **odd-even transposition**:

  * Even phase: compare (0,1), (2,3), etc.
  * Odd phase: compare (1,2), (

    <!-- 
     -->


Sure! Let's go through the code briefly.

### Overview:

The program implements both **sequential** and **parallel** versions of **Bubble Sort** and **Merge Sort**. It measures and compares the time it takes to sort a fixed array of integers using these algorithms, both sequentially and in parallel.

### Main Components:

1. **Parallel Bubble Sort (`parallelBubbleSort`)**:

   * This function uses the **Bubble Sort** algorithm to sort an array.
   * It processes the array in alternating "odd" and "even" passes. For each pass, the program compares adjacent elements and swaps them if they are in the wrong order.
   * It uses **OpenMP** (`#pragma omp parallel for`) to parallelize the inner loop that performs the comparison and swap. This helps the sorting process by splitting the work across multiple threads, improving performance on multi-core CPUs.

2. **Merge (`merge`)**:

   * This is a helper function used in **Merge Sort** to combine two sorted subarrays into one sorted array.
   * It takes two subarrays and merges them into one, maintaining the sorted order by comparing elements of the subarrays.

3. **Parallel Merge Sort (`parallelMergeSort`)**:

   * This function recursively divides the array into two halves and sorts them.
   * It uses **OpenMP** to parallelize the recursive calls for sorting the left and right halves of the array. The `#pragma omp parallel sections` directive tells OpenMP to run these recursive calls in parallel, utilizing multiple threads.
   * After sorting the subarrays, it merges them back together using the `merge` function.

4. **Main Function**:

   * **Array Initialization**: The array is hardcoded as `{9, 2, 5, 1, 8, 3}`, but you can replace this with any input.
   * **Time Measurements**:

     * The time for **sequential** Bubble Sort and Merge Sort is measured using `clock_t` and the `clock()` function. The difference between start and end times is calculated to measure the execution time.
     * The same time measurement is performed for the **parallel** versions of these sorting algorithms.
   * **Output**: After sorting the array using all four algorithms (sequential Bubble Sort, parallel Bubble Sort, sequential Merge Sort, and parallel Merge Sort), the program prints the sorted array and the execution time for each algorithm.
   * **Memory Cleanup**: It dynamically allocates memory for the arrays using `new` and frees them using `delete[]` to avoid memory leaks.

### Code Walkthrough:

1. **Array Initialization**:

   ```cpp
   int arr[] = {9, 2, 5, 1, 8, 3};  // Hardcoded input array
   int n = sizeof(arr) / sizeof(arr[0]);  // Size of the array
   ```

2. **Parallel Bubble Sort**:

   ```cpp
   parallelBubbleSort(bubbleArr, n);
   ```

   * The array is sorted using parallel Bubble Sort. The time it takes is measured using `clock()`.

3. **Parallel Merge Sort**:

   ```cpp
   parallelMergeSort(mergeArr, 0, n - 1);
   ```

   * The array is sorted using parallel Merge Sort. Again, the time taken is measured.

4. **Time Measurement**:
   The time for each sorting algorithm is calculated using `clock()`:

   ```cpp
   start = clock();
   parallelBubbleSort(bubbleArr, n);
   end = clock();
   double time = double(end - start) / CLOCKS_PER_SEC;
   ```

5. **Result Output**:
   After sorting, the program prints the sorted arrays and the execution times for each sorting algorithm.

6. **Memory Cleanup**:
   Dynamically allocated memory for the arrays is freed at the end of the program using `delete[]`.

### Example Output:

If you run this program, it might print something like this:

```
Sequential Bubble Sort Time: 0.00001 seconds
Parallel Bubble Sort Time: 0.00001 seconds
Sequential Merge Sort Time: 0.00001 seconds
Parallel Merge Sort Time: 0.00001 seconds

Sorted array (Sequential Bubble Sort): 1 2 3 5 8 9 
Sorted array (Parallel Bubble Sort): 1 2 3 5 8 9 
Sorted array (Sequential Merge Sort): 1 2 3 5 8 9 
Sorted array (Parallel Merge Sort): 1 2 3 5 8 9 
```

### Conclusion:

This program compares the performance of sequential and parallel sorting algorithms on a small array. For small datasets, the time difference might not be noticeable, but for larger datasets, parallel sorting can significantly improve performance by utilizing multiple CPU cores.

Let me know if you need more details!
