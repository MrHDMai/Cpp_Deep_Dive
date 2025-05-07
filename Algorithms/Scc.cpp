/*This is an implementatino of Strongest Correlated Components*/
#include<iostream>
#include<vector>
#include<limits>
#include<stack>
#include<cmath>

using namespace std;

class graph{
    int vertices;
    vector<vector<int>> adj;
public:
    graph(int vertices) : vertices(vertices), adj(vertices){};
    void addedges(int u, int v);
    void dfs(int v, vector<bool>& visited, stack<int>& stk);
    void transpose();
    void dfs2(int v, vector<bool>& visited);
    void scc();
};

void graph::addedges(int u, int v){
    adj[u].emplace_back(v);
}

int main(){

}