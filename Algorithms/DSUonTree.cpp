#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000;
vector<int> g[MAXN+1];
int col[MAXN+1];
int sz[MAXN+1];
int bigChild[MAXN+1];
int ans[MAXN+1];

unordered_map<int,int>* mp[MAXN+1];   // pointer to each node's map

int N;

void dfsSize(int u, int p) {
    sz[u] = 1;
    bigChild[u] = -1;
    int mx = 0;

    for (int v : g[u]) {
        if (v == p) continue;
        dfsSize(v, u);
        sz[u] += sz[v];
        if (sz[v] > mx) {
            mx = sz[v];
            bigChild[u] = v;
        }
    }
}

void dfs(int u, int p) {
    // heavy child keeps main map
    if (bigChild[u] != -1) {
        dfs(bigChild[u], u);
        mp[u] = mp[bigChild[u]];
    } else {
        mp[u] = new unordered_map<int,int>();
    }

    // add own color
    (*mp[u])[col[u]]++;

    // merge light children
    for (int v : g[u]) {
        if (v == p || v == bigChild[u]) continue;

        dfs(v, u);

        for (auto &px : *mp[v]) {
            (*mp[u])[px.first] += px.second;
        }
    }

    ans[u] = mp[u]->size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> col[i];

    for (int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfsSize(1, 0);
    dfs(1, 0);

    for (int i = 1; i <= N; i++)
        cout << ans[i] << " ";
    cout << "\n";
}
