#include <bits/stdc++.h>
using namespace std;

struct LiChao {
    struct Line {
        long long m, b;
        Line(long long _m=0, long long _b=LLONG_MAX) : m(_m), b(_b) {}
        long long value(long long x) const { return m*x + b; }
    };

    struct Node {
        Line line;
        Node *left = nullptr, *right = nullptr;
    };

    long long L, R;
    Node *root;

    LiChao(long long L=-1e12, long long R=1e12) : L(L), R(R) {
        root = new Node();
    }

    void addLine(Line newLine) { addLine(root, L, R, newLine); }

    void addLine(Node* &node, long long l, long long r, Line newLine) {
        if (!node) node = new Node();

        long long mid = (l + r) >> 1;

        bool leftBetter  = newLine.value(l)   < node->line.value(l);
        bool midBetter   = newLine.value(mid) < node->line.value(mid);

        if (midBetter) swap(newLine, node->line);

        if (r - l == 0) return;

        if (leftBetter != midBetter) {
            addLine(node->left, l, mid, newLine);
        } else {
            addLine(node->right, mid+1, r, newLine);
        }
    }

    long long query(long long x) { return query(root, L, R, x); }

    long long query(Node* node, long long l, long long r, long long x) {
        if (!node) return LLONG_MAX;
        long long res = node->line.value(x);
        long long mid = (l + r) >> 1;
        if (x <= mid) return min(res, query(node->left, l, mid, x));
        return min(res, query(node->right, mid+1, r, x));
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Example:
    // dp[i] = min(m[j] * x[i] + b[j])
    // Insert lines: y = mx + b
    // Query: min at x

    LiChao lc(-1e6, 1e6);

    lc.addLine({2, 3});    // y = 2x + 3
    lc.addLine({-1, 5});   // y = -1x + 5
    lc.addLine({3, -2});   // y = 3x - 2

    cout << lc.query(10) << "\n";  // min value at x = 10
    cout << lc.query(-5) << "\n";

    return 0;
}
