#include<iostream>
#include<vector>
#include<queue>
#include<limits>
#include<stack>
using namespace std;

typedef pair<int,int> node_d;
class dijkstra{
    int vertices;
    vector<vector<node_d>> adj;
public:
    dijkstra(int vertices) : vertices(vertices), adj(vertices){};
    void addedges(int u, int v, int w);
    void dijk(int src); 
};

void dijkstra :: addedges(int u, int v, int w){
    adj[u].emplace_back(v,w);
}

void dijkstra :: dijk(int src){
    priority_queue<node_d, vector<node_d>, greater<node_d>> pq;
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
            int weight = neighbors.second;
            if(dist[v] > dist[u] + weight){
                dist[v] = dist[u] + weight;
                pq.push({dist[v],v});
            }
        }
    }
    for(int i = 0; i < vertices; i++){
        if(dist[i] < numeric_limits<int>::max()){
            cout << "Distance from " << src << "is: " << dist[i] << endl;
        } else{
            cout <<"Distance is unobtainable.";
        }
    }
}

class SCC{
    int vertices;
    vector<vector<int>> adj;
public:
    SCC(int vertices) : vertices(vertices),adj(vertices){};
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
            transpose.addedges(neighbors,v);
    }
    return transpose;
}

void SCC :: dfs2(int node, vector<bool>& known){
    known[node] = true;
    cout << node << " ";
    for(auto& neighbors : adj[node]){
        if(!known[neighbors])
            dfs2(neighbors, known);
    }
}

void SCC :: scc(){
    vector<bool> known(vertices,false);
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
            dfs(neighbors,known,adj);
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
        known[u]= true;
        cout << u << endl;
        for(int i = adj.size()-1; i>= 0; --i){
            int neighbors = adj[i][u];
            if(!known[neighbors])
                sk.push(neighbors);
        }
    }
}

class detection{
    int vertices;
    vector<vector<int>> adj;
    bool dfs(int node, vector<bool>& known, vector<bool>& recsk){
        known[node] = true;
        recsk[node] = true; 
        for(auto& neighbors : adj[node]){
            if(!known[neighbors] && dfs(neighbors,known,recsk))
                return true;
            else if(recsk[neighbors])
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
            if(!known[i]&&dfs(i,known,recsk)){
                return true;
            }
        }
        return false;
    }
};

