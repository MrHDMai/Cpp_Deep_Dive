#include <iostream>

using namespace std;

// Binary search to find the index of the smallest number >= key
int lower_bound(int* arr, int size, int key) {
    int low = 0, high = size;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] >= key)
            high = mid;
        else
            low = mid + 1;
    }
    return low;
}

int LIS(int* arr, int n) {
    int* tail = new int[n]; // tail[i] = smallest ending of LIS of length i+1
    int length = 0;

    for (int i = 0; i < n; ++i) {
        int idx = lower_bound(tail, length, arr[i]);
        tail[idx] = arr[i];
        if (idx == length)
            ++length;
    }

    delete[] tail;
    return length;
}

int main() {
    int arr[] = {10, 9, 2, 5, 3, 7, 101, 18};
    int n = sizeof(arr) / sizeof(arr[0]);

    int length = LIS(arr, n);
    cout << "Length of LIS: " << length << endl;

    return 0;
}
