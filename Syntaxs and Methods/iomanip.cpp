/* Consider that the objective of this library is leveraged to do base conversion of a number. 
*/

#include<iostream>
#include<iomanip>

using namespace std;

int main(){
    int number = 30;
    //coverting the number into hex; 
    cout << hex <<"This is the number in hexidecimal: " << number <<"\n"<< endl;
    //converting the number in octaldecimal
    cout << oct << "This is the numbber in its octaldecimal format:" << number << endl;
    return 0;
}