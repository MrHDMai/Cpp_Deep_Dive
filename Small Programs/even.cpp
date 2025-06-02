#include<iostream>
using namespace std;

int main(){
    int arr [] = {12,8,15,6,2,9,1};
    int arrsize = 0;
    arrsize = sizeof(arr)/sizeof(arr[0]); 
    //consider that the number of element within an arr is 4 byte the total is 4*n elemnt, 
    //divde that by the first place holder which is 4 will return the total nnumber of element
    cout << "The length of an the arr is: " << arrsize << endl;
    for(int i = 0; i < arrsize; i++){
        if(arr[i]%2==0){
            cout << arr[i] << " Number is even." << endl;
        }
    }
    long product = 1;
    int sum = 0;
    for(int i = 0; i < arrsize; i++){
        product = product * arr[i];
        int sum = sum + arr[i];
        cout << "The sum is \t" << sum << endl;
        cout << "The product is \t: " << product << endl;
    }

}