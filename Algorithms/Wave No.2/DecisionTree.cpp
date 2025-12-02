#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<cmath>
#include<tuple>

using namespace std;

struct node{
    int featIndex = -1;
    string label = "";
    string condition = "";
    node* left = nullptr;
    node* right = nullptr;

    ~node(){
        delete left;
        delete right;
    }
};

double entropy(const vector<string>& labels){
    unordered_map<string,int> freq;
    for(const auto& label : labels)
        freq[label]++;
    double e = 0.0;
    for(const auto& [label,count]:freq){
        double p = (double)count/labels.size();
        e -= p* log2(p);
    }
    return e;
}

pair<vector<int>,vector<int>> split(const vector<vector<string>>& data, int col, const string& value){
    vector<int> leftindex,rightindex;
    for(int i = 0;  i < data.size(); i++){
        if(data[i][col] == value)
            leftindex.push_back(i);
        else
            rightindex.push_back(i);
    }
    return {leftindex,rightindex};
}

tuple<int,string,double> bestsplit(const vector<vector<string>>& data, const vector<string>& labels){
    int bestcol = -1;
    string bestval;
    double bestgain = -1;
    double baseentropy = entropy(labels);
    int numfeatures = data[0].size();
    for(int col = 0; col < numfeatures; col++){
        unordered_set<string> values;
        for(const auto& row : data)
            values.insert(row[col]);
        for(const auto& val : values){
            auto[leftindex,rightindex] = split(data,col,val);
            if(leftindex.empty()||rightindex.empty()) continue;

            vector<string> leftlabels, rightlabels;
            for(int i : leftindex) leftlabels.push_back(labels[i]);
            for(int i : rightindex) rightlabels.push_back(labels[i]);

            double p = (double)leftlabels.size()/labels.size();
            double infogain = baseentropy - (p * entropy(leftlabels) + (1 - p) * entropy(rightlabels));
            if(infogain > bestgain){
                bestgain = infogain;
                bestcol = col;
                bestval = val;
            }
        }
    } 
    return {bestcol, bestval, bestgain};
}

node* buildtree(const vector<vector<string>>& data, const vector<string>& labels){
    unordered_map<string, int> freq;
    for(const auto& l : labels) freq[l]++;
    if(freq.size() == 1){
        return new node{-1,labels[0]};
    }
    auto [bestcol, bestval, gain] = bestsplit(data, labels);
    if(gain <= 0){
        string majority;
        int maxcount = 0;
        for(auto& [label, count] : freq){
            if(count > maxcount){
                majority = label;
                maxcount = count;
            }
        }
        return new node{-1, majority};
    }
    auto[leftindex,rightindex] = split(data, bestcol, bestval);
    vector<vector<string>> leftdata, rightdata;
    vector<string> leftlabels, rightlabels;
    for(auto i : leftindex){
        leftdata.push_back(data[i]);
        leftlabels.push_back(labels[i]);
    }
    for(int i : rightindex){
        rightdata.push_back(data[i]);
        rightlabels.push_back(labels[i]);
    }
    node* Node = new node{bestcol, "", bestval};
    Node->left = buildtree(leftdata, leftlabels);
    Node->right = buildtree(rightdata,rightlabels);
    return Node;
}

string predict(node* root, const vector<string>& sample){
    while(root -> featIndex != -1){
        if(sample[root->featIndex] == root->condition)
            root = root->left;
        else 
            root = root->right;
    }
    return root->label;
}

void printTree(node* root, int depth = 0) {
    if (!root) return;
    for (int i = 0; i < depth; ++i) cout << "  ";
    if (root->featIndex == -1) {
        cout << "Label: " << root->label << endl;
    } else {
        cout << "Feature[" << root->featIndex << "] == " << root->condition << "?" << endl;
        printTree(root->left, depth + 1);
        printTree(root->right, depth + 1);
    }
}



int main(){
    vector<vector<string>> data = {
        {"sunny","hot","high", "FALSE"},
        {"sunny","hot","high", "TRUE"},
        {"overcase","hot","high", "FALSE"},
        {"rainy","mild","high", "FALSE"},
        {"sunny","cool","normal", "FALSE"},
        {"rainy","cool","normal", "TRUE"},
        {"overcast","cool","normal", "TRUE"},
        {"sunny","mild","high", "FALSE"},
        {"sunny","cool","normal", "FALSE"},

    };
    vector<string> labels = {
        "no","no","yes","yes","yes","no","yes","no","yes"
    };
    node* root = buildtree(data,labels);
    vector<string> test{"sunny","cool","normal","TRUE"};
    cout << "Prediction: " << predict(root,test) << endl;
    printTree(root);
    delete root;
    return 0;
}
