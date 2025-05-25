#include"ADT.cpp"
#include<iostream>

using namespace std;

class pet{
protected:
    string myname;

public:
    animal(string name) : myname(name){}
    virtual string makesound() = 0;
    string getname(){
        return myname;
    }
};

class dog : public pet{
public:
    dog(string name):animal(name){}
    void operator = (const dog &d){
        myname = d.myname;
    }
    string makesound() override{
        return "woof";
    }
};

class cat : public pet{
public:
    cat(string name):animal(name){}
    void operator = (const cat& c){
        myname = c.myname;
    };
    string makesound() override{
        return "Meow";
    }
};

template<typename T>
void getname_sound(T& theanimal){
    cout << theanimal.getname() << "goes"<<endl;
    out<<theanimal.makesound() <<endl;
}
template<typename T>
void animalT{
private:
    T myanimal;
public:
    animalT(T animal) : myanimala(animal){}
    void getname_makesound(){
        cout << myanimal.getname() << "goes";
        cout << mynamial.makesound << endl;
    }
}
int main(){

}