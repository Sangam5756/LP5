#include <iostream>
#include <ctime>
#include <cstdlib>
#include <omp.h>
using namespace std;

// Parallel Bubble Sort function
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

// Merge function for Merge Sort
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

// Parallel Merge Sort function
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

// Function to print the array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int arr[] = {9, 2, 5, 1, 8, 3};  // Hardcoded input array
    int n = sizeof(arr) / sizeof(arr[0]);

    // Sequential Bubble Sort
    int* bubbleArr = new int[n];
    copy(arr, arr + n, bubbleArr);  // Copy original array
    clock_t start = clock();
    bubbleSort(bubbleArr, n);
    clock_t end = clock();
    double sequentialBubbleTime = double(end - start) / CLOCKS_PER_SEC;

    // Parallel Bubble Sort
    int* bubbleArrParallel = new int[n];
    copy(arr, arr + n, bubbleArrParallel);  // Copy original array
    start = clock();
    parallelBubbleSort(bubbleArrParallel, n);
    end = clock();
    double parallelBubbleTime = double(end - start) / CLOCKS_PER_SEC;

    // Sequential Merge Sort
    int* mergeArr = new int[n];
    copy(arr, arr + n, mergeArr);  // Copy original array
    start = clock();
    mergeSort(mergeArr, 0, n - 1);
    end = clock();
    double sequentialMergeTime = double(end - start) / CLOCKS_PER_SEC;

    // Parallel Merge Sort
    int* mergeArrParallel = new int[n];
    copy(arr, arr + n, mergeArrParallel);  // Copy original array
    start = clock();
    parallelMergeSort(mergeArrParallel, 0, n - 1);
    end = clock();
    double parallelMergeTime = double(end - start) / CLOCKS_PER_SEC;

    // Output times for each sorting method
    cout << "Sequential Bubble Sort Time: " << sequentialBubbleTime << " seconds" << endl;
    cout << "Parallel Bubble Sort Time: " << parallelBubbleTime << " seconds" << endl;
    cout << "Sequential Merge Sort Time: " << sequentialMergeTime << " seconds" << endl;
    cout << "Parallel Merge Sort Time: " << parallelMergeTime << " seconds" << endl;

    // Output sorted arrays
    cout << "Sorted array (Sequential Bubble Sort): ";
    printArray(bubbleArr, n);

    cout << "Sorted array (Parallel Bubble Sort): ";
    printArray(bubbleArrParallel, n);

    cout << "Sorted array (Sequential Merge Sort): ";
    printArray(mergeArr, n);

    cout << "Sorted array (Parallel Merge Sort): ";
    printArray(mergeArrParallel, n);

    // Clean up dynamically allocated memory
    delete[] bubbleArr;
    delete[] bubbleArrParallel;
    delete[] mergeArr;
    delete[] mergeArrParallel;

    return 0;
}
