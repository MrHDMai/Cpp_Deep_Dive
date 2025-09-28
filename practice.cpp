#include<iostream>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

class graph {
private: 
    int vertices;
    vector<vector<int>> adj;
public:
    graph(int vertices) : vertices(vertices),adj(vertices){};
    void addedges(int u, int v);
    void dfs(int node, vector<bool>& known, stack<int>& sk);
    graph transpose();
    void dfs2(int node, vector<bool>& known);
    void scc();
};

void graph :: addedges(int u, int v){
    adj[u].emplace_back(v);
}

void graph :: dfs(int node, vector<bool>& known, stack<int>& sk){
    known[node] = true;
    for(auto& neighbors : adj[node]){
        if(!known[neighbors])
            dfs(neighbors,known,sk);
    }
    sk.push(node);
}

graph graph :: transpose(){
    graph transpose(vertices);
    for(int v = 0; v < vertices; v++){
        for(auto& neighbors : adj[v]){
            transpose.addedges(neighbors,v);
        }
    }
    return transpose;
}

void graph :: dfs2(int node, vector<bool>& known){
    known[node] = true;
    cout << node << " ";
    for(auto& neighbors : adj[node]){
        if(!known[neighbors])
            dfs2(neighbors,known);
    }
}

void graph :: scc(){
    vector<bool> known(vertices, false);
    stack<int> sk;
    for(int i = 0; i < vertices; i++){
        if(!known[i]){
            dfs(i,known,sk);
        }
    }
    cout << "SCC: " << endl;
    fill(known.begin(),known.end(),false);
    graph transp = transpose();
    while(!sk.empty()){
        int u = sk.top();
        sk.pop();
        if(!known[u]){
            transp.dfs2(u,known);
            cout <<" ";
        }
    }
}

typedef pair<int,int> nd;
class dij{
private: 
    int vertices;
    vector<vector<nd>> adj;
public:
    dij(int vertices) : vertices(vertices), adj(vertices){};
    void addedges(int u, int v, int w);
    void dijkstra(int src);
};

void dij :: addedges(int u, int v, int w){
    adj[u].emplace_back(v,w);
    adj[v].emplace_back(u,w);
}

void dij :: dijkstra(int src){
    priority_queue<nd, vector<nd>, greater<nd>> pq;
    vector<int> dist(vertices,numeric_limits<int>::max());
    pq.push({0,src});
    dist[src] = 0;
    while(!pq.empty()){
        int distu = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if(distu > dist[u]) continue;
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
            cout << "Distance: " << dist[i] << endl;
        } else{
            cout << "Cannot find path." << endl;
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
        cout << "u" << endl;
        for(auto& neighbors : adj[u]){
            if(!known[neighbors])
            known[u] = true;
            q.push(neighbors);
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
                return  true;
        }
        recsk[node] = false;
        return false;
    }
public:
    detection(int vertices):vertices(vertices),adj(vertices){};
    void addedges(int u, int v){
        adj[u].emplace_back(v);
    }
    bool hascycle(){
        vector<bool> known(vertices,false);
        vector<bool> recsk(vertices,false);
        for(int i = 0; i < vertices; i++)
            if(!known[i] && dfs(i,known,recsk))
                return true;
            return false;
    }
};

class undirectDetec{
    vector<int> parent,rank;
public:
    undirectDetec(int n){
        parent.resize(n);
        rank.assign(n,0);
        for(int i = 0; i < n; i++)
            parent[i] = i;
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
        else if(rank[xr] < rank[yr]) parent[yr] = xr;
        else{
            parent[yr] = xr;
            parent[xr]++;
        }
        return true;
    }
};

class matrix{
    vector<vector<int>> a;
    matrix operator*(const matrix& other){
        matrix result;
        int n = a.size();
        int m = a[0].size();
        for(int i = 0; i < n; i++){
            vector<int> row(m);
            for(int j = 0; j < m; j++){
                row[j] = a[i][j] * other.a[i][j];
            }
            result.a.push_back(row);
        }
        return result;
    }
};

bool cyclic(int node, vector<pair<int,int>>& edges){
    undirectDetec ud(node);
    for(auto& [u,v] : edges){
        if(!ud.unionset(u,v))
            return true;
    }
    return false;
}

