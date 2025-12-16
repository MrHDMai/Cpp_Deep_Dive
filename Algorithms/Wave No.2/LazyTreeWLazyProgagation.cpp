#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;

struct SegmentTree {
    int n;
    vector<long long> tree;

    SegmentTree(int n) : n(n), tree(4 * n, 0) {}

    void build(const vector<long long>& a, int v, int l, int r) {
        if (l == r) {
            tree[v] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(a, v * 2, l, mid);
        build(a, v * 2 + 1, mid + 1, r);
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }

    void update(int v, int l, int r, int pos, long long val) {
        if (l == r) {
            tree[v] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid)
            update(v * 2, l, mid, pos, val);
        else
            update(v * 2 + 1, mid + 1, r, pos, val);
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }

    long long query(int v, int l, int r, int ql, int qr) const {
        if (qr < l || r < ql)
            return 0;
        if (ql <= l && r <= qr)
            return tree[v];
        int mid = (l + r) / 2;
        return query(v * 2, l, mid, ql, qr) +
               query(v * 2 + 1, mid + 1, r, ql, qr);
    }
};

int main() {
    int n, q;
    cin >> n >> q;

    vector<long long> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    SegmentTree st(n);
    st.build(a, 1, 0, n - 1);

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int pos;
            long long val;
            cin >> pos >> val;
            st.update(1, 0, n - 1, pos, val);
        } else {
            int l, r;
            cin >> l >> r;
            cout << st.query(1, 0, n - 1, l, r) << "\n";
        }
    }

    return 0;
}
