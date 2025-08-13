#include<cstdio>
#include<cstdlib>
#include<cstdint>

static inline long long maxll(long long a, long long b) {return a > b? a : b; }

long long maxpathsum(const long long* grid, int R, int C){
    long long* dp = (long long*) std::malloc(sizeof(long long)* C);
    if(!dp) return 0;

    dp[0] = grid[0];
    for(int j = 1; j < C; ++j) dp[j] = dp[j - 1] + grid[j];
    for(int i = 1; i < R; ++i){
        const long long* row = grid + (long long)i * C;
        dp[0] += row[0];
        for(int j = 1; j < C; ++j){
            long long fromleft = dp[j - 1];
            long long fromup = dp[j];
            dp[j] = maxll(fromleft, fromup) + row[j];
        }
    }
    long long ans = dp[C-1];
    std::free(dp);
    return ans;
}

int main(){
    int R, C;
    if(std::scanf("%d %d", &R, &C) != 2) return 0;
    long long* grid = (long long*) std::malloc(sizeof(long long) * (size_t)R * (size_t)C);
    if(!grid) return 0;
    for(int i = 0; i < R; ++i)
        for(int j = 0; j < C; ++j)
            std::scanf("%lld",&grid[(size_t)i * C + j]); 
    long long ans = maxpathsum(grid,R,C);
    std::printf("%lld\n", ans);
    std::free(grid);
    return 0;
}