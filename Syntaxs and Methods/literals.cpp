/*
Literals or string literals within C++,  are constant value that the programmer have integrated into their code. The compiler
to automaatically know the data via the syntax inputted from the programmer. 
*/

#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;
/*02
Example on constant expression
The introduction of constexpr allow the declared variable or function to be accessed at compiled time - mitigate run-time
overhead. The constexpr is not imbededd into the binary of the software. When conditons are checked at compiled time,
this optimzed by reducing run-time compilation. Consider that constexpr is best used for array size, mathematical constants,
template metaprogramming, and optimized precomputation.
*/
constexpr int training(int i){
    //consider that we are using this ternary function as a recursion method. If the input is 5,
    //it will call the initial input and decrement until input is 0 which suffices the condition.
    //in this case, the result will be 15 if 5 is the input.
    return(i==0)?0 : training(i-1) + i;
}


int main(){
    //01
    int num = +1;
    cout << "num = " << num << endl;
    int num1 = -1;
    cout << "num1 = " << num1 << endl;
    double micro = 1e-6; //represents 1*10^6
    cout << "micro:  " << micro << endl;
    double unit = 1.;
    cout << "unit: " << unit << endl;
    int myhex = 0x100; //256 ini decimal
    cout << "%d" << myhex << endl;
    
    //will now be employing iomanip to do number conversion
    int n = 105;
    cout << "Octal: " << oct << n << endl;
    cout << "Hex: " <<hex << n << endl;
    cout << "Dec: " <<dec << n << endl;

    //const declaration
    const double pi = 3.14; //this value will not be reinitialized to another value
    //restatement 3.14556 will cause a compilation error
    double radius = 5.0;
    double circumference = 2 * pi * radius;
    cout << "Radius: "<< radius << endl;

    //create an array
    const int arr[] = {1,2,3,45};
    //access the elements within the array
    int elem2 = arr[2];
    cout << elem2 <<  endl;

    int inpt; 
    cout <<"intput a number";
    cin >> inpt;
    int result = training(inpt);
    cout << "result: " <<result << endl;

    return 0;


}