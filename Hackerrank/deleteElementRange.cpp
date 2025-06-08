#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
    int n,m,range;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    cin >> m;
    for(int i = 0; i < m; i++){
        cin >> range;
    }
    for(int i = 0; i < range; i++){
        if(i = range){
            v.erase(v.begin(),v.end());
        }
        cout << i << endl; 
    }
    for(auto& num : v){
        cout << num << endl;
    }
    
}