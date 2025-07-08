#include<iostream>
#include<vector>
#include<queue>

using namespace std;

void bfs(int start, const vector<vector<int>>& adjlist, vector<bool>& visited){
    queue<int> q;
    q.push(start);
    visited[start] = true;

    cout << "bfs traversal starting from node: " << start << ": ";

    while(q.empty()){
        int node = q.front();
        q.pop();
        cout << node << " ";

        for(int neighbor : adjlist[node]){
            if(!visited[neighbor]){
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    cout << endl;
}

int main(){
    int vertices, edges;
    cout << "Enter number of vertices and edges: ";
    cin >> vertices >> edges;
    vector<vector<int>> adjlist(vertices);
    cout <<"Enter " << edges << "edges(u v pairs): \n";
    for(int i = 0; i < edges; i++){
        int u, v;
        cin >> u >> v;
        adjlist[u].push_back(v);
        adjlist[v].push_back(u);
    }
    vector<bool> visited(vertices, false);
    int startnode; 
    cout << " Enter the start node for BFS: ";
    cin >> startnode;
    bfs(startnode, adjlist, visited);
    return 0; 
}