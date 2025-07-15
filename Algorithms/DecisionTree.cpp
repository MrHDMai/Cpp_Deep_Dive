#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <tuple>

using namespace std;

// Node structure for the decision tree
struct Node {
    int featureIndex = -1;
    string label = "";
    string condition = "";
    Node* left = nullptr;
    Node* right = nullptr;

    ~Node() {
        delete left;
        delete right;
    }
};

// Compute entropy of a label vector
double entropy(const vector<string>& labels) {
    unordered_map<string, int> freq;
    for (const auto& label : labels)
        freq[label]++;

    double e = 0.0;
    for (const auto& [label, count] : freq) {
        double p = (double)count / labels.size();
        e -= p * log2(p);
    }
    return e;
}

// Split the data into two groups based on feature value
pair<vector<int>, vector<int>> split(const vector<vector<string>>& data, int col, const string& value) {
    vector<int> leftIdx, rightIdx;
    for (int i = 0; i < data.size(); ++i) {
        if (data[i][col] == value)
            leftIdx.push_back(i);
        else
            rightIdx.push_back(i);
    }
    return {leftIdx, rightIdx};
}

// Find the best split based on information gain
tuple<int, string, double> bestSplit(const vector<vector<string>>& data, const vector<string>& labels) {
    int bestCol = -1;
    string bestVal;
    double bestGain = -1;
    double baseEntropy = entropy(labels);
    int numFeatures = data[0].size();

    for (int col = 0; col < numFeatures; ++col) {
        unordered_set<string> values;
        for (const auto& row : data)
            values.insert(row[col]);

        for (const auto& val : values) {
            auto [leftIdx, rightIdx] = split(data, col, val);
            if (leftIdx.empty() || rightIdx.empty()) continue;

            vector<string> leftLabels, rightLabels;
            for (int i : leftIdx) leftLabels.push_back(labels[i]);
            for (int i : rightIdx) rightLabels.push_back(labels[i]);

            double p = (double)leftLabels.size() / labels.size();
            double infoGain = baseEntropy - (p * entropy(leftLabels) + (1 - p) * entropy(rightLabels));

            if (infoGain > bestGain) {
                bestGain = infoGain;
                bestCol = col;
                bestVal = val;
            }
        }
    }

    return {bestCol, bestVal, bestGain};
}

// Recursively build the decision tree
Node* buildTree(const vector<vector<string>>& data, const vector<string>& labels) {
    unordered_map<string, int> freq;
    for (const auto& l : labels) freq[l]++;

    if (freq.size() == 1) {
        return new Node{-1, labels[0]};
    }

    auto [bestCol, bestVal, gain] = bestSplit(data, labels);
    if (gain <= 0) {
        string majority;
        int maxCount = 0;
        for (auto& [label, count] : freq)
            if (count > maxCount) tie(majority, maxCount) = {label, count};
        return new Node{-1, majority};
    }

    auto [leftIdx, rightIdx] = split(data, bestCol, bestVal);
    vector<vector<string>> leftData, rightData;
    vector<string> leftLabels, rightLabels;

    for (int i : leftIdx) {
        leftData.push_back(data[i]);
        leftLabels.push_back(labels[i]);
    }
    for (int i : rightIdx) {
        rightData.push_back(data[i]);
        rightLabels.push_back(labels[i]);
    }

    Node* node = new Node{bestCol, "", bestVal};
    node->left = buildTree(leftData, leftLabels);
    node->right = buildTree(rightData, rightLabels);
    return node;
}

// Predict the label for a sample
string predict(Node* root, const vector<string>& sample) {
    while (root->featureIndex != -1) {
        if (sample[root->featureIndex] == root->condition)
            root = root->left;
        else
            root = root->right;
    }
    return root->label;
}

int main() {
    vector<vector<string>> data = {
        {"sunny", "hot", "high", "FALSE"},
        {"sunny", "hot", "high", "TRUE"},
        {"overcast", "hot", "high", "FALSE"},
        {"rainy", "mild", "high", "FALSE"},
        {"rainy", "cool", "normal", "FALSE"},
        {"rainy", "cool", "normal", "TRUE"},
        {"overcast", "cool", "normal", "TRUE"},
        {"sunny", "mild", "high", "FALSE"},
        {"sunny", "cool", "normal", "FALSE"},
    };

    vector<string> labels = {
        "no", "no", "yes", "yes", "yes", "no", "yes", "no", "yes"
    };

    Node* root = buildTree(data, labels);

    vector<string> test = {"sunny", "cool", "normal", "TRUE"};
    cout << "Prediction: " << predict(root, test) << endl;

    delete root;
    return 0;
}
