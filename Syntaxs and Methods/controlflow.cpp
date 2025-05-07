/* Conditoinal statement such as if, if-else, switch and tenary (?) will allow programmer to interurpt the sequential order to
program execution.
*/

#include<iostream>
#include<string>

using namespace std;

int main(){
    int num;
    cout << "Enter a number: " << endl;
    cin >> num;
    bool doSwitch = false;
    if(num >= 10){
        doSwitch = true;
        cout << "Valid";
    } else {
        doSwitch = false;
        cout <<"Lower than 10 - invalid" << endl; 
    }

    //using tenary operator
    int a = 10, b=20;
    int max = (a > b) ? a : b;
    cout << "The maximum value is: " << max << endl;

    //using the switch case statemet
    int day; 
    cout << "Enter the day of the month" << endl;
    cin >> day;
    switch(day){
        case 1: cout << "Monday";
        break;
        case 2:cout << "Tuesday";
        break;
        //so forth and so forth
        default: 
        cout << "Enter 1 - 7";
    }
    return 0;
}