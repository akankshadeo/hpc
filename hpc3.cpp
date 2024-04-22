#include <iostream>
#include <chrono>
#include <cstdlib>
#include <omp.h>

using namespace std;

void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}


void printArray(int arr[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    int *arr = new int[n];
    srand(time(0));
    for (int i = 0; i < n; ++i)
    {
        arr[i] = rand() % 100;
    }

    cout << "Original array: ";
    printArray(arr, n);

    // Sequential Bubble Sort
    auto start = chrono::high_resolution_clock::now();
    bubbleSort(arr, n);
    auto end = chrono::high_resolution_clock::now();

    cout << "Sequential Bubble Sorted array: ";
    printArray(arr, n);

    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    // Parallel Bubble Sort
    start = chrono::high_resolution_clock::now();
    #pragma omp parallel
    {
        bubbleSort(arr, n);
    }
    end = chrono::high_resolution_clock::now();

    cout << "Parallel Bubble Sorted array: ";
    printArray(arr, n);

    auto parallelBubbleTime = chrono::duration_cast<chrono::microseconds>(end - start).count();


    // Performance measurement
    cout << "Sequential Bubble Sort Time: " << duration.count() << " microseconds" << endl;
    cout << "Parallel Bubble Sort Time: " << parallelBubbleTime << " microseconds" << endl;

}
