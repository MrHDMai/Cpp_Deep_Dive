#include <iostream>
#include <string>
using namespace std;

class animal {
protected:
    string breed;
    int age;
public:
    virtual void setbreed(const string& b) = 0;
    virtual void setage(int a) = 0;
    virtual void getage() = 0;
    virtual ~animal() {}
};

class dog : public animal {
    int tag_id;
    static int tag_counter;
public:
    dog() {
        tag_id = ++tag_counter;
    }
    void setbreed(const string& b) override {
        breed = b;
    }
    void setage(int a) override {
        age = a;
    }
    void getage() override {
        cout << "Breed: " << breed << ", Age: " << age << ", Tag ID: " << tag_id << endl;
    }
};

int dog::tag_counter = 0;

// Example usage
int main() {
    dog d;
    d.setbreed("Labrador");
    d.setage(3);
    d.getage();
    return 0;
}