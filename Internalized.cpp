#include<iostream>
#include<vector>
#include<iomanip>
#include<unordered_set>
#include<string>
#include<algorithm>
#include<limits>
#include<stack>
#include<queue>

using namespace std;

typedef pair<int,int> nd;
struct dijk{
    int vertices;
    vector<vector<nd>> adj;
public:
    dijk(int vertices) : vertices(vertices), adj(vertices){};
    void addedges(int u, int v, int w);
    void shortestpath(int src);
};

void dijk :: addedges(int u, int v, int w){
    adj[u].emplace_back(v,w);
}

void dijk :: shortestpath(int src){
    priority_queue<nd, vector<nd>, greater<nd>> pq;
    pq.push({0,src});
    vector<int> dist(vertices, numeric_limits<int>::max());
    dist[src] = 0;
    while(!pq.empty()){
        int dist_u = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if(dist_u > u) continue;
        for(auto& neighbors : adj[u]){
            int v = neighbors.first;
            int w = neighbors.second;
            if(dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    for(int i = 0; i < vertices; i++){
        if(dist[i] < numeric_limits<int>::max())
            cout << "The distance from " << src << "to " << i << "is " << dist[i];
        else 
            cout << "The distance from " << src << "to " << i << "is unobtainable";
    }
}

struct SCC{
    int vertices;
    vector<vector<int>> adj;
public:
    SCC(int vertices) : vertices(vertices), adj(vertices){};
    void addedges(int u, int v);
    void dfs(int node, vector<bool>& known, stack<int>& sk);
    SCC transpose();
    void dfs2(int node, vector<bool>& known);
    void strongestcorr();
};

void SCC :: addedges(int u, int v){
    adj[u].emplace_back(v);
}

void SCC :: dfs(int node, vector<bool>& known, stack<int>& sk){
    known[node] = true;
    for(auto& neighbors : adj[node]){
        if(!known[neighbors])
            dfs(neighbors, known, sk);
    }
    sk.push(node);
}

SCC SCC :: transpose(){
    SCC transpose(vertices);
    for(int v = 0; v < vertices; v++){
        for(auto& neighbors : adj[v])
            transpose.addedges(neighbors,v);
    }
    return transpose;
}

void SCC :: dfs2(int node, vector<bool>& known){
    known[node] = true;
    cout << node << endl;
    for(auto& neighbors : adj[node]){
        if(!known[node])
            dfs2(neighbors,known);
    }
}

void SCC :: strongestcorr(){
    vector<bool> known;
    stack<int> sk;
    for(int i = 0; i < vertices; i++){
        if(!known[i])
            dfs(i,known,sk);
    }
    fill(known.begin(), known.end(), false);
    SCC transp = transpose();
    cout << "SCC : ";
    while(!sk.empty()){
        int u = sk.top();
        sk.pop();
        if(!known[u])
            transp.dfs2(u,known);
        cout << endl;
    }
}

struct activity{
    int start;
    int end;
    activity(int s, int e) : start(s), end(e){};
};

bool compare(activity a, activity b){
    return a.end < b.end;
}

vector<activity> activityselection(vector<activity>& actions){
    sort(actions.begin(), actions.end(), compare);
    vector<activity> selection;
    int lastend = INT_MIN;
    for(auto& a : actions){
        if(a.start >= lastend){
            selection.push_back(a);
            lastend = a.end;
        }
    }
    return selection;
}

struct backtrackqueen{
    vector<vector<string>> sol;
    unordered_set<int> cols, d1,d2;
    vector<string> board;
    int size;
    void backtrack(int row){
        if(row == size){
            sol.push_back(board);
            return;
        }
        for(int col = 0; col < size; col++){
            if(cols.count(col) || d1.count(row-col) || d2.count(row+col))
                continue;
            board[row][col] = 'Q';
            cols.insert(col);
            d1.insert(row-col);
            d2.insert(row+col);
            backtrack(row + 1);
            board[row][col] = '.';
            cols.erase(col);
            d1.erase(row-col);
            d2.erase(row+col);
        }
    }
public:
    vector<vector<string>> qs(int n){
        size = n;
        vector<string> board(n,string(n,'.'));
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

bool knighttour(int x, int y,int movecount, vector<vector<int>>& board){
    if(movecount == cpc* cpc) return true;
    for(int i = 0; i < 8; i++){
        int nextx = x + dx[i];
        int nexty = y + dy[i];
        if(isvalid(nextx,nexty,board)){
            board[nextx][nexty] = movecount;
            if(knighttour(nextx,nexty,movecount - 1, board))
                return true; 
            board[nextx][nexty] = -1;
        }
    }
    return false;
}

bool ks(){
    vector<vector<int>> board(cpc,vector<int>(cpc,-1));
    board[0][0] = 0;
    if(!knighttour(0,0,1,board)){
        cout << "No Sol";
        return false;
    }
    for(const auto& rows : board){
        for(auto& cell : rows)
            cout << setw(2) << cell << " ";
    }
    return true;
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
        if(minv > elem) minv = elem;
        if(maxv < elem) maxv = elem; 
    }
    if(maxv == minv) return;
    int range = (maxv - minv)/static_cast<int>(numofbuckets);
    if(range == 0) range = 1;
    vector<vector<int>> buckets(numofbuckets);
    for(auto& elem : v){
        int bucketindex = min(static_cast<int>((elem - minv)/range),numofbuckets-1);
        buckets[bucketindex].push_back(elem);
    }
    int index = 0;
    for(auto& bucket : buckets){
        insertion(bucket);
        for(auto& elem : bucket)
            v[index++] = elem; 
    }
}

pair<int,vector<int>> cuttingrod(vector<int>& price, int n){
    vector<int> dp(n + 1, 0);
    vector<int> cut(n + 1, 0);
    int maxv = INT_MIN;
    for(int i = 0; i <= n; i++){
        for(int j = 0; j < i; j++){
            if(maxv < price[j] + dp[i-j-1]){
                maxv = price[j] + dp[i-j-1];
                cut[i] = j + 1;
            }
        }
        dp[i] = maxv;
    }
    vector<int> sol;
    int length = n;
    while(length >= 0){
        sol.push_back(cut[length]);
        length -=cut[length];
    }
    return{dp[n],sol};
}

struct directdetection{
    vector<vector<int>> adj;
    int vertices;
    bool dfs(int node, vector<bool>& known, vector<bool>& recsk){
        known[node] = true; 
        recsk[node] = true;
        for(auto& neighbors : adj[node]){
            if(!known[neighbors] && dfs(neighbors,known,recsk))
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
    directdetection(int vertices) : vertices(vertices), adj(vertices){};
    void addedges(int u, int v){
        adj[u].emplace_back(v);
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

struct undirecteddetection{
    vector<int> parent, rank;
    undirecteddetection(int n){
        parent.resize(n);
        rank.assign(n,0);
        for(int i = 0; i < n; i++){
            if(parent[i] != i)
                parent[i] = i;
        }
    }
    int find(int x){
        if(parent[x] != x){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    bool unionset(int x, int y){
        int xr = find(x); int yr = find(y);
        if(rank[xr] < rank[yr]) parent[yr] = xr;
        if(rank[xr] > rank[yr]) parent[xr] = yr;
        else{
            parent[xr] = yr;
            parent[xr]++;
        }
        return true;
    }
};

void kruksak(int node, vector<edges>& edg){
    sort(edg.begin(), edg.end());
    undirecteddetection ud(node);
    int counter = 0;
    for(auto& e : edg){
        if(ud.unionset(e.u,e.v))
            counter += e.w;
    }
    cout << "The Total count of the kruskal implementation is: " << counter << endl;
}

bool hascycle(int node, vector<pair<int,int>>& edges){
    undirecteddetection ud(node);
    for(auto& [u,v] : edges){
        if(!ud.unionset(u,v))
            return true;
    }
    return false;
}

int fibtd(int n, vector<int>& v){
    if(n <= 1) return n;
    if(v[n] != -1) return v[n];
    v[n] = fibtd(n - 1,v) + fibtd(n-2,v);
    return v[n];
}

int fibbu(int n){
    if(n <= 1) return n;
    vector<int>v(n + 1);
    v[0] = 0;
    v[1] = 1;
    for(int i = 2; i <= n; i++){
        v[i] = v[n -1] + v[n - 2];
    }
    return v[n];
}

int fibspc(int n){
    if(n <= 1) return n;
    int prev2 = 0, prev1 = 1, crrt = 0;
    for(int i = 2; i <= n; i++){
        crrt = prev2 + prev1;
        prev2 = prev1;
        prev1 = crrt;
    }
    return prev1;
}

void inline swap(int* a, int* b){
    int temp = *a;
    *a = *b;
}

void heapify(int arr[], int n, int i){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if(left < n && arr[left] > arr[largest]) largest = left;
    if(right < n && arr[right] > arr[largest]) largest = right;
    if(largest != i){
        swap(&arr[i],&arr[largest]);
        heapify(arr,n,largest);
    }
}

void heapsort(int arr[], int n){
    for(int i = n/2; i >= 0; --i)
        heapify(arr,n,i);
    for(int i = n - 1; i >= 0; i--){
        swap(&arr[0],&arr[i]);
        heapify(arr,0,i);
    }
}

long long invmergecounter(vector<int>& v, int left, int mid,int right){
    vector<int> l(v.begin() + left + 1, v.begin() + mid + 1);
    vector<int> r(v.begin() + mid + 1, v.begin() + right + 1);
    long long counter = 0;
    int i = 0, j = 0, k = left;
    while(i < l.size() && j < r.size()){
        if(v[i] < r[j])
            v[k++] = l[i++];
        else{
            v[k++] = r[j++];
            counter += (l.size() -1);
        }
    }
    while(i < l.size()) v[k++] = l[i++];
    while(j < r.size()) v[k++] = r[j++];
    return counter;
}

long long invcounter(vector<int>& v, int left, int right){
    long long counter = 0;
    if(left < right){
        int mid = left + (right - left)/2;
        counter += invcounter(v,left,mid);
        counter += invcounter(v,mid,right);
        counter += invmergecounter(v,left,mid,right);
    }
    return counter;
}

int kadane(int* arr, int n, int key){
    int maxnum = INT_MIN;
    int maxthus = 0;
    for(int i = 0; i <= n; i++){
        maxthus += arr[i];
        if(maxnum > maxthus)
            maxnum = maxthus;
        if(maxthus <= 0)
            maxthus = 0;
    }
    return maxnum;
}

void bfs(int node, vector<bool>& known, vector<vector<int>>& adj){
    queue<int> q;
    q.push(node);
    known[node] = true;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        cout << u << endl;
        for(auto& neighbors : adj[u]){
            if(!known[neighbors]){
                known[neighbors] = true;
                q.push(neighbors);
            }
        } 
    }
}

void dfs(int node, vector<bool>& known, vector<vector<int>>& adj){
    known[node] = true;
    for(auto& neighbors : adj[node]){
        if(!known[neighbors])
            dfs(neighbors, known, adj);
    }
}

void dfsI(int node, vector<bool>& known, vector<vector<int>>& adj){
    stack<int> sk;
    sk.push(node);
    known[node] = true;
    while(!sk.empty()){
        int u = sk.top();
        sk.pop();
        if(known[u]) continue;
        known[u] = true;
        cout << u << endl;
        for(int i = adj.size() - 1; i >= 0; i--){
            for(auto& neighbors : adj[u]){
                neighbors = adj[u][i];
                if(!known[neighbors])
                    sk.push(neighbors);
            }
        }
    }
}

bool subsetsum(int* arr, int n, int target){
    bool** dp = new bool*[n + 1];
    for(int i = 0; i <= n; i++)
        dp[i] = new bool[target + 1];
    for(int i = 0; i < n; i++)
        dp[i][0] = true;
    for(int j = 0; j < n; j++)
        dp[j][0] = false;
    for(int i = 1; i <= n; i++){
        for(int sum = 1; sum <= target; sum++){
            if(arr[i-1] < sum)
                dp[i][sum] = dp[i-1][sum] || dp[i-1][sum-arr[i-1]];
            else
                dp[i][sum]=dp[i-1][sum];
        }
    }
    bool result = dp[n][target];
    for(int i = 0; i <= n; i++)
        delete[] dp[i];
    delete[] dp;
    return result;
}

const int inf = 1e9;
typedef pair<int,int> pii; 
void prim_mst(int node, vector<vector<pii>>& adj){
    priority_queue<pii,vector<pii>, greater<pii>> pq;
    vector<bool> mst(node, false);
    vector<int> key(node,inf);
    key[0] = 0;
    pq.push({0,0});
    int counter = 0;
    while(pq.empty()){
        int u = pq.top().first;
        int wt = pq.top().second;
        pq.pop();
        if(mst[u]) continue;
        mst[u] = true;
        counter += wt; 
        for(auto& [v,w] : adj[u]){
            if(!mst[u] && v < key[v]){
                key[v] = w;
                pq.push({v,w});
            }
        }
    }
    
}

void mergesort(vector<int>& v, int left, int mid ,int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> l(n1), r(n2);
    for(int i = 0; i < n1; i++)
        l[i] = v[left + i];
    for(int j = 0; j < n2; j++)
        r[j] = v[mid + j + 1];
    int i = 0, j = 0, k = left;
    while(i < n1 && j < n2){
        if(l[i] < r[j]){
            v[k] = l[i];
            i++;
        } else{
            v[k] = r[j];
            j++;
        }
        k++;
    }
    while(i < n1){
        v[k] = l[i];
        i++;
        k++;
    }
    while(j < n2){
        v[k] = r[j];
        j++;
        k++;
    }
}

int lowerbound(int* arr, int n, int key){
    int low = 0, high = n;
    if(low < high){
        int mid = low + (high-low)/2;
        if(arr[mid] > key)
            high = mid;
        else 
            low = mid + 1;
    }
    return low;
}

int lis(int* arr, int n){
    int* tail = new int[n + 1];
    int length = 0;
    for(int i = 0; i < n; i++){
        int index = lowerbound(tail,length,arr[i]);
        tail[index] = arr[i];
        if(index == length)
            ++length;
    }
    return length;
}

void merge(vector<int>& v, int left, int right){
    if(left < right){
        int mid = left + (right - left)/2;
        merge(v,left,mid);
        merge(v,mid + 1, right);
        mergesort(v,left,mid,right);
    }
}

void check(vector<int>& v, int right, int left){
    if(v.empty())
        return;
    merge(v,left,right);
}

int knapsack(int capacity, int* wt, int* v, int n){
    int** dp = new int*[n + 1];
    for(int i = 0; i < n; i++)
        dp[i] = new int[capacity + 1];
    for(int i = 0; i < n; i++){
        for(int w = 0; w < capacity; w++){
            if(i == 0 || w == 0)
                dp[i][w] = 0;
            else if(wt[i-1] < w)
                dp[i][w] = (v[n-1] + dp[i-1][w-wt[i-1]]) < dp[i-1][w] ? v[n + 1] + dp[i-1][w-wt[i-1]]: dp[i-1][w];
            else
                dp[i][w] = dp[i-1][w];
        }
    }
    int result = dp[n][capacity];
    for(int i = 0; i <= n; i++)
        delete[] dp[i];
    delete[] dp;
    return result;
}



int main(){

}
