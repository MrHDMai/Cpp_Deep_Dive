#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<limits>
#include<algorithm>

using namespace std;

typedef pair<int,int> nd;
class dijkstra{
    int vertices;
    vector<vector<nd>> adj;
public:
    dijkstra(int vertices) : vertices(vertices), adj(vertices){};
    void addedges(int u, int v, int w);
    void shortestpath(int src);
};

void dijkstra :: addedges(int u, int v, int w){
    adj[u].emplace_back(v,w);
}

void dijkstra :: shortestpath(int src){
    priority_queue<nd,vector<nd>,greater<nd>> pq;
    pq.push({0,src});
    vector<int> dist(vertices, numeric_limits<int>::max());
    dist[src] = 0;
    while(!pq.empty()){
        int dist_u = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if(dist_u > dist[u]) continue;
        for(auto& neighbors : adj[u]){
            int v = neighbors.first;
            int w = neighbors.second;
            if(dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                pq.push({dist[v],v});
            }
        }
    }
    for(int i = 0; i < vertices; i++){
        if(dist[i] < numeric_limits<int>::max())
            cout << "Distace from : " << i << "is " << dist[i] << endl;
        else 
            cout << "Distance is unobtainable." << endl;
    }
}

class SCC{
    int vertices;
    vector<vector<int>> adj;
public:
    SCC(int vertices) : vertices(vertices), adj(vertices){};
    void addedges(int u, int v);
    void dfs(int node, vector<bool>& known, stack<int>& sk);
    SCC transpose();
    void dfs2(int node, vector<bool>& known);
    void scc();
};

void SCC :: addedges(int u, int v){
    adj[u].emplace_back(v);
}

void SCC :: dfs(int node, vector<bool>& known, stack<int>& sk){
    known[node] = true;
    for(auto& neighbors : adj[node]){
        if(!known[neighbors])
            dfs(neighbors,known,sk);
    }
    sk.push(node);
}

SCC SCC :: transpose(){
    SCC transpose(vertices);
    for(int v = 0; v < vertices; v++){
        for(auto& neighbors : adj[v])
            transpose.addedges(neighbors, v);
    }
    return transpose;
}

void SCC :: dfs2(int node, vector<bool>& known){
    known[node] = true;
    cout << node << " ";
    for(auto& neighbors : adj[node]){
        if(!known[neighbors])
            dfs2(neighbors,known);
    }
}

void SCC :: scc(){
    vector<bool> known(vertices, false);
    stack<int> sk;
    for(int i = 0; i < vertices; i++){
        if(!known[i])
            dfs(i,known,sk);
    }
    cout << "SCC: " << endl;
    fill(known.begin(),known.end(), false);
    SCC transp = transpose();
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
    return a.end <  b.end;
}

vector<activity> activityselection(vector<activity>& actions){
    sort(actions.begin(), actions.end(), compare);
    vector<activity> selection;
    int lastend = -1;
    for(auto& act : actions){
        if(act.start >= lastend){
            selection.push_back(act);
            lastend = act.end;
        }
    }
    return selection;
}

void insertion(vector<int>& v){
    for(int i = 0; i < v.size(); i++){
        int key = v[i];
        int j = i - 1;
        while(j >= 0 && v[j] > key){
            v[j+1] = v[j];
            --j;
        }
        v[j+1] = key;
    }
}

void bucketsort(vector<int>& v, int numofbuckets){
    if(v.empty()) return;
    int minv = v[0];
    int maxv = v[0];
    for(auto& elem : v){
        if(minv > elem) minv = elem;
        if(maxv < elem) maxv = elem;
    }
    if(maxv == minv) return;
    int range = (maxv - minv)/static_cast<int>(numofbuckets);
    if(range == 0) range = 1;
    vector<vector<int>> buckets(numofbuckets);
    for(auto& elem : v){
        int bucketindex = min(static_cast<int>((elem - minv)/range), numofbuckets-1);
        buckets[bucketindex].push_back(elem);
    }
    int index = 0;
    for(auto& bucket : buckets){
        insertion(bucket);
        for(auto& elem : bucket)
            v[index++] = elem;
    }
}

