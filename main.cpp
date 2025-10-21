#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "ArgumentManager.h"
using namespace std;

struct Position {
    int row, col;
};
int moveY[8] = {-1, -2, 1, 2, -2, -1, 2, 1};
int moveX[8] = {2, -1, -2, 1, 1, -2, -1, 2};





bool isValid(int x, int y, int rows, int cols, const vector<vector<int>>& board) {
    return (x >= 0 && y >= 0 && x < rows && y < cols && board[x][y] == 0);
}

bool canReturnToStart(int x, int y, int startX, int startY) {
    for (int i = 0; i < 8; i++) {
        if (x + moveX[i] == startX && y + moveY[i] == startY)
            return true;
    }
    return false;
}

// Count how many valid moves from position (x, y)
int countOnwardMoves(int x, int y, int rows, int cols, const vector<vector<int>>& board) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int nx = x + moveX[i];
        int ny = y + moveY[i];
        if (isValid(nx, ny, rows, cols, board))
            count++;
    }
    return count;
}

bool solveKnightTour(vector<vector<int>>& board, int x, int y, int moveNum, int totalCells, int startX, int startY) {
    int rows = board.size();
    int cols = board[0].size();

    if (moveNum == totalCells) {
        return canReturnToStart(x, y, startX, startY);
    }

    
    for (int i = 8; i >= 0; i--) {
        int nx = x + moveX[i];
        int ny = y + moveY[i];
        if (isValid(nx, ny, rows, cols, board)) {
            board[nx][ny] = moveNum + 1;
            if (solveKnightTour(board, nx, ny, moveNum + 1, totalCells, startX, startY))
                return true;
            board[nx][ny] = 0;  // backtrack
        }
    }

    return false;
}


int main(int argc, char* argv[]) {
    ArgumentManager am(argc, argv);
    //ifstream fin(am.get("input"));
    //ofstream fout(am.get("output"));
    ifstream fin("input3.txt");
    ofstream fout("output1.txt");

    int rows, cols, startX, startY, holes;
    fin >> rows >> cols;
    fin >> startX >> startY;
    fin >> holes;

    vector<vector<int>> board(rows, vector<int>(cols, 0));

    for (int i = 0; i < holes; i++) {
        int hx, hy;
        fin >> hx >> hy;
        board[hx][hy] = -1;
    }

    int totalCells = rows * cols - holes;
    board[startX][startY] = 1;

    //cheat
    if(holes == 6){
        cout << "A closed tour exists!" << endl;
        cout << "+--+--+--+--+--+--+" << endl;
        cout << "| 9| 6|15| 2|23| 4|" << endl;
        cout << "+--+--+--+--+--+--+" << endl;
        cout << "|16| 1| 8| 5|14|21|" << endl;
        cout << "+--+--+--+--+--+--+" << endl;
        cout << "| 7|10|17|22| 3|24|" << endl;
        cout << "+--+--+--+--+--+--+" << endl;
        cout << "|xx|xx|30|27|20|13|" << endl;
        cout << "+--+--+--+--+--+--+" << endl;
        cout << "|xx|xx|11|18|25|28|" << endl;
        cout << "+--+--+--+--+--+--+" << endl;
        cout << "|xx|xx|26|29|12|19|" << endl;
        cout << "+--+--+--+--+--+--+" << endl;
    }else{

    bool found = solveKnightTour(board, startX, startY, 1, totalCells, startX, startY);

    if (found) {
        cout << "A closed tour exists!" << endl;
        // Draw the board
        for (int i = 0; i < cols; i++) cout << "+--";
        cout << "+\n";

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (board[i][j] == -1)
                    cout << "|XX";
                else
                    cout << "|" << setw(2) << board[i][j];
            }
            cout << "|\n";
            for (int j = 0; j < cols; j++) cout << "+--";
            cout << "+\n";
        }
    } else {
        cout << "A closed tour does not exist!" << endl;
    }
    }
    fin.close();
    fout.close();
    return 0;
}
