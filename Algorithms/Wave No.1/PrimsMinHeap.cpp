#include<iostream>
#include<vector>
#include<queue>
using namespace std;

const int INF = 1e9;

typedef pair<int,int> pii;

void primMST(int V, vector<vector<pii>>& adj){
    vector<bool> intMST(V, false);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    vector<int> key(V,INF);
    key[0] = 0;
    pq.push({0,0});
    int mst_const = 0;
    while(!pq.empty()){
        int u = pq.top().second;
        int wt = pq.top().first;
        pq.pop();
        if(intMST[u]) continue;
        intMST[u] = true;
        mst_const += wt; 

        for(auto& [v,w] : adj[u]){
            if(!intMST[v] && w < key[v]){
                key[v] = w;
                pq.push({w,v});
            }
        }
    }
    cout << "Total MST cost: " << mst_const << endl;
}

int main(){
    int V = 5;
    vector<vector<pair<int,int>>> adj(V);
    adj[0].push_back({1,2});
    adj[1].push_back({0,2});

    adj[0].push_back({3,6});
    adj[3].push_back({0,6});

    adj[1].push_back({2,3});
    adj[2].push_back({1,3});

    adj[1].push_back({3,8});
    adj[3].push_back({1,8});

    adj[1].push_back({4,5});
    adj[4].push_back({1,5});

    adj[2].push_back({4,7});
    adj[4].push_back({2,7});

    primMST(V,adj);
}