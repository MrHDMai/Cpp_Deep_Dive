#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

class Person{
protected:
    string name;
    int id;
    static int id_counter;
public:
    Person() : id(++id_counter){}
    virtual void getData() = 0;
    virtual void displayData() const = 0;
    virtual ~Person() {}
};
int Person::id_counter = 1000;

class Student : public Person{
protected:
    vector<string> coursesEnrolled;
    float gpa;
public:
    void getData() override{
        cout << "Enter name of student: " << endl;
        cin >> name;
        cout << "Number of courese: " << endl;
        int n; cin >> n;
        cout <<"Enter course name: " << endl;
        for(int i = 0; i < n; i++){
            string courses; cin >> courses;
            if(coursesEnrolled.size() < 5)
                coursesEnrolled.push_back(courses);
        }
        cout << "Enter GPA :";
        cin >> gpa;
    }
    void displayData() const override{
        cout << "ID" << id << "Name:" << name << "Courses:" <<endl;
        for(const auto& c : coursesEnrolled){
            cout << "courses: " << c << "GPA: " << gpa << endl;
        }
    }
    bool isEnrolled(const string& courses) const{
        return find(coursesEnrolled.begin(), coursesEnrolled.end(), courses) != coursesEnrolled.end();
    }

};

int main(){

}