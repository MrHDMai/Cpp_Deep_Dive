#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node {
    Node* next;
    Node* prev;
    int value;
    int key;
    Node(Node* p, Node* n, int k, int val) : prev(p), next(n), key(k), value(val) {};
    Node(int k, int val) : prev(NULL), next(NULL), key(k), value(val) {};
};

class Cache {
protected:
    map<int, Node*> mp;
    int cp;
    Node* tail;
    Node* head;
    virtual void set(int, int) = 0;
    virtual int get(int) = 0;
};

class LRUCache : public Cache {
public:
    LRUCache(int capacity) {
        cp = capacity;
        head = NULL;
        tail = NULL;
    }

    void set(int key, int value) override {
        if (mp.find(key) != mp.end()) {
            mp[key]->value = value;
            moveToHead(mp[key]);
        } else {
            if (mp.size() == cp) {
                if (tail) {
                    Node* toDelete = tail;
                    mp.erase(toDelete->key);
                    removeNode(toDelete);
                    delete toDelete;
                }
            }
            Node* newNode = new Node(key, value);
            addToHead(newNode);
            mp[key] = newNode;
        }
    }

    int get(int key) override {
        if (mp.find(key) == mp.end()) {
            return -1;
        }
        moveToHead(mp[key]);
        return mp[key]->value;
    }

private:
    void addToHead(Node* node) {
        node->prev = NULL;
        node->next = head;
        if (head) {
            head->prev = node;
        }
        head = node;
        if (tail == NULL) {
            tail = node;
        }
    }

    void removeNode(Node* node) {
        if (node->prev) {
            node->prev->next = node->next;
        } else {
            head = node->next;
        }
        if (node->next) {
            node->next->prev = node->prev;
        } else {
            tail = node->prev;
        }
    }

    void moveToHead(Node* node) {
        if (node == head) 
            return;
        removeNode(node);
        addToHead(node);
    }
};

int main() {
    int n, capacity, i;
    cin >> n >> capacity;
    LRUCache l(capacity);
    for (i = 0; i < n; i++) {
        string command;
        cin >> command;
        if (command == "get") {
            int key;
            cin >> key;
            cout << l.get(key) << endl;
        } else if (command == "set") {
            int key, value;
            cin >> key >> value;
            l.set(key, value);
        }
    }
    return 0;
}