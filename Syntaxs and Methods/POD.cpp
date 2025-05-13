/* POD - Structs and Unions
POD stands for Plan Old Data. This is the most simplied structure of data that can be denoted in terms of structs
These PODS are consists of functions and class. Such consists of the "."operator to  access the data type of specificly
declared variable in an effort of assign it for a use case.Another example are unions, unions starts with the union key word
and the outline is just like structs. However, these declared variables are declared using the same memeory address, be careful
when using them, if declaring the variable one afer the other, there will be corruption. If declared to run within the same line,
the value will also be corrupted since the share memeory is being intialized and overwritten.
*/

/*Structs methods

*/

#include<iostream>
//creating struct and access the defined value to reassign attributes.
using namespace std;
struct car{
    char make[256];
    int year;
    int wheels;
    bool operatable;
};
//Unions implementation
union variant{ //consider that data within this union shares one memory address
    char mystring[10];
    int myint;
    double mydouble;
};
/* Implementing */
struct addnum{ //declare the struciton
    void add(){ //create function of implementation
        num++;
    }
    int num; // declare the variable in which it will be assigned within the main function
};

int main(){
    //drive quote 
    car mycar;
    mycar.year = 2001;
    mycar.operatable = true;
    mycar.wheels = 4;
    printf("My car's year make is: %d\n", mycar.year);
    printf("Is my car operable? %s\n", mycar.operatable? "True":"False");
    printf("The total of wheels on the car is: %d\n", mycar.wheels);
    //
    variant v;
    v.myint = 10;
    //printf ("My integer is: %d\n and my double integer is: %f\n", v.myint, v.mydouble); // since both data are share, only one will print correctly. 
    printf ("My integer is: %d\n", v.myint);
    v.mydouble = 99.99; // declare the double here to not corrupt the byte by redeclaring what is already 10 from the start.
    printf ("My double integer is: %f\n", v.mydouble);

    //implementation of struct method function call
    addnum addition;
    addition.num = 10;
    printf("The number assigned to num is: %d\n",addition.num);
    addition.add();
    printf("Post operation of the add function: %d\n", addition.num);


}