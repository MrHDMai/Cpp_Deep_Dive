#include<iostream>
#include<vector>
#include<stack>
using namespace std;


void dfs(int node, vector<vector<int>>& adj, vector<bool>& known){
    known[node] = true;
    cout << node << " " << endl;
    for(auto& neighbor : adj[node]){
        if(!known[neighbor])
            dfs(neighbor, adj, known);
    }
}
//known -> check for unknown -> check using recurssion

void dfsIT(int start,vector<vector<int>>& adj, vector<bool>& known){
    stack<int> sk;
    sk.push(start);
    while(!sk.empty()){
        int node = sk.top();
        sk.pop();
        cout << node << " ";
        if(known[node]) continue;
        known[node] = true;
        for(int i = adj[node].size() - 1; i >= 0; i--){
            int neighbor = adj[node][i];
            if(!known[neighbor])
                sk.push(neighbor);
        }
    }
}


// -> create stack (filo) -> pop -> check -> mark -> manually recursed and push

// 2. DFS-IT marks on pop
// Because popping corresponds to entering a node, mirroring recursive DFS call behavior.

// 3. Marking DFS-IT on push
// Breaks recursive equivalence and can skip valid paths or alter traversal structure.

// 4. Reverse neighbors
// To preserve the same visitation order as recursive DFS due to stack LIFO behavior.


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