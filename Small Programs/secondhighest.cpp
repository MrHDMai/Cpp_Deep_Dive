#include<iostream>
using namespace std;

int main(){
    int arr[] = {12,8,15,6,2,9,1};
    int arrsize = 0;
    arrsize = sizeof(arr)/sizeof(arr[0]);

    cout << "The length of the arr is: " << arrsize <<endl;
//kin to that of bubble sort, this sort will sort the array in decending order instead of acsending order
//consider that looping it once through the i iteration will not allow the array to be fully sorted
//pass the iternation through j will "bubble" the posiiton of the value and allow for a thorough sort
    for(int j = 0; j < arrsize; j++){
        for(int i = 0; i < arrsize; i++){
            if(arr[i] < arr[i + 1]){
                int temp = 0;
                temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
    }
    cout << "the second highest array is: " << arr[1] << endl;
    return 0;

}