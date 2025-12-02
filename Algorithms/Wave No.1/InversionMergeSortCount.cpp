#include<iostream>
#include<vector>
using namespace std;

long long mergeandcount(vector<int>& arr, int left, int mid, int right){
    vector<int> leftsub(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> rightsub(arr.begin() + mid + 1, arr.begin() + right + 1);
    int i = 0, j = 0, k = left;
    long long inv_count = 0;
    while(i < leftsub.size() && j < rightsub.size()){
        if(leftsub[i] <= rightsub[j]){
            arr[k++] = leftsub[i++];
        } else{
            arr[k++] = leftsub[j++];
            inv_count+=(leftsub.size() - i); 
        }
    }
    while(i < leftsub.size()) arr[k++] = leftsub[i++];
    while(j < rightsub.size()) arr[k++] = rightsub[j++];
    return inv_count;
}

long long mergeSandCount(vector<int>& arr, int left, int right){
    long long inv_count = 0;
    if(left < right){
        int mid = (left + right)/2;
        inv_count += mergeSandCount(arr,left,mid);
        inv_count += mergeSandCount(arr, mid + 1, right);
        inv_count += mergeandcount(arr, left, mid, right);
    }
    return inv_count; 
}

int main(){
    vector<int> arr = {2,4,1,3,5};
    long long result = mergeSandCount(arr,0,arr.size() - 1);
    cout << "Number of Inversion: " << result << endl;
    return 0;
}