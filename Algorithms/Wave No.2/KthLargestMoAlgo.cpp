#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

struct Query {
    int l, r, k, idx, block;
};

static const int MAXN = 200000;

int n, q;
int arr[MAXN + 5];
int freq[MAXN + 5];
int fenwickTree[MAXN + 5];
int M;

// Fenwick Tree: update index i by +v
void fenwick_update(int i, int v) {
    for (; i <= M; i += (i & -i))
        fenwickTree[i] += v;
}

// Fenwick Tree: prefix sum
int fenwick_sum(int i) {
    int s = 0;
    for (; i > 0; i -= (i & -i))
        s += fenwickTree[i];
    return s;
}

// Fenwick binary lifting to find k-th smallest (ID)
int kth_smallest(int k) {
    int pos = 0;
    int bit = 1 << 18; // sufficient for M ≤ 2e5

    while (bit > 0) {
        if (pos + bit <= M && fenwickTree[pos + bit] < k) {
            k -= fenwickTree[pos + bit];
            pos += bit;
        }
        bit >>= 1;
    }
    return pos + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    vector<int> comp;
    comp.reserve(n);

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        comp.push_back(arr[i]);
    }

    // Coordinate compression
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    M = comp.size();

    auto getID = [&](int x) {
        return int(lower_bound(comp.begin(), comp.end(), x) - comp.begin()) + 1;
    };

    for (int i = 1; i <= n; i++)
        arr[i] = getID(arr[i]);

    int block_size = static_cast<int>(sqrt(n));
    vector<Query> queries(q);

    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r >> queries[i].k;
        queries[i].idx = i;
        queries[i].block = queries[i].l / block_size;
    }

    // Mo's sorting order
    sort(queries.begin(), queries.end(), [&](const Query &a, const Query &b) {
        if (a.block != b.block)
            return a.block < b.block;
        return (a.block & 1) ? (a.r > b.r) : (a.r < b.r);
    });

    vector<int> ans(q);

    int L = 1, R = 0;

    auto add = [&](int pos) {
        int v = arr[pos];
        freq[v]++;
        if (freq[v] == 1)
            fenwick_update(v, +1);
    };

    auto remove = [&](int pos) {
        int v = arr[pos];
        freq[v]--;
        if (freq[v] == 0)
            fenwick_update(v, -1);
    };

    // Process queries
    for (auto &Q : queries) {
        while (L > Q.l) add(--L);
        while (R < Q.r) add(++R);
        while (L < Q.l) remove(L++);
        while (R > Q.r) remove(R--);

        int len = Q.r - Q.l + 1;
        int kth_small = len - Q.k + 1; // convert kth-largest -> kth-smallest

        int id = kth_smallest(kth_small);
        ans[Q.idx] = comp[id - 1];
    }

    // Output answers in original order
    for (int x : ans)
        cout << x << "\n";

    return 0;
}
