/*
Given a sorted vector, taken in a number of query and using the lower bound method, find return "Yes" and the index
if the input is within the array and if not return no. 
*/
#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;

int main(){
    int n;
    cin >>n;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    int m, y;
    cin >> m;
    while(m--){
        cin >> y;
        auto it = lower_bound(v.begin(),v.end(),y);
        int index = it - v.begin() + 1;
        if(it != v.end() && it* == y){
            cout << "Yes " << (it - v.begin() + 1) << endl; 
        } else {
            cout << "No " << index << endl;
        }
    }
}