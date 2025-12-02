#include <iostream>
using namespace std;

int knapSack(int W, int n, int* wt, int* val) {
    int** dp = new int*[n + 1];
    for (int i = 0; i <= n; ++i)
        dp[i] = new int[W + 1];

    // Build table dp[][], dp[i][w] = max value with first i items and capacity w
    for (int i = 0; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i - 1] <= w)
                dp[i][w] = (val[i - 1] + dp[i - 1][w - wt[i - 1]] > dp[i - 1][w]) ?
                           val[i - 1] + dp[i - 1][w - wt[i - 1]] : dp[i - 1][w];
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    int result = dp[n][W];

    for (int i = 0; i <= n; ++i) delete[] dp[i];
    delete[] dp;

    return result;
}

int main() {
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int W = 50;
    int n = sizeof(val) / sizeof(val[0]);

    cout << "Max value in Knapsack = " << knapSack(W, n, wt, val) << endl;
    return 0;
}
