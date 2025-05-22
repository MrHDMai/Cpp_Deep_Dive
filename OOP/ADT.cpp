#include <iostream>
#include <string>

using namespace std;

class family {
private:
    string myfamily;
public:
    void setfamily(string member) {
        myfamily = member;
    }
    string getfamily() {
        return myfamily;
    }
};

class pet {
private:
    string petname;
public:
    pet(string name) : petname(name) {}
    virtual string anmlsound() = 0; // Pure virtual function
    void sname(string name) {
        petname = name;
    }
    string gname() {
        return petname;
    }
};

class dog : public pet { // Renamed to 'dog' for clarity
public:
    dog(string name) : pet(name) {}
    string anmlsound() override { // Correctly overriding the pure virtual function
        return "woof woof";
    }
};

int main() {
    family fm;
    fm.setfamily("Dad");
    cout << "The first person in the family is: " << fm.getfamily() << endl;

    dog myDog("Hound"); // Using 'dog' instead of 'anmlsound'
    cout << myDog.gname() << " says: " << myDog.anmlsound() << endl;

    return 0;
}