#include<iostream>

using namespace std;

bool subsetsum(int* arr, int n, int target){
    bool** dp = new bool*[n + 1];
    for(int i = 0; i <= n; ++i){
        dp[i] = new bool[target + 1];
    }
    for(int i = 0; i <= n; ++i)
        dp[i][0] = true;
    for(int j = 1; j <= n; ++j)
        dp[0][j] = false;
    for(int i = 1; i <= n; ++i){
        for(int sum = 1; sum <= target; ++sum){
            if(arr[i -1] <= sum)
                dp[i][sum] = dp[i -1][sum] || dp[i -1][sum - arr[i-1]];
            else 
                dp[i][sum] = dp[i-1][sum];
        }
    }
    bool result = dp[n][target];
    for(int i = 0; i <= n; ++i)
        delete[] dp[i];
    delete[] dp;
    return result;
}

int main(){
    int arr[] = {2,34,4,12,5,2};
    int n = sizeof(arr)/sizeof(arr[0]);
    int target = 9;
    if(subsetsum(arr, n, target))
        cout << "Subset with given sum exist\n";
    else 
        cout << "No subset with given sum\n";
    return 0;
}