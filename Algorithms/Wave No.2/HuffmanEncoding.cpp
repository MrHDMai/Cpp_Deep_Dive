#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>

using namespace std;

// Tree node
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {}
};

// Comparator for min-heap
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Recursive function to build Huffman codes
void buildCodes(Node* root, string code, unordered_map<char, string>& huffmanCode) {
    if (!root) return;

    // Leaf node
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = code;
    }

    buildCodes(root->left, code + "0", huffmanCode);
    buildCodes(root->right, code + "1", huffmanCode);
}

// Free memory
void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// Main Huffman encoding function
void huffmanEncode(const string& text) {
    // Step 1: Count frequency of each character
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    // Step 2: Create a priority queue (min-heap)
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto& pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    // Step 3: Build the Huffman tree
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;

        pq.push(merged);
    }

    // Root of Huffman Tree
    Node* root = pq.top();

    // Step 4: Generate Huffman codes
    unordered_map<char, string> huffmanCode;
    buildCodes(root, "", huffmanCode);

    // Step 5: Print codes
    cout << "Huffman Codes:\n";
    for (auto& pair : huffmanCode) {
        cout << pair.first << ": " << pair.second << '\n';
    }

    // Step 6: Encode the input
    string encoded = "";
    for (char ch : text) {
        encoded += huffmanCode[ch];
    }

    cout << "\nEncoded Text:\n" << encoded << '\n';

    // Optional: decode example
    cout << "\nDecoded Text:\n";
    Node* current = root;
    for (char bit : encoded) {
        current = (bit == '0') ? current->left : current->right;
        if (!current->left && !current->right) {
            cout << current->ch;
            current = root;
        }
    }

    // Step 7: Clean up
    freeTree(root);
}

int main() {
    string text = "hello huffman";
    huffmanEncode(text);
    return 0;
}
