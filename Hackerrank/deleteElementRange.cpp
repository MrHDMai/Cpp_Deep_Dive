#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
    int n, postition,a,b;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    cin >> postition;
    v.erase(v.begin() + postition - 1); // adjust for 0 position index
    cin >> a >> b;
    v.erase(v.begin() + a - 1, v.begin() + b -1); // adjust for 0 index from start position to end position within the vector
    cout<< v.size() << endl; // print the size of vector
    for(auto& num : v){  //iterate through the vector and produce when left over values
        cout << num << " ";
    }
    cout << endl;
    return 0;
}