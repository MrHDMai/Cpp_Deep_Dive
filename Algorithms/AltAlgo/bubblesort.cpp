#include<iostream>
#include<vector>

using namespace std;

void bubble(int arr[]){
    int n = 5;
    arr[n];
    for(int i = 0; i < n; i++){
        int* key = &arr[i];
        for(int j = 0; j < n - 1; j++){
            if(arr[j + 1] > arr[j]){
                swap(arr[j + 1],arr[j]);
            }
        }
    }
}

int main(){
    int arr[5] = {4,3,2,1,0};
    bubble(arr);
    for(auto& num : arr){
        cout << num << endl;
    }
}