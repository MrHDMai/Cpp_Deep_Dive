/* The goal of a pointer is to store th address of a declared variable, given this implementation, the pointer
doesn't make a copy of the data itself, but rather points or references the data rather than making a direct copies. Furthermore,
pointers can be used to dynamically allocate memory, and in some instances - pointers can also be reassigned to another
address.
*/

#include<iostream>

using namespace std;

int main(){
    int v = 20; 
    int* ptr = &v; //& denotes the retrieval of the memeory address of the variable
                  //* denotes the dereference of the address and access the value stored within the variable  
    cout << &v << endl; // printing the address of the variable
    cout <<  ptr << endl; // printing the address of the variable
    cout << *ptr << endl; // using the dereference in order to print the value store within the memory location

    cout << "------------------------------" << endl;
    //Lets use pointers to reference an arry;
    int numarr [] = {1,2,4};
    int* ptrarr = numarr; //creating a pointer that refernces the memeory address of the numarr arr.
    cout << ptrarr << endl; //calling the memeory address of the arr - this will only print out the memory address of the array.
    cout << *ptrarr << endl; //printing out the accessed value of memory of the arr by using the dereference - this method will print out the first value.
    ptrarr++; //post increment the value by one - access the second elemnt of the array from memory;
    cout << *ptrarr << endl; // print out the second values of the access memory from the arr. 
    ptrarr++; // post increment to find the third value;
    cout << *ptrarr << endl; // print the third value
}