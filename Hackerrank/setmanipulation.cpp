#include<math>
#include<cstdio>
#include<vector>
#include<iostream>
#include<set>
#include<algorithm>

using namespace std;

int main(){
    int q;
    cin >> q;
    set<int> s;
    for(int i = 0; i < q; i++){
        int type, value;
        cin >> type >> value;
        if(type == 1){
            s.insert(value);
        } else if (type == 2){
            s.erase(value);
        } else if (type == 3){
            if(s.find(value) != s.end()){
                cout << "Yes" <<  endl;
            } else {
                cout << "No" << endl;
            }
        }
    }
    return 0;
}