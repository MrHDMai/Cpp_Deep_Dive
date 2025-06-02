#include<iostream>

using namespace std;

struct person{
    string name;
    int age;
};

int main(){
    person person1;
    person1.name = "Ky";
    person1.age = 28;

    person* personptr;
    personptr = &person1;
    cout << "Name: " << personptr->name << endl;
    cout << "Age: " << personptr->age << endl;
}