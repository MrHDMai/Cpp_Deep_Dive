#include<iostream>
#include<vector>

using namespace std;

bool subsetsum(int* arr, int n, int target){
    std::vector<char> dp((n + 1LL) * (target + 1), 0);
    for(int i = 0; i <= n; ++i)
        dp[i * (target + 1) + 0] = 1;
    for(int j = 1; j <= target; ++j)
        dp[0 * (target + 1) + j] = 0;
    for(int i = 1; i <= n; ++i){
        for(int sum = 1; sum <= target; ++sum){
            if(arr[i -1] <= sum)
                dp[i * (target + 1) + sum] = dp[(i -1) * (target + 1) + sum] || dp[(i -1) * (target + 1) + (sum - arr[i-1])];
            else 
                dp[i * (target + 1) + sum] = dp[(i -1) * (target + 1) + sum];
        }
    }
    bool result = dp[n * (target + 1) + target] != 0;
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