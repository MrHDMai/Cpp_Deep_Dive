#include <bits/stdc++.h>
using namespace std;

struct CentroidDecomposition {
    int n;
    vector<vector<int>> adj;
    vector<int> sz;
    vector<bool> removed;
    vector<int> parent; // centroid tree parent

    CentroidDecomposition(int n)
        : n(n), adj(n), sz(n), removed(n, false), parent(n, -1) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int dfs_size(int u, int p) {
        sz[u] = 1;
        for (int v : adj[u]) {
            if (v != p && !removed[v])
                sz[u] += dfs_size(v, u);
        }
        return sz[u];
    }

    int find_centroid(int u, int p, int total) {
        for (int v : adj[u]) {
            if (v != p && !removed[v] && sz[v] > total / 2)
                return find_centroid(v, u, total);
        }
        return u;
    }

    int decompose(int root, int p) {
        int total = dfs_size(root, -1);
        int c = find_centroid(root, -1, total);

        parent[c] = p;     // store centroid parent (in centroid tree)
        removed[c] = true; // mark as processed

        for (int v : adj[c]) {
            if (!removed[v]) {
                decompose(v, c);
            }
        }

        return c;
    }

    void build(int root = 0) {
        decompose(root, -1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    CentroidDecomposition cd(n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v; // convert to 0-based
        cd.addEdge(u, v);
    }

    cd.build(); // build centroid tree

    // Output centroid parent of each node
    // parent[x] = -1 means this node is the root centroid
    for (int i = 0; i < n; i++) {
        cout << cd.parent[i] + 1 << " "; // convert back to 1-based
    }
    cout << "\n";

    return 0;
}
