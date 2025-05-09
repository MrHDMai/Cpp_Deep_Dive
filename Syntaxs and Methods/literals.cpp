/*
Literals or string literals within C++,  are constant value that the programmer have integrated into their code. The compiler
to automaatically know the data via the syntax inputted from the programmer. 
*/

#include<iostream>
#include<iomanip>
using namespace std;

int main(){
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
    return 0;


}