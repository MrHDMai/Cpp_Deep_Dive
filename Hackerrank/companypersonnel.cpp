#include<iostream>
#include<string>
using namespace std;

class Employee {
protected:
    string name;
    float salary;
    int id;
    string type;
    static int id_counter;
public:
    virtual void calculateSalary() = 0;
    virtual void displayDetails() = 0;
    virtual void getData() = 0;
    virtual ~Employee() {}
};

int Employee::id_counter = 1000; // Shared counter for all employee types

class FullTimeEmployee : public Employee {
    float bonus;
public:
    FullTimeEmployee() {
        id = ++id_counter;
        type = "Full-time";
    }
    void getData() override {
        cin >> name >> salary >> bonus;
    }
    void calculateSalary() override {
        salary += bonus;
    }
    void displayDetails() override {
        cout << "Employee ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Type: " << type << endl;
        cout << "Salary: " << salary << endl << endl;
    }
};

class PartTimeEmployee : public Employee {
    int hoursWorked;
    float hourlyRate;
public:
    PartTimeEmployee() {
        id = ++id_counter;
        type = "Part-time";
    }
    void getData() override {
        cin >> name >> hoursWorked >> hourlyRate;
    }
    void calculateSalary() override {
        salary = hoursWorked * hourlyRate;
    }
    void displayDetails() override {
        cout << "Employee ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Type: " << type << endl;
        cout << "Salary: " << salary << endl << endl;
    }
};

class Intern : public Employee {
    float stipend;
    int durationMonths;
public:
    Intern() {
        id = ++id_counter;
        type = "Intern";
    }
    void getData() override {
        cin >> name >> stipend >> durationMonths;
    }
    void calculateSalary() override {
        salary = stipend;
    }
    void displayDetails() override {
        cout << "Employee ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Type: " << type << endl;
        cout << "Stipend: " << salary << endl;
        cout << "Duration: " << durationMonths << " months" << endl << endl;
    }
};

int main() {
    int n, type;
    cin >> n;
    Employee* employees[n];
    
    for(int i = 0; i < n; i++) {
        cin >> type;
        if(type == 1) employees[i] = new FullTimeEmployee();
        else if(type == 2) employees[i] = new PartTimeEmployee();
        else employees[i] = new Intern();
        
        employees[i]->getData();
        employees[i]->calculateSalary();
    }
    
    for(int i = 0; i < n; i++) {
        employees[i]->displayDetails();
        delete employees[i];
    }
    
    return 0;
}