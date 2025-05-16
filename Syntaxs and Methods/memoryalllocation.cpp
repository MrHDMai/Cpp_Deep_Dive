#include<iostream>
#include<vector>
using namespace std;

int main(){

    int* a = new int (52);
    printf("print a address: %p\n",a);
    printf("print a value: %d\n",*a);
    int* b = new int {62};
    printf("print b address: %p\n",b);
    printf("print b value: %d\n",*b);
    cout <<"\n" << endl;

    const int size = 5;
    int *p = new int[size]; //when using new int, must leverage c++ delete function to delete the int or arry to avoid memory leak
    //consider that one the pointer variable is intialized call the pointer don't need to be dereferenced
    p[0] = 1;
    p[1] = 2;
    for(int i = 2; i < size; i++){
        p[i] = p[i - 1] + 1; // pointer i accessing the indices from 2 - starting from 2, p[i - 1] - for each element that follows, add one
    }
    for(int i = 0; i < size; i++){
        cout << p[i] <<endl;
    }
    delete[] p; // this method is for dynamic memory allocation

    printf("----------------------Vector implementation -----------------\n");

    vector<int> v = {1,2};
    for(int i = 0; i < 6; i++){
        v.push_back(v.back()+1);
    }
    for(int num : v){
        cout << num << endl;
    }



    return 0;
}