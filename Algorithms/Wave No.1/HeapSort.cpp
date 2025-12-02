#include<iostream>
using namespace std;

inline void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i){
    int large = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n && arr[left] > arr[large])large = left;
    if(right < n && arr[right] > arr[large]) large = right;

    if(large!= i){
        swap(&arr[i],&arr[large]);
        heapify(arr,n,large);
    }
}

void heapsort(int arr[], int n){
    for(int i = n/2 - 1; i >=0; i--)
        heapify(arr,n,i);
    
    for(int i = n-1; i >= 0; i--){
        swap(&arr[0], &arr[i]);
        heapify(arr,i,0);
    }
}

int main() {
    int arr[] = {4, 10, 3, 5, 1};
    int n = sizeof(arr)/sizeof(arr[0]);

    heapsort(arr, n);

    for (int i = 0; i < n; ++i) cout << arr[i] << " ";
    return 0;
}