pair<int,vector<int>> cuttingrod (const vector<int>& price, int n){
    vector<int> dp(n+1,0);
    vector<int> cut(n+1,0);
    for(int i = 0; i <= n; i++){
        int maxv = -1;
        for(int j = 0; j < i; j++){
            if(maxv < price[j] + dp[i-j-1]){
                maxv = price[j] + dp[i-j-1];
                cut[i] = j + 1;
            }
        }
        dp[i] = maxv;
    }
    vector<int> solcut;
    int length = n;
    while(length > 0){
        solcut.push_back(cut[length]);
        length-=cut[length];
    }
    return{dp[n],solcut};
}

class detection{
    int vertices;
    vector<vector<int>> adj;
    bool dfs(int node, vector<bool>& known, vector<bool>& recsk){
        for(auto& neighbors : adj[node]){
            known[node]  = true;
            recsk[node] = true;
            if(!known[neighbors] && dfs(neighbors,known,recsk))
                return true;
            else if (recsk[neighbors]);
                return true;
        }
        recsk[node] = false;
        return false;
    }
public:
    detection(int vertices) : vertices(vertices), adj(vertices){};
    void addedges(int u, int v){
        adj[u].emplace_back(v);
    }
    bool hascycle(){
        vector<bool> known(vertices, false);
        vector<bool> recsk(vertices, false);
        for(int i = 0; i < vertices; i++){
            if(!known[i] && dfs(i,known,recsk))
                return true;
        }
        return false;
    }
};

struct edges{
    int u, v, w;
    bool operator<(const edges& other) const{
        return w < other.w;
    }
};

class undirectDetection{
    vector<int> parent, rank;
public:
    undirectDetection(int n){
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
        if(rank[xr] < rank[yr]) parent[xr] = yr;
        if(rank[xr] > rank[yr]) parent[yr] = xr;
        else{
            parent[yr] = xr;
            parent[xr] ++;
        }
        return true;
    }
};

int kruskal(int node, vector<edges>& edg){
    sort(edg.begin(), edg.end());
    int counter = 0;
    undirectDetection ud(node);
    for(auto& e : edg){
        if(ud.unionset(e.u,e.v))
            counter+=e.w;
    }
    return counter;
}

bool cyclic(int node, vector<pair<int,int>>& edges){
    undirectDetection ud(node);
    for(auto& [u,v] : edges){
        if(!ud.unionset(u,v))
            return true;
    }
    return false;
}

int fibtd(int n, vector<int>& v){
    if(n <= 1) return n;
    if(v[n] != -1) return v[n];
    v[n] = fibtd(n-1,v) + fibtd(n-2,v);
    return v[n];
}

