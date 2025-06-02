#include<iostream>
using namespace std;

int main(){
    int arr[7] = {12,19,100,1,5,8,11};
    int arrsize = 0;
    arrsize = sizeof(arr)/sizeof(arr[0]);
    cout << "Size of the arr is " << arrsize << endl;
    int max = arr[0];
    for(int i = 0; i < arrsize; i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    cout << "The max is : " << max << endl;

}