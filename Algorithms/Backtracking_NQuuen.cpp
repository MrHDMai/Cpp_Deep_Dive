#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>

using namespace std;

class nqueensolver{
private: 
    vector<vector<string>> solutions;
    unordered_set<int> cols, diag1, diag2; 
    vector<string> board;
    int N;

    void backtrack(int row){
        if(row == N){
            solutions.push_back(board);
            return;
        }
        for(int col = 0; col < N; col++){
            if(cols.count(col) || diag1.count(row -  col) || diag2.count(row+col))
                continue;
            //placemennt of queen on the board    
            board[row][col] = 'Q';
            cols.insert(col);
            diag1.insert(row - col);
            diag2.insert(row + col);
            //moving to the next row
            backtrack(row + 1);
            //backtracking magic
            board[row][col] = '.';
            cols.erase(col);
            diag1.erase(row - col);
            diag2.erase(row + col);
        }
    }
public:
    vector<vector<string>> queensolver(int n){
        N = n;
        board = vector<string>(n, string(n,'.'));
        backtrack(0);
        return solutions;
    }

}; 


int main(){
    int n = 8;
    nqueensolver solver;
    vector<vector<string>> solutions = solver.queensolver(n);
    cout <<"Numer of solutions for" << n << "-Queens: " << solutions.size() << "\n";
    for(const auto& solution : solutions){
        for(const string& row : solution)
            cout << row << "\n";
        cout << "\n";
    } 
    return 0;
}