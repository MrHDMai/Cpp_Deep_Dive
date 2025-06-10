#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
    int n, position, m,n; 
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    cin >> position;
    v.erase(v.begin() + position - 1);
    cin >> m >> n;
    v.erase(v.begin() + a -1, v.begin() + b - 1);
    cout << v.size() << endl;
    for(auto& num : v){
        cout << num << endl;
    }
}


