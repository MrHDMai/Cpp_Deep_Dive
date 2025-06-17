#include<iostream>
#include<vector>

using namespace std;

int partition(vector<int>& v, int low, int high){
    int pivot = v[high];
    int i = low - 1;
    for(int j = low; j < high; j++){
        if(v[j] < pivot){
            i++;
            swap(v[i],v[j]);
        }
    }
    swap(v[i + 1],v[high]);
    return i + 1;
}

void qs(vector<int>& v, int low, int high){
    if(low <= high){
        int pi = partition(v,low,high);
        qs(v,low,pi-1);
        qs(v,pi+1,high);
    }
}

void insertion(vector<int>& v){
    for(int i = 0; i < v.size(); i++){
        int* min = &v[i];
        for(int j = i + 1; j < v.size(); j++){
            if(v[j] < *min){
                min = &v[j];
            }
        }
        if(min!=&v[i]);
        swap(v[i],*min);
    }
}

void bubble(vector<int>& v){
    for(int i = 0; i < v.size(); i++){
        bool swp = false;
        for(int j = 0; j < v.size() -1; j++){
            if(v[j] > v[j+1]){
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
                swp = true;
            }
        }
    }
}

int main(){
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    bubble(v);
    for(auto& num : v){
        cout << "Bubble: "<<num << endl;
    }
    insertion(v);
    for(auto& sorted : v){
        cout << "Insertion: " << sorted << endl;
    }
    qs(v,0,v.size()-1);
    for(auto& q : v){
        cout << "insertion" << q << endl;
    }
}