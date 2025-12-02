#include<iostream>
#include<climits>

using namespace std;

int kandane(int* arr, int n){
    int MaxNum = INT_MIN;
    int Maxthus = 0;
    int* ptr = arr;
    for(int i = 0; i < n; ++i,++ptr){
        maxthus+=*ptr;
        if(MaxNum < maxthus)
            Maxnum = maxthus;
        if(maxthus <= 0)
            maxthus =  0;
    }
    return MaxNum; 
}

int main() {
    int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int size = sizeof(arr) / sizeof(arr[0]);

    int maxSubarraySum = kadane(arr, size);

    std::cout << "Maximum Subarray Sum: " << maxSubarraySum << std::endl;

    return 0;
}