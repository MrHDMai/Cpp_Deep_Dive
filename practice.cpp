#include<iostream>
#include<vector>
#include<algorithm>
#include<deque>
using namespace std;

void printmax(int arr[], int n, int k){
    deque<int> dq;
    for(int i = 0; i < n; i++){
        while(!dq.empty() && dq.front() <= i - k){
            dq.pop_front();
        }
        while(!dq.empty() && arr[i] >= arr[dq.back()]){
            dq.pop_back();
        }
        dq.push_back(i);
        if(i > k - 1){
            cout << arr[dq.front()] << " ";
        }
        cout << endl;
    }
}


int main(){
    int t;
    cin >> t;
    while(t--){
        int n,k;
        cin >> n >> k;
        int arr[n];
        for(int i = 0; i < n; i++){
            cin >> arr[i];
            printmax(arr,n,k);
        }
    }
}