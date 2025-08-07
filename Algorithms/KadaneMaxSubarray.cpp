//usage: max profit in quant engineering, segment windws within AI, system usage spike

#include<iostream>
#include<climits>

using namespace std;

int kadane(int* arr, int n){
    int maxthus = INT_MIN;
    int maxthushere = 0;

    int* ptr = arr;
    for(int i = 0; i < n; ++i, ++ptr){
        maxthushere += *ptr;
        if(maxthus < maxthushere)
            maxthus = maxthushere;

        if(maxthushere < 0)
            maxthushere = 0;
    }
    return maxthus;
}

int main(){
    int arr[] = {-2,-3,4,-1,-2,1,5,-3};
    int size = sizeof(arr)/sizeof(arr[0]);
    int maxsub = kadane(arr,size); 

    cout <<maxsub << endl;
}
