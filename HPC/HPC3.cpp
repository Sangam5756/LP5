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


