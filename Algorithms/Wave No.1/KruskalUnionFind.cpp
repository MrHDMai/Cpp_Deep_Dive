#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct edge{
    int u, v, wt;
    bool operator<(const edge& other) const{
        return wt < other.wt;
    }
}; 

struct DSU{
    vector<int> parent, rank;
    DSU(int n){
        parent.resize(n); rank.resize(n,0);
        for(int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int X){
        if(X!=parent[X])
            parent[X] = find(parent[X]);
        return parent[X];
    }
    bool unite(int x, int y){
        int xr = find(x), yr = find(y);
        if(xr == yr) return false;
        if(rank[xr] < rank[yr]) parent[xr] = yr;
        else if(rank[xr] > rank[yr]) parent[yr] = xr;
        else{
            parent[yr] = xr;
            rank[xr]++;
        }
        return true;
    }
}; 

void kruskalMST(int V, vector<edge>& edg){
    sort(edg.begin(), edg.end());
    DSU dsu(V);
    int mst_cost = 0;
    for(auto& e : edg){
        if(dsu.unite(e.u, e.v)){
            mst_cost += e.wt;
        }
    }
    cout << "Total MST cost: " << mst_cost << endl;
}

int main(){
    int V = 5;
    vector<edge> edg;
    edg.push_back({0,1,2});
    edg.push_back({0,3,6});
    edg.push_back({1,2,3});
    edg.push_back({1,3,8});
    edg.push_back({1,4,5});
    edg.push_back({2,4,7});
    kruskalMST(V,edg); 
    return 0;

}