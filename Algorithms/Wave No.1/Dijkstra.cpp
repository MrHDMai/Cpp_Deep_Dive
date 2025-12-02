#include<iostream>
#include<limits>
#include<cmath>
#include<queue>
#include<vector>

using namespace std;

typedef pair<int,int> node_dist;

class graph{
    int vertices;
    vector<vector<node_dist>> adj_list;
public:
    graph(int vertices) : vertices(vertices), adj_list(vertices) {};
    void addedges(int u, int v, int w);
    void dijkstra(int src);
};

void graph::addedges(int u, int v, int w){
    adj_list[u].emplace_back(v,w);
    adj_list[v].emplace_back(u,w);
}

void graph::dijkstra(int src){
    priority_queue<node_dist, vector<node_dist>, greater<node_dist>> pq;
    vector<int> dist(vertices, numeric_limits<int>::max());
    pq.push({0,src});
    dist[src] = 0;
    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();
        for(auto& neighbor : adj_list[u]){
            int v = neighbor.first;
            int weight = neighbor.second;
            if(dist[v] > dist[u] + weight){
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    for(int i = 0; i < vertices; i++){
        if(dist[i] < numeric_limits<int>::max()){
            cout << "Distance from " << src << " to " << i << " is " << dist[i] << endl;
        } else {
            cout << "No path from " << src << " to " << i << endl;
        }
    }
}


int main(){
    int n, m, u, v, w;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;
    graph g(n);
    cout << "Enter edges (u v w):" << endl;
    for(int i = 0; i < m; i++){
        cin >> u >> v >> w;
        g.addedges(u, v, w);
    }
    int src;
    cout << "Enter source vertex: ";
    cin >> src;
    g.dijkstra(src);
    return 0;
}