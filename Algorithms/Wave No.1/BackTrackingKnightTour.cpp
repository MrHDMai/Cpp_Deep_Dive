#include<iostream>
#include<vector>
#include<iomanip>

using namespace std;

const int N = 8;
const int dx[8] = {1,2,-1,-2,-2,-1,1,2};
const int dy[8] = {1,2,2,1,-1,-2,-2,-1};

inline bool isvalid(int x, int y, const vector<vector<int>>& board){
    return x>= 0 && y > 0 && x < N && y < N && board[x][y] == -1;
}

bool solveknighttour(int x, int y, int movecount, vector<vector<int>>& board){
    if(movecount == N * N - 1) return true;
    for(int i = 0; i < 8; i++){
        int nextX = x + dx[i];
        int nextY = y + dy[i];

        if(isvalid(nextX,nextY, board)){
            board[nextX][nextY] = movecount;
            if(solveknighttour(nextX,nextY,movecount + 1, board))
                return true;
            board[nextX][nextY] = -1;
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
    knighttour();
    return 0;

}