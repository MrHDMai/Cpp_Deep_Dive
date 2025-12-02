#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node *left, *right;

    Node(int v = 0, Node* l = nullptr, Node* r = nullptr)
        : val(v), left(l), right(r) {}
};

const int MAXN = 200000;
Node* version[MAXN];  // store roots of versions

Node* build(int l, int r) {
    if (l == r) return new Node();
    int mid = (l + r) / 2;
    return new Node(0, build(l, mid), build(mid + 1, r));
}

// create a new version with arr[pos] = value
Node* update(Node* prev, int l, int r, int pos, int value) {
    if (l == r) {
        return new Node(prev->val + value);   // persistent behavior
    }
    int mid = (l + r) / 2;

    if (pos <= mid) {
        return new Node(prev->val + value,
                        update(prev->left, l, mid, pos, value),
                        prev->right);
    } else {
        return new Node(prev->val + value,
                        prev->left,
                        update(prev->right, mid + 1, r, pos, value));
    }
}

// query sum[l..r] using two versions
int query(Node* rVer, Node* lVer, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return 0;
    if (ql <= l && r <= qr)
        return rVer->val - lVer->val;
    
    int mid = (l + r) / 2;
    return query(rVer->left, lVer->left, l, mid, ql, qr) +
           query(rVer->right, lVer->right, mid + 1, r, ql, qr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    version[0] = build(1, n);

    for (int i = 1; i <= n; i++) {
        // update version[i-1] at position arr[i] by +1
        version[i] = update(version[i - 1], 1, n, arr[i], 1);
    }

    int q;
    cin >> q;
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;

        // count of numbers equal to x in [l, r]
        int result = query(version[r], version[l - 1], 1, n, x, x);
        cout << result << '\n';
    }
    return 0;
}
