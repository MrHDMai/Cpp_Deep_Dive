/*This is an implementatino of Strongest Correlated Components*/
#include<iostream>
#include<vector>
#include<limits>
#include<stack>
#include<cmath>

using namespace std;

class graph{
    int vertices;
    vector<vector<int>> adj;
public:
    graph(int vertices) : vertices(vertices), adj(vertices){};
    void addedges(int u, int v);
    void dfs(int v, vector<bool>& visited, stack<int>& stk);
    graph transpose();
    void dfs2(int v, vector<bool>& visited);
    void scc();
};

void graph::addedges(int u, int v){
    adj[u].emplace_back(v);
}

void graph::dfs(int v, vector<bool>& known, stack<int>& filo){
    known[v] = true;
    for(auto& neighbors : adj[v]){
        if(!known[neighbors]){
            dfs(neighbors,known,filo);
        }
    }
    filo.push(v);
}

graph graph::transpose(){
    graph transpose(vertices);
    for(int v = 0; v < vertices; ++v){
        for(auto& neighbor : adj[v]){
                transpose.addedges(neighbor,v);
        }
    }
    return transpose;
}

void graph::dfs2(int v, vector<bool>& known){
    known[v] = true;
    cout << v << " ";
    for(auto& neighbor : adj[v]){
        if(!known[neighbor]){
            dfs2(neighbor,known);
        }
    }
}

void graph::scc(){
    stack<int> filo;
    vector<bool> known(vertices, false);
    for(int i = 0; i < vertices; i++){
        if(!known[i]){
            dfs(i,known,filo);
        }
    }
    cout << "scc" << endl;
    graph transp = transpose();
    fill(known.begin(),known.end(),false);
    while(!filo.empty()){
        int v = filo.top();
        filo.pop();
        if(!known[v]){
            transp.dfs2(v,known);
            cout << endl;
        }
    }
}

int main(){
    graph g(6);
    g.addedges(0,1);
    g.addedges(1,2);
    g.addedges(2,0);
    g.addedges(1,3);
    g.addedges(3,4);
    g.addedges(4,5);
    g.addedges(5,3);
    g.scc();
}