int fib_bu(int n){
    if(n <= 1) return n;
    vector<int> v(n+1);
    v[0] = 0;
    v[1] = 1;
    for(int i = 2; i <= n; i++){
        v[i] = v[n-1] + v[n-2];
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

inline void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i){
    int high = i;
    int left = 2 * i + 1;
    int right = 2 * i + 1;
    if(left < n && arr[left] > arr[high]) high = left;
    if(right < n && arr[right] > arr[high]) high = right;
    if(high != i){
        swap(&arr[high],&arr[i]);
        heapify(arr,n,high);
    }
}

void heapsort(int arr[], int n){
    for(int i = n/2 - 1; i >= 0; --i)
        heapify(arr,n,i);
    for(int i = n - 1; i >= 0; --i){
        swap(&arr[0],&arr[i]);
        heapify(arr,i,0);
    }
}

long long invcount(vector<int>& v, int left, int mid, int right){
    vector<int> l(v.begin() + left + 1, v.begin() + mid + 1);
    vector<int> r(v.begin() + mid + 1, v.begin() + right + 1);
    int counter = 0;
    int i = 0, j = 0, k = left;
    while(i < l.size() && j < r.size()){
        if(l[i] < r[j])
            v[k++] = l[i++];
        else{
            v[k++] = r[j++];
            counter += (l.size() - i);
        }
    }
    while(i < l.size())
        v[k++] = l[i++];
    while(j < r.size())
        v[k++] = r[j++];
    return counter;
}

long long mergecount(vector<int>& v, int left, int right){
    int counter = 0;
    if(left < right){
        int mid = left + (right - left)/2;
        counter += mergecount(v,left,mid);
        counter += mergecount(v,mid+1,right);
        counter += invcount(v,left,mid,right);
    }
    return counter;
}

int lowerbound(int* arr, int n, int key){
    int low = 0, high = n;
    while(low < high){
        int mid = low + (high - low)/2;
        if(arr[mid] >= key)
            high = mid;
        else
            low = mid + 1;
    }
    return low;
}

int lis(int* arr, int n){
    int* tail = new int[n];
    int length = 0;
    for(int i = 0; i < n; i++){
        int index = lowerbound(arr,length,arr[i]);
        tail[index] = arr[i];
        if(index == length)
            ++length;
    }
    delete[] tail;
    return length;
}

int kadane(int* arr, int n){
    int maxnum = INT_MIN;
    int maxthus = 0;
    for(int i = 0; i <= n; i++){
        maxthus += arr[i];
        if(maxnum > maxthus)
            maxthus = maxthus;
        if(maxthus < 0)
            maxthus = 0;
    }
    return maxnum;
}

int knapsack(int capacity, int n, int* wt, int* v){
    int** dp = new int*[n + 1];
    for(int i = 0; i <= n; i++)
        dp[i] = new int[capacity + 1];
    for(int i = 0; i < n; i++){
        for(int w = 0; w <= capacity; w++){
            if(i==0 || w == 0)
                dp[i][w] = 0;
            else if(wt[i-1] < w)
                dp[i][w] = (v[i-1] + dp[i-1][w-wt[i-1]]) > dp[i-1][w] ? v[i-1] + dp[i-1][w-wt[i-1]] : dp[i-1][w]; 
            else dp[i][w] = dp[i-1][w];
        }
    }
    int result = dp[n][capacity];
    for(int i = 0; i <= n; i++)
        delete[]dp[i];
    delete[] dp;
    return result;
}

void mergesort(vector<int>& v, int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> l(n1),r(n2);
    for(int i = 0; i < n1; i++)
        l[i] = v[left + i];
    for(int j = 0; j < n2; j++)
        r[j] = v[mid + j + 1];
    int i = 0, j = 0, k = left;
    while(i < n1 && j < n2){
        if(l[i] < r[j])
            v[k++] = l[i++];
        else
            v[k++] = r[j++];
    }
    while(i < n1)
        v[k++] = l[i++];
    while(j < n2)
        v[k++] = r[j++];
}

void merge(vector<int>& v, int left, int right){
    if(left < right){
        int mid = left + (right - left)/2;
        merge(v,left,mid);
        merge(v,mid+1,right);
        mergesort(v,left,mid,right);
    }
}

void check(vector<int>& v, int left, int right){
    if(v.size() <= 1) return;
    merge(v,left,right);
}

const int inf = 1e9;
typedef pair<int,int> pii;
void prim_mst(int vertices, vector<vector<pii>>& adj){
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    pq.push({0,0});
    vector<int> key(vertices, inf);
    vector<bool> known(vertices,false);
    int counter = 0;
    while(!pq.empty()){
        int v = pq.top().second;
        int weight = pq.top().first;
        if(known[v]) continue;
        known[v] = true;
        counter=+ weight;
        for(auto& [v,weight] : adj[v]){
            if(!known[v] && weight < key[v]){
                key[v] = weight;
                pq.push({v,weight});
            }
        }
    }
    cout << counter << endl;
}

void bubble(vector<int>& v){
    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v.size()-1; j++){
            if(v[j] > v[j + 1]){
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

int partition(vector<int>& v, int low, int high){
    int pvt = v[high];
    int i = low - 1;
    for(int j = low; j < high; j++){
        if(v[j] < pvt){
            ++i;
            swap(v[i],v[j]);
        }
    }
    swap(v[i+1],v[high]);
    return i + 1;
}

void quicksort(vector<int>& v, int low, int high){
    if(low <= high){
        int pii = partition(v,low,high);
        quicksort(v,low,pii-1);
        quicksort(v,pii+1,high);
    }
}

void selection(vector<int>& v){
    for(int i = 0; i < v.size(); i++){
        int* min = &v[i];
        for(int j = i + 1; j < v.size(); i++){
            if(v[j] < *min)
                swap(v[i],v[j]);
            if(min!=&v[i])
                swap(*min,v[i]);
        }
    }
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

void dfsIterative(int node, vector<bool>& known, vector<vector<int>>& adj){
    stack<int> sk;
    sk.push(node);
    known[node] = true;
    while(!sk.empty()){
        int u = sk.top();
        sk.pop();
        if(known[u]) continue;
        known[u] = true;
        cout << u << endl;
        for(int i = adj[u].size() -1; i >= 0; i--){
            int neighbors = adj[u][i];
            if(!known[neighbors])
                sk.push(neighbors);
        }
    }
}

bool subsetsub(int* arr, int n, int target){
    bool** dp = new bool*[n + 1];
    for(int i = 0; i < n; i++)
        dp[i] = new bool[target + 1];
    for(int i = 0; i <= n; i++)
        dp[i][0] = true; 
    for(int j = 0; j <= n; j++)
        dp[j][0] = false;
    for(int i = 1; i < n; i++){
        for(int sum = 1; sum < target; sum++){
            if(arr[i] < sum)
                dp[i][sum] = dp[i-1][sum] || dp[i-1][sum-arr[i-1]];
            else
                dp[i-1][sum];
        }
    }
    bool result = dp[n][target];
    for(int i = 0; i <= n; i++)
        delete[] dp[i];
    delete[] dp;
    return result;
}

class backtrackqueen{
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
            backtrack(row+1);
            board[row][col] = '.';
            cols.erase(col);
            d1.erase(row-col);
            d2.erase(row+col);
        }
    } 
    vector<vector<string>> queensolve(int n){
        size = n;
        board = vector<string>(n,string(n,'.'));
        backtrack(0);
        return sol;
    }
};

const int cpc = 8;
const int dx[8] = {};
const int dy[8] = {};

inline bool isvalid(int x, int y, vector<vector<int>>& board){
    return x >- 0 && y > 0 && x < cpc && y < cpc && board[x][y] == -1;
}

bool knightsolver(int x, int y, int movecount, vector<vector<int>>& board){
    if(movecount == cpc * cpc) return;
    for(int i = 0; i < 8; i++){
        int nextx = x + dx[i];
        int nexty = y + dy[i];
        if(isvalid(nextx,nexty,board)){
            board[nextx][nexty] = movecount;
            if(knightsolver(nextx,nexty,movecount+1,board))
                return true;
            board[nextx][nexty] = -1;
        }
    }
    return false;
}

bool knighttour(){
    vector<vector<int>> board(N,vector<int>(N,-1));
    board[0][0] = 0;
    if(!solveknighttour(0,0,1,board)){
        cout << "No Solution Found.\n";
        return false;
    }
    for(const auto& row : board){
        for(int cell : row)
            cout << setw(2) << cell << " ";
        cout << '\n';
    }
    return true;
}

int main(){

}