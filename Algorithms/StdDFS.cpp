#include<iostream>
#include<vector>

using namespace std;

void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited){
    visited[node] = true;
    cout << node << " ";

    for(int neighbor : adj[node]){
        if(!visited[neighbor]){
            dfs(neighbor,adj,visited);
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
    vector<bool> visited(vertices,false);
    cout << "DFS traversal: \n";
    for(int i = 0; i < vertices; i++){
        if(!visited[i]){
            dfs(i, adj,visited);
        }
    }
    return 0;
}