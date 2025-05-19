#include<iostream>

using namespace std;

struct opt{
    opt* ntask;
    string description; 

};

struct operation{
    opt* head = nullptr;
    opt* tail = nullptr;
    void addopt(const string& dec){
        opt* n_task = new opt{nullptr,dec};
        if(!head) head = n_task;
        if(tail) tail->ntask= n_task;
        tail = n_task;
    }
    void print(){
        opt* current = head; 
        while(current){
            cout << "*" << current->description << endl;
            current = current->ntask;
        }
    }
    void clear(){
        while(head){
            opt* temp = head;
            head = head->ntask;
            delete temp;
        }
        tail = nullptr;
    }
    ~operation(){clear();}
};

int main(){
    operation myopt;
    myopt.addopt("code");
    myopt.addopt("read");
    myopt.addopt("code again");
    myopt.addopt("sleeep");
    myopt.addopt("repeat");
    myopt.print();
}