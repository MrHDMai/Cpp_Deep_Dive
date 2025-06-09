#include<iostream>
#include<vector>

using namespace std;

int main(){
    vector<string> words = {"hello", "world"};
    for (auto it = words.begin(); it != words.end(); ++it) {
        *it = "[" + *it + "]";
        cout << *it << endl;
    }
}