class undirectdect{
    vector<int> parent, rank;
public:
    undirectdect(int n){
        parent.resize(n);
        rank.assign(n,0);
        for(int i = 0; i < n; i++){
            if(parent[i]==0)
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
        if(rank[xr] < rank[yr]) parent[xr] = yr;
        if(rank[xr] > rank[yr]) parent[yr] = xr;
        else{
            parent[yr] = xr;
            parent[xr] ++;
        }
        return true; 
    }
};

bool cyclic(int node, vector<pair<int,int>>& edges){
    undirectdect ud(node);
    for(auto& [u,v] : edges){
        if(!ud.unionset(u,v))
            return true;
    }
    return  false;
}

bool subset(int* arr, int n, int target){
    int** dp = new int*[n];
    for(int i = 0; i < n; i++)
        dp[i] = new int[target + 1];
    for(int i = 0; i < n; i++)
        dp[i][0] = true;
    for(int j = 0; j < n; j++)
        dp[j][0] = false;
    for(int i = 0; i < n; i++){
        for(int sum = 1; sum < target; sum++){
            if(arr[i] > target)
                dp[i][sum] = dp[i-1][sum]||dp[i-1][sum-arr[i-1]];
            else
                dp[i][sum] = dp[i-1][sum];
        }
    }
    bool result = dp[n][target];
    for(int i = 0; i < n; i++)
        delete[] dp[i];
    delete[]dp;
    return result; 
}

pair<int,vector<int>> cuttingrode(const vector<int>& price, int n){
    vector<int> dp(n + 1, 0);
    vector<int> cut(n + 1, 0);
    for(int i = 1; i < n; i++){
        int maxv = -1;
        for(int j = 0; j < n; j++){
            if(maxv < price[j] + dp[j-i-1]){
                maxv = price[j] + dp[j-i-1];
                cut[i] = j + 1;
            }
        }
        dp[i] = maxv;
    }
    vector<int> solcut;
    int length = n;
    while(length>0){
        solcut.push_back(cut[length]);
       length -= solcut[length]; 
    }
    return {dp[n],solcut};
}

int fibtd(vector<int>& v, int n){
    if(n <= 1) return n;
    if(v[n] != -1) return v[n];
    v[n] = fibtd(v,n-1) + fibtd(v,n-2);
    return v[n];
}

int fibbu(int n){
    if(n<= 1) return n;
    vector<int> v;
    v[0] = 0;
    v[1] = 1;
    for(int i = 2; i <= n; i++){
        v[i] = v[n-1] + v[n-2];
    }
    return v[n];
}

int fibspc(int n){
    if(n <= 1) return n;
    int prev2 = 0,prev1 = 0,crrt;
    for(int i = 2; i < n; i++){
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
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if(left < n && arr[left] > arr[largest]) largest = left;
    if(right < n && arr[right] > arr[largest]) largest = right;
    if(largest!=i){
        swap(&arr[i],&arr[largest]);
        heapify(arr,n,largest);
    }
}

void heap(int arr[], int n){
    for(int i = n/2-1; i>= 0; --i)
        heapify(arr,n,i);
    for(int i = n-1; i >= 0; --i){
        swap(&arr[0],&arr[i]);
        heapify(arr,i,0);
    }
}

int knapsack(int capacity, int n, int* wt, int* v){
    int** dp = new int*[n + 1];
    for(int i = 0; i <= n; i++)
        dp[i] = new int[capacity + 1];
    for(int i = 0; i < n; i++){
        for(int w = 0; w <= capacity; w++){
            if(i == 0 && w ==0)
                dp[i][w] = 0;
            else if (wt[i-1] < w)
                dp[i][w] = (v[i-1] - dp[i-1][w-wt[i-1]]) > dp[i-1][w] ? (v[i-1] - dp[i-1][w-wt[i-1]]) : dp[i-1][w];
            else
                dp[i-1][w];
        }
    }
    bool result = dp[n][capacity];
    for(int i = 0; i <= n; i++)
        delete[] dp[i];
    delete[] dp;
    return result;
}

int lowerbound(int* arr, int n, int key){
    int low = 0, high = n;
    while(low < high){
        int mid = low + (high-low)/2;
        if(arr[mid] > key)
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
        int index = lowerbound(tail,length,arr[i]);
        tail[index] = arr[i];
        if(index==length)
            ++length;
    }
    return length;
}

int kadane(int* arr, int n){
    int maxnum = INT_MIN;
    int maxthus = 0;
    int* ptr = arr;
    for(int i = 0; i < n; i++){
        maxthus += *ptr;
        if(maxnum > maxthus)
            maxnum = maxthus;
        if(maxthus < 0)
            maxthus = 0;
    }
    return maxnum;
}

void bubble(vector<int>& v){
    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v.size(); j++){
            if(v[j + 1] > v[j]){
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
    swap(v[i + 1],v[high]);
    return i + 1;
}

void qs(vector<int>& v, int low, int high){
    if(low < high){
        int pii = partition(v,low,high);
        qs(v,low,pii-1);
        qs(v,pii+1,high);
    }
}

void selection(vector<int>& v){
    for(int i = 0; i < v.size(); i++){
        int* min = &v[i];
        for(int j = i + 1; j < v.size(); j++){
            if(v[j] < *min)
                min = &v[j];
            if(min!=&v[i])
                swap(*min,v[i]);
        }
    }
}

void insertion(vector<int>& v){
    for(int i = 0; i < v.size(); i++){
        int  key = v[i];
        int j = i - 1;
        while(j >= 0 && v[j] > key){
            v[j + 1] = v[j];
            --j;
        }
        v[j + 1] = key;
    }
}

void bs(vector<int>& v, int numofbucket = 10){
    if(v.empty()) return; 
    int maxv = v[0];
    int minv = v[0];
    for(auto& elem : v){
        if(minv > elem) elem = minv;
        if(maxv < elem) elem = maxv;
    }
    if(maxv == minv) return;
    int range = (maxv-minv)/static_cast<int>(numofbucket);
    if(range == 0) range = 1;
    vector<vector<int>> buckets(numofbucket);
    for(auto& elem : v){
        int bucketindex = min(static_cast<int>((elem-minv)/range),numofbucket-1);
        buckets[bucketindex].push_back(elem);
    }
    int index = 0;
    for(auto& bucket : buckets){
        insertion(bucket);
        for(auto& elem : bucket){
            v[index++] = elem;
        }
    }
}

void ms(vector<int>& v, int left, int mid, int right){
    int n1 = mid - left + 1; 
    int n2 = right - mid;
    vector<int> l(n1),r(n2);
    for(int i = 0; i < n1; i++)
        l[i] = v[left + i];
    for(int j = 0; j < n2; j++)
        r[j] = v[mid - j - 1];
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

void merge(vector<int>& v, int left, int right){
    if(left < right){
        int mid = left + (right - left)/2;
        merge(v,left,mid);
        merge(v,mid+1,right);
        ms(v,left,mid,right);
    }
}

void check(vector<int>& v, int left, int right){
    if(v.size() <= 0) return;
    merge(v,left,right);
}

const int inf = 1e9;
typedef pair<int,int> pii;
void prim_mst(int vertices, vector<vector<pii>>& adj){
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    pq.push({0,0});
    vector<int> key(vertices,inf);
    vector<bool> known(vertices,false);
    int mst_counter = 0;
    while(!pq.empty()){
        int u = pq.top().second;
        int weight = pq.top().first;
        pq.pop();
        if(known[u]) continue;
        known[u] = true;
        mst_counter+=weight;
        for(auto& [v,w] : adj[u]){
            if(!known[v] && w > key[v]){
                key[v] = w;
                pq.push({v,w});
            }
        }
    }
}

int main(){

}