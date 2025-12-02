#include<iostream>
#include<vector>

using namespace std;

void sort(vector<int>& v, int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int>l(n1),r(n2);
    for(int i = 0; i < n1; i++)
        l[i] = v[left + 1];
    for(int j = 0; j < n2; j++)
        r[j] = v[mid + 1 + j];
    int i = 0,j=0,k=left;
    for(int i = 0; i < n1; i++){
        if(l[i] <= r[j]){
            v[k] = l[i];
            i++;
        } else{
            v[k] = r[j];
            j++;
        }
        k++;
    }
    while(i <= n1){
        v[k] = l[i];
        i++;
        k++;
    }
    while(j <= n2){
        v[k] = r[j];
        j++;
        k++;
    }
}

void merge(vector<int>& v, int left, int right){
    if(left < right){
        int mid = left + (right-left)/2;
        merge(v,left,mid);
        merge(v,mid + 1, right);
        sort(v,left,mid,right);
    }
}

void check(vector<int>& v, int left, int right){
    if(v.size() <= 1){
        return;
    }
    merge(v,left,right);
}

int main(){
    int n;
    cin >> n; 
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    check(v,0,v.size()-1);
    for(auto& num : v){
        cout << num << endl;
    }
}