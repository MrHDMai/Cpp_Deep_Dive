#include<iostream>
#include<vector>

using namespace std;

class matrix{
public:
    vector<vector<int>> a;
    matrix operator*(const matrix& other){
        matrix result;
        int n = a.size();
        int m = a[0].size();
        for(int i = 0; i < n; i++){
            vector<int>row(m);
            for(int j = 0;  j < m; j++){
                row[j] = a[i][j] * other.a[i][j];
            }
            result.a.push_back(row);
        }
        return result;
    }
};

int main(){
    int cases,k;
    cin >> cases;
    for(k = 0; k < cases; k++){
        matrix result;
        matrix x;
        matrix y;
        int m, n;
        cin >> m >> n;
        for(int i = 0; i < n; i++){
            vector<int> b(m);
            for(int j = 0; j < m; j++){
                cin >> b[j];
            }
            x.a.push_back(b);
        }
        for(int i = 0; i < n; i++){
            vector<int>b(m);
            for(int j = 0; j < m; j++){
                cin >> b[j];
            }
            y.a.push_back(b);
        }
        result = x * y;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cout << result.a[i][j] << endl;
            }
        }
    }
    return 0;
}