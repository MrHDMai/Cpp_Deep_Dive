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

int main(){
    int n;
    cout << "Enter n: ";
    cin >> n;
    //runner implementation for fibonacci Memoization
    vector<int> dp(n + 1, -1);
    cout << "Fibonacci("<<n<<")=" << fibM(n,dp) << endl;
    return 0;
}