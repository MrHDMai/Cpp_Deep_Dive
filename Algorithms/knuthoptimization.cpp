#include <bits/stdc++.h>
using namespace std;

const long long INF = 4e18;

// cost[l][r] must be precomputed
// use prefix sums for O(1) range sums

int main() {
    int N;
    cin >> N;
    vector<long long> a(N+1);
    for (int i = 1; i <= N; i++) cin >> a[i];

    // prefix sum
    vector<long long> pre(N+1);
    for (int i = 1; i <= N; i++) pre[i] = pre[i-1] + a[i];

    auto cost = [&](int l, int r) {
        return pre[r] - pre[l-1];
    };

    // DP and opt array
    vector<vector<long long>> dp(N+2, vector<long long>(N+2, 0));
    vector<vector<int>> opt(N+2, vector<int>(N+2, 0));

    // base: dp[i][i] = 0, opt[i][i] = i
    for (int i = 1; i <= N; i++) {
        dp[i][i] = 0;
        opt[i][i] = i;
    }

    // increasing length
    for (int length = 2; length <= N; length++) {
        for (int l = 1; l + length - 1 <= N; l++) {
            int r = l + length - 1;

            dp[l][r] = INF;

            // search only from opt[l][r-1] to opt[l+1][r]
            int start = opt[l][r-1];
            int end   = opt[l+1][r];
            if (start > end) swap(start, end);

            for (int k = start; k <= end; k++) {
                long long val = dp[l][k] + dp[k+1][r] + cost(l, r);
                if (val < dp[l][r]) {
                    dp[l][r] = val;
                    opt[l][r] = k;
                }
            }
        }
    }

    cout << dp[1][N] << "\n";
    return 0;
}
