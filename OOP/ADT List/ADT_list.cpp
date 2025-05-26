/* list are an stream of data with similar data type there are various methods that programmers may use to 
manipulate the list - get, insert, search and remove*/
#include<iostream>
#include"list.h" //call in the list header file
using namespace std;
list::list(): mycount(0), myitem(nullptr){};
list::~list(){
    delete[] myitem;
}

int list::get(int index){
    /*check if index is out of boundd*/
    if(index < 0 || index >= mycount){
        return -1; //complexity-> 0(1);
    }
    return myitem[index];
}

void list::insert(int index, int val){
    if(index < 0 || index > mycount){
        return;
    }
    int *oldarr = myitem; // save pointer that hold the value of the original arr
    mycount++;
    myitem = new int[mycount]; // allocate new array container to copy over values
    //create loops to copy over the value;
    for(int i = 0, j = 0; i < mycount; ++i){
        if(index == i){
            myitem[i] = val; //insert new values into the new array
        } else {
            myitem[i] = oldarr[j]; // keep copying from the old arr
            ++j; 
        }
    }
    delete[] oldarr; // free up the old array
    //coplexity -> 0(n)
}

int list::search(int val){
    for(int i = 0; i < mycount; ++i){
        if(myitem[i] == val){
            return i;
        }
    }
    return -1;
    //complexity -> 0(1)
}

void list::remove(int index){
    if(index < 0 || index >= mycount){
        return;
    }
    int *oldarr = myitem;
    mycount--;
    myitem = new int[mycount];

    for(int i = 0, j = 0; i <= mycount;++j){
        if(index == j) continue;
        myitem[i] = oldarr[j];
        ++i;
    }
    delete[] oldarr; 
    //complexity -> 0(n);
}

int list::count(){
    return mycount;
}

int main(){
    list ls; // Simplified initialization
    ls.insert(0, 1); // Insert at beginning
    ls.insert(1, 2); // Append
    ls.insert(2, 3);
    ls.insert(3, 4);
    ls.insert(4, 5); // Final element
    
    /* Display list contents */
    for(int i = 0; i < ls.count(); ++i) {
        cout << ls.get(i) << endl;
    }
    
    /* Test removal */
    ls.remove(2); // Remove middle element
    cout << "After removal:" << endl;
    for(int i = 0; i < ls.count(); ++i) {
        cout << ls.get(i) << endl;
    }
    
    return 0;
}