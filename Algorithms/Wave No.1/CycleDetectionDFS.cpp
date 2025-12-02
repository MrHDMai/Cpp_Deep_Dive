#include<iostream>
#include<vector>

using namespace std;
//Implementation with a directed graph
class graph{
    int vertices;
    vector<vector<int>> adj;

    bool dfs(int v, vector<bool>& visited, vector<bool>& recstack){
        visited[v] = true;
        recstack[v] = true;

        for(auto neighbor : adj[v]){
            if(!visited[neighbor] && dfs(neighbor, visited, recstack))
                return true;
            else if(recstack[neighbor])
                return true;
        }
        recstack[v] = false;
        return false;
    }
public:
    graph(int vertices) : vertices(vertices), adj(vertices){}
    void addedges(int u, int v){
        adj[u].push_back(v);
    }
    bool hascycle(){
        vector<bool> visited(vertices, false);
        vector<bool> recstack(vertices, false);

        for(int i = 0; i < vertices; i++)
            if(!visited[i] && dfs(i, visited, recstack))
                return true;
        return false;
    }
}; 

//Implementation with undirected graph
class unionfind{
    vector<int> parent, rank;
public:
    unionfind(int n){
        parent.resize(n);
        rank.assign(n,0);
        for(int i = 0; i < n; i++)
            parent[i] = i;
    }
    int find(int x){
        if(parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unionsets(int x, int y){
        int xr = find(x), yr = find(y);
        if(xr == yr)
            return false;
        if(rank[xr] < rank[yr])
            parent[xr] = yr;
        else if(rank[xr] > rank[yr])
            parent[yr] = xr;
        else{
            parent[yr] = xr;
            rank[xr]++;
        }
        return true;
    }
};

bool hasCycle(int V, const vector<pair<int,int>>& edges){
    unionfind uf(V);
    for(auto& [u,v] : edges){
        if(!uf.unionsets(u,v))
            return true;
    }
    return false;
}

int  main(){
    graph g(4);
    g.addedges(0,1);
    g.addedges(1,2);
    g.addedges(2,0);
    g.addedges(2,3);

    cout << (g.hascycle() ? "Cycle deteced" : "No Cycle") << endl;
    printf("----------------------------------------\n");
    int V = 4;
    vector<pair<int,int>> edges = {
        {0,1},{1,2},{2,3},{3,0}
    };
    cout << (hasCycle(V,edges) ? "Cycle Deteced" : "No Cycle") << endl;

    return 0; 
}