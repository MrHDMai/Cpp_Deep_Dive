#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

pair<int, vector<int>> rodCutting(const vector<int>& price, int n) {
    vector<int> dp(n + 1, 0);     // dp[i] = max profit for rod length i
    vector<int> cuts(n + 1, 0);   // cuts[i] = best first cut for rod length i

    // Build up the dp array
    for (int i = 1; i <= n; ++i) {
        int maxVal = -1;
        for (int j = 0; j < i; ++j) {
            if (maxVal < price[j] + dp[i - j - 1]) {
                maxVal = price[j] + dp[i - j - 1];
                cuts[i] = j + 1; // store the piece length (j+1)
            }
        }
        dp[i] = maxVal;
    }

    // Reconstruct the cuts
    vector<int> solutionCuts;
    int length = n;
    while (length > 0) {
        solutionCuts.push_back(cuts[length]);
        length -= cuts[length];
    }

    return {dp[n], solutionCuts};
}

int main() {
    vector<int> price = {1, 5, 8, 9, 10, 17, 17, 20}; // prices for rod lengths 1 to 8
    int rodLength = 8;

    auto [maxProfit, cuts] = rodCutting(price, rodLength);

    cout << "Maximum Obtainable Value: " << maxProfit << endl;
    cout << "Cuts to make for maximum profit: ";
    for (int cut : cuts) {
        cout << cut << " ";
    }
    cout << endl;

    return 0;
}
