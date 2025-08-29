//implementation of Fibonacci (Memo + Tab)

//Memoization (top-down + Cache)
#include<iostream>
#include<vector>

using namespace std;

int fibM(int n, vector<int>& dp){
    if(n<=1) return n;
    if(dp[n] != -1) return dp[n];
    dp[n] = fibM(n-1,dp) + fibM(n-2,dp);
    return dp[n];
}

//tabulation (Bottom-up DP)
int fibtb(int n){
    if(n <= 1) return n;
    vector<int>dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    for(int i = 2; i <= n; i++)
        dp[i] = dp[i -1] + dp[i - 2];
    return dp[n];
    
}

//space optimization
int fibsp(int n){
    if(n <= 1) return n;
    int prev2 = 0, prev1 = 1, curr;
    for(int i = 2; i <= n; i++){
        curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

int main(){
    int n;
    cout << "Enter n: ";
    cin >> n;
    //runner implementation for fibonacci Memoization
    vector<int> dp(n + 1, -1);
    cout << "Fibonacci("<<n<<")=" << fibM(n,dp) << endl;
    return 0;
}