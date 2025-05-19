#include<iostream>

using namespace std;

class house{
private:
    int length{0},width{0};
public:
    void setval(int x, int y){
        length = x;
        width = y;
    }
    int cala(){
        return length * width;
    }
    void print(){
        cout << "The area is: " << cala() << endl;
    }
};

int main(){
    house myhouse;
    myhouse.setval(500,5000);
    myhouse.cala();
    myhouse.print();
}