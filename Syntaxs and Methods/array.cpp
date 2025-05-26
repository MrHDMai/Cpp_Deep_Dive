/*Array are data containers that stored variables within a memory block, indices always start at one
*/
#include<iostream>
using namespace std;

int main() {
    int arr[] = {60, 50, 75, 90};  // Array initialized with 4 elements

    // Loop 1: Print original array
    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
        cout << arr[i] << endl;
    }

    // Modify existing elements (no "int" keyword)
    arr[3] = 10;  // Change 4th element (index 3) from 90 to 10
    arr[0] = 1;    // Change 1st element (index 0) from 60 to 1

    // Loop 2: Print modified array
    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
        cout << arr[i] << endl;
    }
    cout << endl;
    cout << "---- another way of printint it out is using an auto temp declare varible to iterate over the values--------" << endl;
    for(auto num : arr){
        cout << num << endl;
    }
    cout << endl;
    cout << "Array pointers: " << endl;
    int *ptr = arr;
    ptr++;
    cout << *ptr << endl;

    /* Using an array length to initialize an array*/
    cout << "Using array index" << endl;
    int arrlength = 5;
    int *pr = new int[arrlength]{1,2,3,4,5};
    for(int i = 0; i < arrlength; i++){
        cout << "values:"<<*pr << "\t"<<endl;
        cout << "address:"<<&pr << endl;
        pr++;
    }
    pr-=arrlength;
    delete[] pr;
    return 0;
}