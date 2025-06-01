#include<iostream>
using namespace std;

int main(){
    int divend = 10;
    int divisor = 0;
    int result = 0;

    try{
        if(divisor == 0){
            throw "Divisor cannot be 0";
        } else {
            result = divend/divisor;
            cout << "Result: " << result << endl;
        }
    } catch(const char* error){
        cout << "Error" << error << endl;
    }
}