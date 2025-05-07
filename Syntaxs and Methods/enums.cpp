/*
The goal of an enum is to create a set of defined properties that can be calls within the main functions.
The main function can output the indecies of the object by calling the name name of that property and assinging it an alias.
*/
#include<iostream>
using namespace std;

enum shapes { //declaring the list of shapes and specifying the type of shape
    square,
    circle, 
    triangle,
    rectangle,
    pentagon,
    heart
};

enum executionMethod{
    codeExpploit = 1,
    acctHack = 2,
    passwordCrack = 3

};

int main(){
    shapes callindex = square; // calling the enum object and assigning ana alias to call a specifsic location of an object. 
    cout << "Index of shape:" << callindex << endl;
    executionMethod callAttck = acctHack;
    cout << acctHack << endl;

}