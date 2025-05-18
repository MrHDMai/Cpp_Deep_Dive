#include<iostream>
#include<vector>

using namespace std;

int main(){
    vector<string> str {"name1", "name2", "name3", "name4"};
    for(auto i = 0; i < str.size(); i++){
        cout << str.at(0) << endl; // this will print 1, 4 times since it is access the first index.
                                    // doing it by this method has limitation - it is random access and the scope needs to be specified.
    }

    for(string name : str){
        cout << name << endl; // this will print out all the name of the items
    }
}