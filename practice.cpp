#include<iostream>
#include<vector>
#include<queue>
#include<limits>

using namespace std;

typedef pair<int,int> node_dist;

class graph{
    int vertices;
    vector<vector<node_dist>> adj;
public:
    graph(int vertices) : vertices(vertices), adj(vertices){};
    void addedges(int u, int v, int w);
    void dijkstra(int src);
};

void graph :: addedges(int u, int v, int w){
    adj[u].emplace_back(v,w);
    adj[v].emplace_back(u,w);
};

void graph :: dijkstra(int src){ 
    priority_queue <node_dist, vector<node_dist>, greater<node_dist>> pq;
    vector<int> dist(vertices,numeric_limits<int>::max());
    pq.push({0,src});
    dist[src] = 0;
    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();
        for(auto& neighbor : adj[u]){
            int v = neighbor.first;
            int weight = neighbor.second;
            if(dist[v] > dist[u] + weight){
                dist[v] = dist[u] + weight;
                pq.push({dist[v],v});
            }
        }
    }
    for(int i = 0; i < vertices; i++){
        if(i < numeric_limits<int>::max()){
            cout << "The distance from " << i << " is " << dist[i] << endl;
        } else {
            cout << "The distance to " << i << " is impossible";
        }
    }
}


int main(){
    int n, m, u,w,v;
    cin >> n,m;
    graph g(n);
    cout << "enter the edges of the graph (u, v, w)";
    cin >> u >> v >> w;
    for(int i = 0; i < m; i++){
        g.addegdes(u,v,w);
    }
    int src;
    cout << "Enter the src" << endl;
    cin >> src;
    g.dijkstra(int src);
}