#include<iostream>
#include<string>

using namespace std;

class animal{
private:
    string breed;

public:
    void setname(string mybreed){
        breed = mybreed;
    }
    string getname(){
        return breed;
    }
};

int main(){
    animal dog = animal();
    dog.setname("Pitbull");
    cout << "The dog's breed is: \n" <<dog.getname() << endl;
}