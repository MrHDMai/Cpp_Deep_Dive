#include<iostream>
#include<vector>
#include<map>

using namespace std;

int main(){
    int q;
    cin >> q;
    map<string,int> mp;
    for(int i = 0; i < q; i++){
        int qt;
        cin >> qt;
        string name;
        cin >> name;
        if(qt == 1){
            int mark;
            cin >> mark;
            mp[name] = mp[name] + mark;
        } else if (qt == 2){
            mp.erase(name);
        } else if(qt == 3){
            cout << mp[name] << endl;
        }
    }
    return 0;
}