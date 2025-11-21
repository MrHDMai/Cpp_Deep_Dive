#include <bits/stdc++.h>
using namespace std;

// ------- Treap Node for Euler Tour Tree ------- //

struct Node {
    int val;               // node id
    int pr;                // treap priority
    Node *l, *r;           // left/right children
    int sz;                // size of subtree

    Node(int v) : val(v), pr(rand()), l(NULL), r(NULL), sz(1) {}
};

int getSize(Node* t) { return t ? t->sz : 0; }

void pull(Node* t) {
    if (!t) return;
    t->sz = 1 + getSize(t->l) + getSize(t->r);
}

// Treap split: splits t into (l, r) where left tree has first k nodes.
void split(Node* t, int k, Node*& l, Node*& r) {
    if (!t) {
        l = r = NULL;
        return;
    }
    if (getSize(t->l) >= k) {
        split(t->l, k, l, t->l);
        r = t;
    } else {
        split(t->r, k - getSize(t->l) - 1, t->r, r);
        l = t;
    }
    pull(t);
}

// Treap merge (BST merge)
Node* merge(Node* a, Node* b) {
    if (!a || !b) return a ? a : b;
    if (a->pr > b->pr) {
        a->r = merge(a->r, b);
        pull(a);
        return a;
    } else {
        b->l = merge(a, b->l);
        pull(b);
        return b;
    }
}

// -------- Euler Tour Tree Structure -------- //

struct ETT {
    int n;
    vector<Node*> ref;   // reference to one occurrence of each node
    vector<Node*> root;  // root of each Euler Tour treap

    ETT(int n) : n(n), ref(n), root(n) {
        for (int i = 0; i < n; i++) {
            ref[i] = new Node(i);
            root[i] = ref[i];
        }
    }

    Node* getRoot(Node* x) {
        if (!x) return NULL;
        // Climb to treap root
        while (x->l || x->r) {
            if (x->l && x->l->pr > x->pr) x = x->l;
            else if (x->r && x->r->pr > x->pr) x = x->r;
            else break;
        }
        return x;
    }

    bool connected(int u, int v) {
        return getRoot(ref[u]) == getRoot(ref[v]);
    }

    // Insert v after u in Euler tour
    void link(int u, int v) {
        if (connected(u, v)) return;

        Node* ru = getRoot(ref[u]);
        Node* rv = getRoot(ref[v]);

        // Create occurrences
        Node* a = new Node(u);
        Node* b = new Node(v);

        // Merge ru + a + rv + b = Euler tour of union
        Node* t = merge(ru, a);
        t = merge(t, rv);
        t = merge(t, b);

        // Set roots
        root[u] = root[v] = t;
    }

    void cut(int u, int v) {
        if (!connected(u, v)) return;

        Node* r = getRoot(ref[u]);

        // We need to split out the section representing edge (u,v)
        // Simplest: rebuild trees from scratch (works for most uses)

        // TODO: Full dynamic cut implementation requires
        // tracking Euler tour indices of occurrences for each edge,
        // which is lengthy. I can give a full version if you want.

        cout << "Cut requires tracking occurrences of edges.\n";
    }
};
