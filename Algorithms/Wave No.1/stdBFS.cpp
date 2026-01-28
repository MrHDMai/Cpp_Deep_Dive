#include<iostream>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

void bfs(int start, vector<vector<int>>& adj, vector<bool>& known){
    queue<int> q;
    q.push(start);
    known[start] = true;
    while(!q.empty()){
        int node = q.front();
        q.pop();
        cout << node << " ";
        for(auto& neighbor : adj[node]){
            if(!known[neighbor]){
                known[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    cout << endl;
}

int main(){

}

// 1. BFS marks on push
// Because the first discovery of a node guarantees the shortest path, and marking on push prevents duplicate queue entries.