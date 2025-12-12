#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;

struct Fenwick {
    int n;
    vector<long long> bit;

    Fenwick(int n) : n(n), bit(n + 1, 0) {}

    // add value v at index idx
    void update(int idx, long long v) {
        for (++idx; idx <= n; idx += idx & -idx)
            bit[idx] += v;
    }

    // prefix sum [0..idx]
    long long query(int idx) const {
        long long s = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            s += bit[idx];
        return s;
    }

    // sum range [l..r]
    long long range_sum(int l, int r) const {
        return query(r) - query(l - 1);
    }
};

int main() {
    int n, q;
    cin >> n >> q;

    Fenwick ft(n);
    vector<long long> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ft.update(i, a[i]);
    }

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int i; long long v;
            cin >> i >> v;
            ft.update(i, v); // add v to index i
        } else {
            int l, r;
            cin >> l >> r;
            cout << ft.range_sum(l, r) << "\n";
        }
    }
}
