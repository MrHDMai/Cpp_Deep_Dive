#include<iostream>
#include<cstdio>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

/*
Objective:
- Create three classes - Person, Professor, Student.
- Person should have the name and age data member.
- Professor should have two integer member, publication and cur_id.
    Professor should have two member functions: getdata and putdata.
    getdata should take the input from the user=> the name, age, and publication of the professor.
    putdata should print the name, age, and publication of the professor including their cur_id;
- Student should have two data members: marks which has an array of 6 and cur_id.
    getdata should get input from the user => the name, age and the mark of the student
    putdata should print the name, age amd sum of matks and the cur_id of the student. 
- Consider that for each objects being creating of the professor or student class, subsequent ID should be assigned
    starting is 1.
- Leverage virtual functions to solve. 

*/
class Person{
private:
    int age;
    string name;
public:
    virtual void getdata() = 0;
    virtual void putdata() = 0;
    virtual ~person(){};
    
};

class Professor : public Person{
    int publication;
    static int cur_id_counter;
    int cur_id;
public:
    professor(){
        cur_id = ++cur_id_counter;
    }
    void getdata() override{
        cin >> name >> age >> publication;
    }
    cout << cur_id << endl;
    void putdata() override{
        cout << "name" << " " << age << " " << publication << " "<< endl;
    }
};

int professor::cur_id_counter = 0;

class Student:public Person{
    int marks[6];
    static int cur_id_counter;
    int cur_id;
public:
    Student(){
        cur_id = ++cur_id_counter;
    }
    void getdata() override{
        cin >> name >> age;
        for(int i = 0; i < 6; i++){
            cin >> mark[i];
        }
    }
    cout<<cur_id<<endl;
    void putdata() override{
        int sum = 0;
        for(int i = 0; i < 6; i++){
            sum += marks[i];
        }
        cout << name <<" "<<age<<" "<<sum<<" "<<endl;
    }
    
};

int Student::cur_id_counter = 0;

int main(){
    int n, val;
    cin>>n; //The number of objects that is going to be created.
    Person *per[n];

    for(int i = 0;i < n;i++){

        cin>>val;
        if(val == 1){
            // If val is 1 current object is of type Professor
            per[i] = new Professor;

        }
        else per[i] = new Student; // Else the current object is of type Student

        per[i]->getdata(); // Get the data from the user.

    }

    for(int i=0;i<n;i++)
        per[i]->putdata(); // Print the required output for each object.

    return 0;

}