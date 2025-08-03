#include<iostream>
#include<vector>
#include<stack>
#include<queue>

using namespace std;

void bfs(int start, vector<vector<int>>& adj, vector<bool>& visited){
    queue<int> q;
    q.push(start);
    visited[start] = true;
    cout << "BFS Traversal: " << endl;

    while(!q.empty()){
        int u = q.front();
        q.pop();
        cout << u << " " << endl;
        for(auto& neighbors : adj[u]){
            if(!visited[neighbors]){
                visited[neighbors] = true;
                q.push(neighbors);
            }
        }
    }
    cout << endl;
}

void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited){
    visited[node] = true;
    for(auto& neighbors : adj[node]){
        if(!visited[neighbors]){
            dfs(node, adj, visited);
        }
    }
}

void dfsIT(int node, vector<vector<int>>& adj, vector<bool>& visited){
    stack<int> stk;
    stk.push(node);
    visited[node] = true;
    cout << node << " " << endl;
    while(!stk.empty()){
        int u = stk.top();
        stk.pop();
        if(visited[u]) continue;
        visited[u] = true;
        cout << node << " "; 
        for(int i = adj[u].size(); i >= 0; --i){
            int neighbors = adj[u][i];
            if(!visited[neighbors]){
                stk.push(neighbors); 
            }
        }
    }
}

void bubblesort(vector<int>& v){
    for(int i = 0; i < v.size(); i++){
        bool swp = false;
        for(int j = 0; j < v.size()-1; j++){
            if(v[j] > v[j + 1]){
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
                swp = true;
            }
        }
    }
}

void insertion(vector<int> v){
    for(int i = 0; i < v.size(); i++){
        int key = v[i];
        int j = i + 1;
        while(v[j]>=0 && v[j] > key){
            --j;
            swap(v[i],v[j]);
        }
        v[j + 1] = key;
    }
}

void selection(vector<int>& v){
    for(int i = 0; i < v.size(); i++){
        int* min = &v[i];
        for(int j = i + 1; j < v.size(); j++){
            if(v[j] < *min){
                min = &v[j];
            }
            if(*min!=v[i]){
                swap(*min,v[i]);
            }
        }
    }
}

int partition(vector<int> v, int low, int high){
    int pvt = v[high];
    int i = low - 1;
    for(int j = low; j < high; j++){
        if(v[j] <= pvt){
            swap(v[i],v[j]);
        }
    }
    swap(v[i + 1],v[high]);
    return i + 1;
}

void qs(vector<int>& v, int low, int high){
    if(low <= high){
        int pi = partition(v,low,high);
        qs(v,low,pi-1);
        qs(v,pi+1,high);
    }
}

void fusionM(vector<int>& v, int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - left;
    vector<int> r(n1),l(n2);
    for(int i = 0; i < n1; i++)
        l[i] = v[left + 1]; 
    for(int j = 0; j < n2; j++)
        r[j] = v[mid + 1 - j];
    int i = 0, j = 0, k = left;
    while(i < n1 && j < n2){
        if(l[i] < r[j]){
            v[k] = l[i];
            i++;
        } else {
            v[k]  = r[j];
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

void msort(vector<int>&v, int left, int right){
    if(left <= left){
        int mid = left+(right - left)/2;
        msort(v,left,mid);
        msort(v,mid+1,right);
        fusionM(v, left, mid, right);
    }
}

void check(vector<int>& v, int left, int right){
    if(v.size() == 0)
        return;
    msort(v,left,right);
}

int main(){

}