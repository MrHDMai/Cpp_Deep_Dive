/*
Consider that in c++, there is a pre-increment and a post increment. Pre incremenet means value will be increment first and then result the result.
On the other hand, post-increment will be perfrom once the operation of the value has completed.
*/

#include<iostream>

using namespace std;

int main(){
    int n = 5;
    int y = ++n; //value will be incremented to 6 and then assigned to y
    cout << "The result of the pre-increment: " << y << endl;

    int v = 5;
    int x = v++; //value will be reassigned to x first which will be 5, and then incremented.
    cout << "The result of post increment: "<< x << endl;
    cout << "The value of v is: " << v << endl; //in order to see the incremented value before it is assigned, print the value being incremented
    //increments in the operations of an array;
    int numarr[] = {1,2,3,4};
    int* arrpt = numarr;
    int* secpt = numarr;
    ++secpt;
    arrpt++;
    cout << "The post increment of the pointer to the arr is: " << *arrpt << endl; //default ptr will print the first value, since we are post incrementing, it will print the next value.
    cout << "The preinrement of the arr is: " << *secpt << endl;
    --secpt;
    cout << "The pre-decrement of the arr is: " << *secpt << endl;
    arrpt--;
    cout << "The post-decrement of the arr is: " << *arrpt << endl;
    //programmer can also specify a specific index location of the arr and the increment/decrement to their desire;
    int* arrloc = numarr + 2;
    arrloc++;
    cout << "Post-increment of desired position: " << *arrloc << endl;
    ++arrloc;
    cout << "Pre-increment of desired position: " << *arrloc << endl;
    arrloc--;
    cout << "Post-decrement of desired position: " << *arrloc << endl;
    --arrloc;
    cout << "Pre-decrement of desired position: " << *arrloc << endl;    
}