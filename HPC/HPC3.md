## ✅ **Practical 1: HPC 3 – Parallel Min, Max, Sum, and Average using OpenMP**

* Initializes an array of integers.
* Uses **OpenMP reduction** to find:

  * Minimum
  * Maximum
  * Sum
  * Average

---

### 🧠 **Code:**

```cpp
#include <iostream>
#include <omp.h>
#include <limits.h>

using namespace std;

int main() {
    const int n = 1000;
    int arr[n];

    // Initialize array with values
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;  // Random values between 0-999
    }

    int min_val = INT_MAX;
    int max_val = INT_MIN;
    long long sum = 0;

    #pragma omp parallel for reduction(min:min_val) reduction(max:max_val) reduction(+:sum)
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_val)
            min_val = arr[i];
        if (arr[i] > max_val)
            max_val = arr[i];
        sum += arr[i];
    }

    double average = static_cast<double>(sum) / n;

    cout << "Minimum value: " << min_val << endl;
    cout << "Maximum value: " << max_val << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;

    return 0;
}
```

---

### 🛠️ **To Compile and Run:**

Make sure you have OpenMP support.

```bash
g++ hpc3_parallel_operations.cpp -fopenmp -o hpc3
./hpc3
```

---

### ✅ Output Sample:

```
Minimum value: 1
Maximum value: 998
Sum: 500123
Average: 500.123
```

---

Let me know once you're done running this, and I’ll give you **DL1: Boston Housing Price Prediction** next. Ready?


---

## 📘 **Theory & Explanation (HPC 3)**

### 🔷 **Objective:**

To implement a parallel program using **OpenMP** to find:

* Minimum
* Maximum
* Sum
* Average
  from a given array of numbers.

---

### 🧠 **What is OpenMP?**

OpenMP (Open Multi-Processing) is a tool in C/C++ that allows you to run parts of your code **in parallel** using multiple CPU cores. This helps your program **run faster** by doing multiple things at the same time.

* It works by using **threads**.
* You control it using special **#pragma directives**.

---

### 🔧 **What is Reduction?**

**Reduction** is a technique used in parallel programming when:

* Multiple threads are **updating a single variable**, like `sum`, `min`, or `max`.

In OpenMP, `reduction` ensures:

* Each thread works on its own copy.
* At the end, the values are combined correctly.

---

### 🗂️ **Code Components Explained:**

```cpp
#pragma omp parallel for reduction(min:min_val) reduction(max:max_val) reduction(+:sum)
```

This line tells the compiler:

* Use **parallel threads** to loop over the array.
* Apply **reduction** on:

  * `min_val` → get the minimum across all threads.
  * `max_val` → get the maximum.
  * `sum` → calculate total sum.

---

### 📉 **Why Use This Approach?**

* Sequential loop = only 1 core = slow on big data
* Parallel loop = multiple cores = faster
* Using reduction ensures correctness while being fast

---

### 📌 **Final Result:**

You get:

* `min_val`: Smallest number in the array.
* `max_val`: Largest number in the array.
* `sum`: Total of all values.
* `average`: Mean value (sum / count).

---

### ✅ **Use Case in Real Life:**

* Finding analytics from large datasets like sensor readings, sales records, etc.
* Example: “What was the highest temperature recorded today across 1 million sensors?”

---

### 💬 Viva Questions You Might Get:

| Question                          | Simple Answer                                                                                 |
| --------------------------------- | --------------------------------------------------------------------------------------------- |
| What is OpenMP?                   | OpenMP is a parallel programming tool in C/C++ that lets us use multiple cores using threads. |
| What is reduction in OpenMP?      | Reduction combines thread results into a single value (like sum or max).                      |
| Why use parallel programming?     | To make programs faster by using all available CPU cores.                                     |
| What is the use of `#pragma omp`? | It tells the compiler to run the loop in parallel using OpenMP.                               |

---

# THEORY
Sure! Let's break down and compare what each code does, why it does it, and what problems they are solving, from a **higher-level perspective**:

### **Code 1: Sequential Operations**

#### **What it does:**

* **Input**: Takes the size of an array `n` from the user.
* **Array Initialization**: Creates an array of size `n` and fills it with random integers between 0 and 99.
* **Operations**:

  * **Finds the minimum value** in the array.
  * **Finds the maximum value** in the array.
  * **Calculates the sum and average** of all array elements.
* **Output**: It displays the array elements, the minimum and maximum values, and the sum and average of the array.

#### **Why it does it:**

* This code demonstrates **basic array operations** such as finding the minimum, maximum, and calculating the sum and average. These operations are useful in many applications (e.g., finding the range of values, summarizing data, or checking data consistency).

#### **Other ways to achieve it:**

* The operations are straightforward and cannot be done in significantly different ways unless using different data structures or algorithms. For example, using a more specialized data structure like a heap or balanced binary search tree might offer efficiency in finding min/max values, but that’s not necessary for this simple task.

#### **Problem it solves:**

