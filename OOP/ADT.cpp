#include <iostream>
#include <string>

using namespace std;

class family {
protected:
    string myfamily;
public:
    void setfamily(string member) {
        myfamily = member;
    }
    virtual string nmember() = 0;
    string getfamily() {
        return myfamily;
    }
};

class fmember : public family{
public:
    fmember(string member){setfamily(member);}// since family doesn't have a constructor that would return a string we have to inti set family here
    string nmember() override{
        return "mom";
    }
};

class mem : public family{
public:
    mem(string member){setfamily(member);}
    void operator = (const mem &ch){
        myfamily = ch.myfamily;
    }
    string nmember() override{
        return "Hao";
    }
};

class pet {
protected:
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
    void operator = (const dog &d){ //operator overload
        petname = d.petname;
    }
    string anmlsound() override {  //overriding the pure virtual function
        return "woof woof";
    }
};

class cat : public pet{
public:
    cat(string name) : pet(name){}
    void operator = (const cat &c){
        petname = c.petname;
    }
    string anmlsound() override{
        return "Meow Meow";
    }
};

template<typename L>
void getmember(L &allmember, string member){
    allmember.setfamily(member);
    cout<<allmember.getfamily()<<endl;
}

template<typename T>
void getname_sound(T &thepet){
    cout << thepet.anmlsound() << endl;
    cout << thepet.gname() << endl;
}

int main() {
    fmember fm("Dad");
    cout << "The first person in the family is: " << fm.getfamily() << endl;
    fmember fm2("Mom");
    cout << "The second person in my family is: " << fm2.getfamily() << endl;

    dog myDog("Hound"); // Using 'dog' instead of 'anmlsound'
    cout << myDog.gname() << " says: " << myDog.anmlsound() << endl;

    dog myd = dog("Terrier");
    cout << myd.gname() << " is barking: ";
    cout << myd.anmlsound() << endl;

    dog myd2 = dog("Pit");
    cout << myd2.gname() << " is barking: ";
    cout << myd2.anmlsound() <<endl;

    cat c = cat("Prince");
    getname_sound(c);

    mem m("Hao");
    getmember(m, "Hao");

    return 0;
}