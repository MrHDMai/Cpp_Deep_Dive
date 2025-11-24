#include <bits/stdc++.h>
using namespace std;

// Link-Cut Tree (splay-based) with point updates and path-sum queries.
struct LinkCut {
    struct Node {
        int ch[2] = {0,0}, p = 0;
        bool rev = false;
        long long val = 0;    // value at the vertex
        long long sum = 0;    // agg sum of subtree in aux tree
    };

    int n;
    vector<Node> t;

    LinkCut(int n=0): n(n), t(n+1) {}

    void init(int N) {
        n = N;
        t.assign(n+1, Node());
    }

    // helper
    bool isRoot(int x) {
        int p = t[x].p;
        if (!p) return true;
        return t[p].ch[0] != x && t[p].ch[1] != x;
    }

    void pushUp(int x) {
        t[x].sum = t[x].val;
        if (t[x].ch[0]) t[x].sum += t[t[x].ch[0]].sum;
        if (t[x].ch[1]) t[x].sum += t[t[x].ch[1]].sum;
    }

    void applyReverse(int x) {
        if (!x) return;
        t[x].rev ^= 1;
        swap(t[x].ch[0], t[x].ch[1]);
    }

    void pushDown(int x) {
        if (!x || !t[x].rev) return;
        if (t[x].ch[0]) applyReverse(t[x].ch[0]);
        if (t[x].ch[1]) applyReverse(t[x].ch[1]);
        t[x].rev = false;
    }

    // rotate x around its parent
    void rotate(int x) {
        int p = t[x].p;
        int g = t[p].p;
        int is_right = (t[p].ch[1] == x);
        int b = t[x].ch[is_right ^ 1];

        if (!isRoot(p)) {
            if (t[g].ch[0] == p) t[g].ch[0] = x;
            else if (t[g].ch[1] == p) t[g].ch[1] = x;
        }
        t[x].p = g;

        t[x].ch[is_right ^ 1] = p;
        t[p].p = x;

        t[p].ch[is_right] = b;
        if (b) t[b].p = p;

        pushUp(p);
        pushUp(x);
    }

    // splay x to be a child of goal (goal = 0 means root of aux tree)
    void splay(int x) {
        static vector<int> stk;
        stk.clear();
        int u = x;
        stk.push_back(u);
        while (!isRoot(u)) {
            u = t[u].p;
            stk.push_back(u);
        }
        // push down all ancestors so lazy flags are correct
        for (int i = (int)stk.size()-1; i >= 0; --i) pushDown(stk[i]);

        while (!isRoot(x)) {
            int p = t[x].p;
            int g = t[p].p;
            if (!isRoot(p)) {
                if ((t[p].ch[0] == x) ^ (t[g].ch[0] == p)) rotate(x);
                else rotate(p);
            }
            rotate(x);
        }
    }

    // expose/access: makes path root->x the preferred path and returns last accessed node
    int access(int x) {
        int last = 0;
        for (int y = x; y; y = t[y].p) {
            splay(y);
            t[y].ch[1] = last;
            pushUp(y);
            last = y;
        }
        splay(x);
        return last;
    }

    // make x the root of its represented tree
    void makeRoot(int x) {
        access(x);
        applyReverse(x);
        pushDown(x);
    }

    // find root of the tree containing x
    int findRoot(int x) {
        access(x);
        // go to leftmost node
        while (true) {
            pushDown(x);
            if (t[x].ch[0]) x = t[x].ch[0];
            else break;
        }
        splay(x);
        return x;
    }

    // check if u and v are connected
    bool connected(int u, int v) {
        if (u == v) return true;
        return findRoot(u) == findRoot(v);
    }

    // link u as child of v (connect u-v). Only valid if u and v are in different trees.
    bool link(int u, int v) {
        makeRoot(u);
        if (findRoot(v) == u) return false; // already connected
        t[u].p = v;
        return true;
    }

    // cut edge u-v if it exists
    bool cut(int u, int v) {
        makeRoot(u);
        access(v);
        // after access(v), v is root of aux tree and its left child should be u if edge exists
        if (t[v].ch[0] != u || t[u].ch[1] != 0) return false;
        t[v].ch[0] = 0;
        t[u].p = 0;
        pushUp(v);
        return true;
    }

    // set node u's value
    void updateValue(int u, long long value) {
        access(u);
        t[u].val = value;
        pushUp(u);
    }

    // query sum on path u-v
    long long pathSum(int u, int v) {
        makeRoot(u);
        access(v);
        return t[v].sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    // Input format:
    // n q
    // n values (1..n)
    // then q lines, each operation:
    // "link u v" : connect u v
    // "cut u v"  : cut edge u v
    // "conn u v" : print 1 if connected else 0
    // "set u x"  : set node u value to x
    // "sum u v"  : print path sum u..v
    //
    // nodes are 1-based.

    if (!(cin >> n >> q)) return 0;
    LinkCut lc(n);
    for (int i = 1; i <= n; ++i) {
        long long val;
        cin >> val;
        lc.t[i].val = val;
        lc.t[i].sum = val;
    }

    while (q--) {
        string op;
        cin >> op;
        if (op == "link") {
            int u, v; cin >> u >> v;
            bool ok = lc.link(u, v);
            cout << (ok ? "linked\n" : "already-connected\n");
        } else if (op == "cut") {
            int u, v; cin >> u >> v;
            bool ok = lc.cut(u, v);
            cout << (ok ? "cut\n" : "no-edge\n");
        } else if (op == "conn") {
            int u, v; cin >> u >> v;
            cout << (lc.connected(u, v) ? "1\n" : "0\n");
        } else if (op == "set") {
            int u; long long x; cin >> u >> x;
            lc.updateValue(u, x);
            cout << "ok\n";
        } else if (op == "sum") {
            int u, v; cin >> u >> v;
            cout << lc.pathSum(u, v) << "\n";
        } else {
            // unknown op
            string rest;
            getline(cin, rest);
            cout << "unknown-op\n";
        }
    }
    return 0;
}
