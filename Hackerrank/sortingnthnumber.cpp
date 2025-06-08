/*
Given an nth length of number, use a vector to sort the number accordingly.
*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std; 

int main(){
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    sort(v.begin(),v.end());
    for(auto &num : v){
        cout << num << " " << endl;
    }
}