pair<int,vector<int>> cutrod(const vector<int>& price, int n){
    vector<int> dp(n + 1, 0);
    vector<int> cut(n + 1, 0);
    for(int i = 1; i < n; i++){
        int maxv = -1;
        for(int j = 0; j < i; j++){
            if(maxv < price[j] + dp[j - i - 1]){
                maxv = price[j] + dp[j - i - 1];
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
    return{dp[n],solcut};
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
        known[u] = true;
        cout << u << endl;
        for(int i = adj.size() -1; i >= 0; --i){
            int neighbors = adj[u][i];
            if(!known[neighbors])
                sk.push(neighbors);
        }
    }
}

bool subset(int* arr, int n, int target){
    bool** dp = new bool*[n + 1];
    for(int i = 0; i < n; i++)
        dp[i] = new bool[target + 1];
    for(int i = 1; i < n; i++)
        dp[i][0] = true;
    for(int j = 0; j < n; j++)
        dp[j][0] = false;
    for(int i = 0; i < n; i++){
        for(int sum = 1; sum < target; sum++){
            if(arr[i] < target)
                dp[i][sum] = dp[i-1][sum] || dp[i-1][sum-arr[i-1]];
            else
                dp[i][sum] = dp[i-1][sum];
        }
    }
    bool result = dp[n][target];
    for(int i  = 0; i < n; i++)
        delete[] dp[i];
    delete[] dp;
    return result;
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

int kadan(int* arr, int n){
    int maxnum = INT_MIN;
    int maxthus = 0;
    int* ptr = arr;
    for(int i = 0; i < n; i++){
        maxthus += *ptr;
        if(maxnum > maxthus)
            maxnum = maxthus;
        if(maxthus <= 0)
            maxthus = 0;
    }
    return maxnum;
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
    for(int i = n/2-1; i >=0; --i)
        heapify(arr,n,i);
    for(int i = n -1; i >= 0; --i){
        swap(&arr[0],&arr[i]);
        heapify(arr,i,0);
    }
}

void insert(vector<int>& v){
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

void bucket(vector<int>& v, int numofbucket = 10){
    if(v.empty()) return;
    int minv = v[0];
    int maxv = v[0];
    for(auto& elem  : v){
        if(elem < minv) minv = elem;
        if(elem > maxv) maxv = elem;
    }
    if(minv == maxv) return;
    int range = (maxv - minv)/static_cast<int>(numofbucket);
    if(range == 0) range = 1;
    vector<vector<int>> buckets(numofbucket);
    for(auto& elem : v){
        int bucketindex = min(static_cast<int>((elem-minv)/range),numofbucket-1);
        buckets[bucketindex].push_back(elem);
    }
    int index = 0;
    for(auto& bucket: buckets){
        insert(bucket);
        for(auto& elem : v){
            v[index++] = elem;
        }
    }
}

int fibtd(int n, vector<int>& v){
    if(n <= 1) return n;
    if(v[n]!=-1) return v[n];
    v[n] = fibtd(n -1,v) + fibtd(n-2,v);
    return v[n];
}

int fibbu(int n){
    if(n <= 1) return n;
    vector<int> v(n+1);
    v[0] = 0;
    v[1] = 1;
    for(int i = 2; i <= n; i++){
        v[i] = v[n-1] + v[-2];
    }
    return v[n];
}

int fibspc(int n){
    if(n <= 1) return n; 
    int prev2, prev1, crrt;
    for(int i = 2; i <= n; i++){
        crrt = prev2 + prev1;
        prev2 = prev1;
        prev1 = crrt;
    }
    return prev1;
}

void bubble(vector<int>& v){
    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v.size()-1; j++){
            if(v[j + 1] > v[j]){
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
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
        int mid = partition(v,low,high);
        qs(v,low,mid-1);
        qs(v,mid+1,high);
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
    int i =0, j = 0, k = left;
    while(i < n1 && j < n2){
        if(l[i] < r[j]){
            v[k] = l[i];
            i++;
        } else {
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
    if(v.size() <= 1) return;
    merge(v,left,right);
}

bool cyclic(int node, const vector<pair<int,int>>& edges){
    undirectDetec ud(node);
    for(auto& [u,v] : edges){
        if(!ud.unionset(u,v))
            return true;
    }
    return false;
}

int knapsack(int capacity, int n, int* wt, int* v){
    int** dp = new int*[n + 1];
    for(int i = 0; i <= n; i++)
        dp[i] = new int[capacity + 1];
    for(int i = 0; i <= n; ++i){
        for(int w = 0; w <= capacity; ++w){
            if(i==0 && w==0)
                dp[i][w] = 0;
            else if(wt[i-1]<=w)
                dp[i][w] = (v[i-1] + dp[i-1][w-wt[i-1]] > dp[i-1][w]) ? v[i-1] + dp[i-1][w-wt[i-1]] : dp[i-1][w];
            else
                dp[i][w] = dp[i-1][w];
        }
    }
    int result = dp[n][capacity];
    for(int i = 0; i <= n; i++) delete[] dp[i];
    delete[]dp;
    return result;
}



int main(){
    return 0;
}