#include<iostream>
#include<vector>

using namespace std;

/*Find the min and max of an arr
*/

int functionMin(vector<int>& v){
    int min = v[0];
    for(int i = 0; i < v.size(); i++){
        if(min > v[i]){
            min = v[i];
        }
    }
    return min;
}

int functionMax(vector<int>& v){
    int max = v[0];
    for(int i = 0; i < v.size(); i++){
        if(v[i] > max)
        max = v[i];
    }
    return max;
}

int main(){
    int n;
    cin >>n;
    vector<int>v(n);
    for(int i = 0; i < n; i ++){
        cin >> v[i];
    }
    int min = functionMin(v);
    int max = functionMax(v);
    int result = max - min;
    cout << result << endl;
}