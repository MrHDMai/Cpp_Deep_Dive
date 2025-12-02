/*This is a simple linked list
*/

#include<iostream>
#include<vector>

using namespace std;

struct operations{
    operations* n_opt;
    string description; 
};

struct opt{
    operations* head = nullptr;
    operations* tail = nullptr;
    void addopt(const string& dec){
        operations* nopt = new operations{nullptr,dec};
        if(!head) head=nopt;
        if(tail) tail->n_opt=nopt;
        tail = nopt;
    }
    void printopt(){
        operations* current = head;
        while(current){
            cout << "."<< current->description << endl;
            current = current->n_opt;
        }
    }
    void clear(){
        while(head){
            operations* temp = head; 
            head = head->n_opt;
            delete temp;
        }
        tail = nullptr;
    }
    ~opt(){clear();}
};

int main(){
    opt myopt;
    myopt.addopt("code");
    myopt.addopt("read");
    myopt.addopt("code again");
    myopt.addopt("sleeep");
    myopt.addopt("repeat");
    myopt.printopt();
}