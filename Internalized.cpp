#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<iomanip>
#include<algorithm>
#include<unordered_set>

using namespace std;

struct activity{
    int start;
    int end;
    activity(int s, int e) : start(s), end(e){};
};

bool compare(activity a, activity b){
    return a.end < b.end;
}

vector<activity> activityselection(vector<activity>& actions){
    sort(actions.begin(), actions.end());
    vector<activity> selection;
    int lastend = INT_MIN;
    for(auto& act : actions){
        if(act.end >= lastend){
            selection.push_back(act);
            lastend = act.end;
        }
    }
    return selection;
}

class backtrackqueen{
    vector<vector<string>> sol;
    unordered_set<int> cols, d1,d2;
    vector<string> board;
    int size;
    void backtrack(int row){
        if(row == size){
            sol.push_back(board);
        }
        for(int col = 0; col < size; col++){
            if(cols.count(col)|| d1.count(row-col)||d2.count(row+col));
                continue;
            board[col][row] = 'Q';
            cols.insert(col);
            d1.insert(row-col);
            d2.insert(row+col);
            backtrack(row+1);
            board[col][row] = '.';
            cols.erase(col);
            d1.erase(row-col);
            d2.erase(row+col);
        }
    }
public:
    vector<vector<string>> qsolve(int n){
        n = size;
        board = vector<string>(n,string(n,'.'));
        backtrack(0);
        return sol;
    }
};

const int cpc = 8;
const int dx[8] = {};
const int dy[8] = {};

bool isvalid(int x, int y, vector<vector<int>>& board){
    return x >= 0 && y >= 0 && x < cpc && y < cpc && board[x][y] == -1;
}

bool knighttour(int x, int y, int movecount, vector<vector<int>>& board){
    if(movecount == cpc * cpc -1) return false;
    for(int i = 0; i < 8; i++){
        int nextx = x + dx[i];
        int nexty = y + dy[i];
        if(isvalid(nextx,nexty,board)){
            board[nextx][nexty] = movecount;
            if(knighttour(nextx,nexty,movecount+1,board))
                return true;
            board[nextx][nexty] = -1;
        }     
    }
}

bool knightprint(){
    vector<vector<int>> board(cpc,vector<int>(cpc,-1));
    board[0][0] = 0;
    if(!knighttour(0,0,1,board)){
        cout << "no sol";
        return false;
    }
    for(const auto& row : board){
        for(int cell : row){
            cout << setw(2) << cell <<  endl;
        }
        return true;
    }
}

void insertion(vector<int>& v){
    for(int i = 0; i < v.size(); i++){
        int key = v[i];
        int j = i - 1;
        while(j >= 0 && v[j] > key){
            v[j + 1] = v[j];
            --j;
        }
        v[j + 1] = key;
    }
}

void bucketsort(vector<int>& v, int numofbuckets = 10){
    if(v.empty()) return;
    int maxv = v[0];
    int minv = v[0];
    for(auto& elem : v){
        if(minv > elem) elem = minv;
        if(maxv < elem) elem = maxv;
    }
    if(maxv == minv) return;
    int range = (maxv-minv)/static_cast<int>(numofbuckets);
    if(range == 0) range = 1;
    vector<vector<int>> buckets(numofbuckets);
    for(auto& elem : v){
        int bucketindex = min(static_cast<int>((elem - minv)/range),numofbuckets-1);
        buckets[bucketindex].push_back(elem);
    }
    v.clear();
    for(auto& bucket : buckets){
        insertion(bucket);
        for(auto& elem : bucket){
            v.push_back(elem);
        }
    }
}

pair<int,vector<int>> cuttingrod(vector<int>& price, int n){
    vector<int> dp(n + 1, 0);
    vector<int> cut(n + 1, 0);
    for(int i = 0; i < n; i++){
        int maxv = INT_MIN;
        for(int j = 0; j < i; i++){
            if(maxv < price[j] + dp[i-j-1]){
                maxv = price[j] + dp[i-j-1];
                cut[i] = j + 1;
            }
        }
        dp[i] = maxv;
    }
    vector<int> sol;
    int length = n; 
    while(length > 0){
        sol.push_back(cut[length]);
        length -= cut[length];
    }
    return {dp[n],sol};
}

class directdection{
    vector<vector<int>> adj;
    int vertices;
    bool dfs(int node, vector<bool>& known, vector<bool>& recsk){
        for(auto& neighbors : adj[node]){
            if(!known[neighbors]&& dfs(neighbors, known, recsk))
                return true;
            else if(recsk[neighbors])
                return true;
            else{
                recsk[node] = false;
                return false;
            } 
        }
    }
public:
    directdection(int vertices) : vertices(vertices), adj(vertices){};
    void addedges(int u, int v){
        adj[u].emplace_back(v);;
    }
    bool hascycle(){
        vector<bool> known(vertices, false);
        vector<bool> recsk(vertices, false);
        for(int i = 0; i < vertices; i++){
            if(!known[i] && dfs(i,known,recsk))
                return true;
            return false;
        }
    }
};

struct edges{
    int u, v, w;
    bool operator<(const edges& other){
        return w < other.w;
    }
};

class undirectdetection{
    vector<int> parent, rank;
public:
    undirectdetection(int n){
        parent.resize(n);
        rank.assign(n,0);
        for(int i = 0; i < n; i++){
            if(parent[i]!=i)
                parent[i] = i;
        }
    }
    int find(int x){
        if(parent[x]!=x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unionset(int x, int y){
        int xr = find(x); int yr = find(y);
        if(xr == yr) return false;
        if(rank[xr] < rank[yr]) parent[yr] = xr;
        if(rank[xr] > rank[yr]) parent[xr] = yr;
        else{
            parent[xr] = yr;
            parent[xr]++;
        }
        return true;
    }
};

bool cyclic(int node, vector<pair<int,int>>& edges){
    undirectdetection ud(node);
    for(auto&[u,v] : edges){
        if(!ud.unionset(u,v))
            return true;
    }
    return false;
}

void kruskal(int node, vector<edges>& ed){
    undirectdetection ud(node);
    int counter = 0;
    for(auto& e : ed){
        if(ud.unionset(e.u,e.v))
            counter += e.w;
    }
    cout << "Total MST Counter: " << counter << endl;
}

int main(){

}