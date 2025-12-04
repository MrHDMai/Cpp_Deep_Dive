#include<bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node *left, *right;
    Node(int v = 0, Node* l = nullptr, Node* r = nullptr)
        : val(v), left(l), right(r) {}
};

const int MAXN = 200000;
Node* version[MAXN];

Node* build(int l, int r) {
    if (l == r) return new Node();
    int mid = (l + r) / 2;
    return new Node(0, build(l, mid), build(mid + 1, r));
}

Node* update(Node* prev, int l, int r, int pos) {
    if (l == r)
        return new Node(prev->val + 1);

    int mid = (l + r) / 2;

    if (pos <= mid)
        return new Node(prev->val + 1,
                        update(prev->left, l, mid, pos),
                        prev->right);
    else
        return new Node(prev->val + 1,
                        prev->left,
                        update(prev->right, mid + 1, r, pos));
}

int kthSmallest(Node* R, Node* L, int l, int r, int k) {
    if (l == r) return l;

    int mid = (l + r) / 2;
    int leftCount = R->left->val - L->left->val;

    if (k <= leftCount)
        return kthSmallest(R->left, L->left, l, mid, k);
    else
        return kthSmallest(R->right, L->right, mid + 1, r, k - leftCount);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> arr(n + 1), comp;

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        comp.push_back(arr[i]);
    }

    // Coordinate compression
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    int m = comp.size();

    auto getID = [&](int x) {
        return int(lower_bound(comp.begin(), comp.end(), x) - comp.begin()) + 1;
    };

    // Version 0 is an empty tree
    version[0] = build(1, m);

    // Build persistent trees
    for (int i = 1; i <= n; i++) {
        int id = getID(arr[i]);
        version[i] = update(version[i - 1], 1, m, id);
    }

    // Process queries
    while (q--) {
        int L, R, k;
        cin >> L >> R >> k;

        int len = R - L + 1;
        int kth_small = len - k + 1;  // convert to kth smallest

        int idx = kthSmallest(version[R], version[L - 1], 1, m, kth_small);
        cout << comp[idx - 1] << "\n";
    }
}
