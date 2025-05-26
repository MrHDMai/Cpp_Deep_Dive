#include<iostream>
using namespace std;
template<typename T>
class node{
public:
    int value;
    node *next = nullptr; //consider that when a new pointer objecct is created, always set it to a nullptr val
    /* consider that this present implementation cannot take in datatype of any kind - in order to achieve this
    we use create a template class in order to implement this*/
    node(T value) : value(value),next(NULL){}
};
template<typename T>
void printnode(node<T> *node){
    while(node!=NULL){
        cout <<  node->value << endl;
        node = node->next;
    }
    cout << "NULL" << endl;
}

int main(){
    // node * node1 = new node();
    // node1 -> value = 5;

    // node * node2 = new node();
    // node2 -> value = 20;

    // node * node3 = new node();
    // node3 -> value = 40; 

    // //reassine with ptr
    // node1 -> next = node2; 
    // node2 -> next = node3;

    // printnode(node1);
    // printnode(node2);
    node<float> * node1 = new node<float>(4.6);
    node<float> * node2 = new node<float>(5.7);
    node<float> * node3 = new node<float>(10.6);
    node1 -> next = node2; 
    node2 -> next = node3;
    printnode(node1);
    printnode(node2);
    return 0;

}