* **Problem**: You have an array of numbers and you want to calculate the minimum, maximum, sum, and average of the array.
* **Solution**: This code does this sequentially, making it simple and easy to understand, though not the most efficient for very large datasets. It helps you quickly extract basic statistics from an array.

---

### **Code 2: Parallel Operations with OpenMP**

#### **What it does:**

* **Input**: Initializes a fixed-size array (`n = 1000`) filled with random integers between 0 and 999.
* **Operations**:

  * **Parallelized Loop**: Uses **OpenMP** (`#pragma omp parallel for`) to perform the operations of finding the **minimum**, **maximum**, and **sum** of array elements **in parallel** across multiple threads.
  * **Reduction**: Uses OpenMP's **reduction** clause to safely update shared variables (`min_val`, `max_val`, `sum`) in parallel.
  * **Calculates the average** by dividing the total sum by the number of elements.
* **Output**: Displays the minimum value, maximum value, sum, and average.

#### **Why it does it:**

* This code leverages **parallel processing** to make calculations faster, especially for large arrays. Parallel programming can split tasks across multiple threads, making use of multiple CPU cores. In this case, it speeds up operations like finding the min/max values and summing the array elements.

#### **Other ways to achieve it:**

* Without OpenMP, we could either:

  * Use **manual multithreading** in C++ (with `std::thread`), though OpenMP is much easier to implement for simple parallelization.
  * Split the array into chunks and process each chunk sequentially, which is a form of **divide and conquer**, but OpenMP handles the splitting and combining of results more efficiently and is less error-prone.

#### **Problem it solves:**

* **Problem**: When working with very large arrays, sequentially processing the array becomes slow. Calculating statistics like the minimum, maximum, and sum can take a significant amount of time if the array size is large.
* **Solution**: This code uses **parallelism** to split the work across multiple CPU cores, greatly improving the time efficiency when handling large datasets. This is particularly useful when processing big data in fields like analytics, image processing, or scientific computing.

---

### **Key Differences Between the Codes**

1. **Parallelism vs Sequential Execution**:

   * **Code 1** processes the array **sequentially**, meaning that each operation (min, max, sum) is done one after another. It’s simple but might take a long time for large datasets.
   * **Code 2** uses **OpenMP** to process the array in **parallel**, distributing the work across multiple threads. This significantly reduces the computation time, especially for large arrays. It’s useful for large datasets where speed is a concern.

2. **Performance**:

   * **Code 1**: Performs fine for small arrays but can be slow for large ones.
   * **Code 2**: Speeds up operations using parallel processing, making it more efficient for large datasets, as multiple threads work concurrently.

3. **Complexity**:

   * **Code 1** is **simpler**, easier to understand, and doesn’t require any parallel programming knowledge.
   * **Code 2** involves a little more complexity due to **parallelism** and the use of OpenMP. However, it can handle **larger datasets** much more efficiently.

4. **Scalability**:

   * **Code 1** becomes slower as the size of the dataset increases, making it unsuitable for very large arrays.
   * **Code 2** can scale much better with larger datasets due to parallel processing. As the array size grows, the performance improvement from parallelism becomes more evident.

---

### **Why Use Parallelism (Code 2) Over Sequential Processing (Code 1)?**

1. **Performance in Large Datasets**:

   * **Code 2** can process data much faster when dealing with large datasets. The key reason for this is parallelism: multiple CPU cores can handle different parts of the data simultaneously, making the processing faster than doing it one step at a time.
2. **Real-World Scenarios**:

   * In many real-world applications, such as data analytics, machine learning, or image processing, datasets can easily exceed millions of records. **Parallel processing** is essential to reduce computation time when handling these large amounts of data.
3. **Efficiency**:

   * **Code 2** is more **efficient** for modern multi-core CPUs, taking advantage of all the available processing power. On the other hand, **Code 1** is limited by a single thread and may cause delays when working with large datasets.
4. **Hardware Utilization**:

   * **Code 2** makes use of the system's hardware resources more effectively, utilizing multiple processor cores. This is a critical advantage for applications running on powerful machines with multi-core processors.

---

### **When to Use Each Approach?**

1. **Use Code 1 (Sequential) when**:

   * Working with **small arrays** or datasets where performance isn’t a major concern.
   * Simplicity and readability are more important than execution speed.
   * You are just learning about basic array operations and algorithms.

2. **Use Code 2 (Parallel with OpenMP) when**:

   * You are working with **large arrays** or datasets where processing speed is important.
   * You are working in an environment where the data volume can significantly impact performance (e.g., big data applications, scientific computations).
   * You need to leverage **multi-core processors** to improve performance.

---

### **Summary of Problems Solved:**

* **Code 1**: Solves the problem of calculating basic statistics from a small array, which can be done sequentially and is suitable for simple, small-scale tasks.
* **Code 2**: Solves the problem of efficiently calculating statistics from large datasets by using parallelism. It improves performance significantly by utilizing multiple CPU cores for faster execution.
