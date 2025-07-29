#include<iostream>
#include<vector>
#include<stack>
using namespace std;


//standard implementation using stack - simple to understand when clarity matters and the graph size is manageable
void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited){
    visited[node] = true;
    cout << node << " ";

    for(int neighbor : adj[node]){
        if(!visited[neighbor]){
            dfs(neighbor,adj,visited);
        }
    }
}

void dfsIterative(int start, vector<vector<int>>& adj, vector<bool>& visited) {
    stack<int> stk;
    stk.push(start);

    while (!stk.empty()) {
        int node = stk.top();
        stk.pop();

        if (visited[node]) continue;

        visited[node] = true;
        cout << node << " ";  // Process the node

        // To mimic recursive DFS order, reverse the neighbors when pushing
        for (int i = adj[node].size() - 1; i >= 0; --i) {
            int neighbor = adj[node][i];
            if (!visited[neighbor]) {
                stk.push(neighbor);
            }
        }
    }
}

int main(){
    int vertices, edges;
    cout << "Enter number of vertices and edges: ";
    cin>> vertices >> edges;
    vector<vector<int>> adj(vertices);
    cout << "Enter " << edges << " edges (u v pairs): \n";
    for(int i = 0; i < edges; i++){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<bool> visited_recursive(vertices, false);
    vector<bool> visited_iterative(vertices, false);

    cout << "\nRecursive DFS traversal:\n";
    for (int i = 0; i < vertices; i++) {
        if (!visited_recursive[i]) {
            dfs(i, adj, visited_recursive);
        }
    }

    cout << "\n\nIterative DFS traversal:\n";
    for (int i = 0; i < vertices; i++) {
        if (!visited_iterative[i]) {
            dfsIterative(i, adj, visited_iterative);
        }
    }
    return 0;
}