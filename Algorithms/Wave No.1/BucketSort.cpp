#include<stack>
#include<vector>
#include<iostream>
#include<cmath>

using namespace std;

template<typename T>
void isort(vector<T>& bucket){
    for(size_t i = 0; i < bucket.size(); i++){
        T target = bucket[i];
        int j = i - 1;
        while(j >= 0 && bucket[j] > target){
            bucket[j + 1] = bucket[j];
            --j;
        }
        bucket[j + 1] = target;
    }
}

template<typename T>
void bsort(vector<T>& v,int numofbuckets = 10){
    if(v.empty()) return;
    int minV = v[0];
    int maxV = v[0];
    for(const auto& elem : v){
        if(elem < minV) minV = elem;
        if(elem > maxV) maxV = elem;
    }
    if(minV == maxV) return;
    T range = (maxV - minV)/static_cast<T>(numofbuckets);
    if(range == 0) range = 1;
    vector<vector<T>>buckets(numofbuckets);
    for(const auto& elem : v){
        int bucketIndex = min(static_cast<int>((elem - minV)/range), numofbuckets - 1);
        buckets[bucketIndex].push_back(elem);
    } 
    v.clear();
    for(auto& bucket : buckets){
        isort(bucket);
        for(const auto& elem : bucket){
            v.push_back(elem);
        }
    }
}
int main(){
    int n;
    cout << "number of elements: " << endl;
    cin >> n;
    vector<float> unsorted(n);
    for(int i = 0; i < n; i++){
        cin >> unsorted[i];
    }
    bsort(unsorted);
    for (const auto& sorted : unsorted){
        cout << sorted <<endl;
    }
    return 0;  
}