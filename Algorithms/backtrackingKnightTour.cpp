#include <iostream>
#include <vector>
#include <iomanip> // for setw

using namespace std;

const int N = 8; // Board size: 8x8
const int dx[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
const int dy[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

// Function to check if (x, y) is a valid move
inline bool isValid(int x, int y, const vector<vector<int>>& board) {
    return x >= 0 && y >= 0 && x < N && y < N && board[x][y] == -1;
}

// Recursive backtracking function
bool solveKnightTour(int x, int y, int moveCount, vector<vector<int>>& board) {
    if (moveCount == N * N) return true; // All cells visited

    for (int i = 0; i < 8; ++i) {
        int nextX = x + dx[i];
        int nextY = y + dy[i];

        if (isValid(nextX, nextY, board)) {
            board[nextX][nextY] = moveCount;

            if (solveKnightTour(nextX, nextY, moveCount + 1, board))
                return true; // Found solution path

            board[nextX][nextY] = -1; // Backtrack
        }
    }
    return false; // No valid move found from this position
}

// Entry point to setup and solve Knight's Tour
bool knightTour() {
    vector<vector<int>> board(N, vector<int>(N, -1)); // Initialize board with -1
    board[0][0] = 0; // Start at top-left corner

    if (!solveKnightTour(0, 0, 1, board)) {
        cout << "No solution found.\n";
        return false;
    }

    // Print solution
    for (const auto& row : board) {
        for (int cell : row)
            cout << setw(2) << cell << " ";
        cout << '\n';
    }
    return true;
}

int main() {
    knightTour();
    return 0;
}
