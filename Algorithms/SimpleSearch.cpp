#include<vector>
#include<iostream>

using namespace std;

void merge(vector<int>& v, int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> l(n1), r(n2);
    
    for(int i = 0; i < n1; i++)
        l[i] = v[left + i];
    for(int j = 0; j < n2; j++)
        r[j] = v[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while(i < n1 && j < n2){
        if(l[i] <= r[j]){
            v[k] = l[i];
            i++;
        } else {
            v[k] = r[j];
            j++;
        }
        k++;
    }
    while(i < n1){
        v[k] = l[i];
        i++;
        k++;
    }
    while(j < n2){
        v[k] = r[j];
        j++;
        k++;
    }
}

void sort(vector<int>& v, int left, int right){
    if(left < right){
        int mid = left + (right - left)/2;
        sort(v, left, mid);
        sort(v, mid + 1, right);
        merge(v, left, mid, right);
    }
}

void check(vector<int>& v, int left, int right){
    if(v.size() == 0){
        cout << "Nothing to sort" << endl;
        return;
    }
    sort(v, left, right);
}

void insertion(vector<int>& v){
    for(int i = 0; i < v.size(); i++){
        int key = v[i];
        int j = i - 1;
        while (j >= 0 && v[j] > key){
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = key;
    }
}

int partition(vector<int>& v, int low, int high){
    int pvt = v[high];
    int i = low - 1;
    for(int j = low; j < high; j++){
        if (v[j] < pvt){
            ++i;
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

void selection(vector<int>& v){
    for(int i = 0; i < v.size(); i++){
        int* min = &v[i];
        for(int j = i + 1; j < v.size(); j++){
            if(v[j] < *min){
                min = &v[j];
            }
            if(min!=&v[i]){
                swap(*min,v[i]);
            }
        }
    }
}

void bubble(vector<int>& v){
    for(int i = 0; i < v.size(); i++){
        bool swp = false;
        for(int j = 0; j < v.size()-1; j++){
            if(v[j] >  v[j + 1]){
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
    for(int i = 0;i < n; i++){
        cin >> v[i];
    }
    // selection(v);
    // for(auto& num : v){
    //     cout << "Selection: " << num << endl;
    // }
    // qs(v,0,v.size()-1);
    // for(auto& sorted : v){
    //     cout << "Quick Sort: " << sorted << endl;
    // }

    // insertion(v);
    // for(auto& val : v){
    //     cout << "Insertion: " << val << endl;
    // }

    // check(v,0,v.size()-1);
    // for(auto& ms : v){
    //     cout <<"Merge Sort: " << ms << endl;
    // }

    bubble(v);
    for(auto& bs : v){
        cout << "Bubble Sort: " << bs << endl; 
    }
}