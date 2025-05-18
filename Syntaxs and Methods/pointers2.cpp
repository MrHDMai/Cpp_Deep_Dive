#include<iostream>

using namespace std;

struct task{
    task* pNext; //consider that the pointer to the struct's name infers that there will be multiple last linked to this task 
    string description;
};

//creating a linkedlist - a more advance version of task list
struct tasklist{
    task* head = nullptr;
    task* tail = nullptr;
    void addtask(const string& dec){
        task* ntask = new task{nullptr,dec};
        if(!head) head = ntask;
        if(tail) tail ->pNext = ntask;
        tail = ntask;
    }
    void printall(){ //print the task
        task* current = head; //points to the task struct and set the current task as head
        while(current){ //while there is a head
            cout << ". " << current -> description << endl; //print the head
            current = current ->pNext; // set the head task to the next task on the list
        }
    }
    void cleanup(){
        while(head){
            task* temp = head;
            head = head -> pNext;
            delete temp;
        }
        tail = nullptr;
    }
    ~tasklist(){
        cleanup();
    }
};

int main(){
    task prort;
    prort.description = "Code";
    task* task_2 = new task;
    task_2 ->description = "Sleep";
    cout << prort.description<<endl;
    cout << task_2->description <<endl; // use poitner access to point and print out the description for task 2
    delete task_2;

    cout << "Printing the task list as linked list\n" << endl;
    tasklist mytask;
    mytask.addtask("CODE");
    mytask.addtask("SLEEP");
    mytask.addtask("BATHROOM");
    mytask.addtask("CODE SOME MORE");
    mytask.addtask("REPEAT");
    cout <<"MY DAILY ROUTINE: \n"<<endl;
    mytask.printall();

}