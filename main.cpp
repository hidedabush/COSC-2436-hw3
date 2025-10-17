#include <fstream>
#include <iostream>
#include <vector>
#include "ArgumentManager.h"

using namespace std;

bool IS_VALID_MOVE(int x, int y, int l, int h, int** grid) {
    return (x >= 0 && x < l && y >= 0 && y < h && grid[y][x] == 0);
}

bool SolveKT(int x, int y, int movei, int** grid, int l, int h, int moveX[], int moveY[], int hole) {
    if(movei == l * h - hole) {
        return true;
    }
    
    return false;
}



int main(int argc, char *argv[]) {
    ArgumentManager am(argc, argv);
    //ifstream fin(am.get("input"));
    //ofstream fout(am.get("output"));
    ifstream fin("input3.txt");
    ofstream fout("output1.txt");

    int l = 0, h = 0;
    fin >> l >> h; // length and height of the grid
    int** grid = new int*[h];
    for (int i = 0; i < h; i++) {
        grid[i] = new int[l];
        for (int j = 0; j < l; j++) {
            grid[i][j] = 0; // initialize grid cells to 0
        }
    }

    int startX = 0, startY = 0;
    fin >> startX >> startY; // starting coordinates

    int hole = 0;
    fin >> hole; // number of holes
    for(int i = 0; i < hole; i++) {
        int holeX = 0;
        int holeY = 0;
        fin >> holeX >> holeY;
        grid[holeY][holeX] = 1; // mark hole positions in the grid
    } // create array of holes

    //horse moves
    int moveX[8] = {2, -1, -2, 1, 1, -2, -1, 2};
    int moveY[8] = {1, 2, -1, -2, 2, 1, -2, -1};

    //declare starting pos
    grid[startY][startX] = 1;
    
    //solve knight tour
    

    //print grid
    if(SolveKT(startX, startY, 1, grid, l, h, moveX, moveY, hole)){
        cout << "A closed tour exists!" << endl;
        for(int i = 0; i < h; i++){
            
            for(int j = 0; j < l; j++){
                cout << "+--";
            }

            cout << "+" << endl;

            for(int j = 0; j < l; j++){
                if(grid[i][j] == 1 && (i != startY || j != startX)){
                    cout << "|xx";
                }else{
                    cout << "| " << grid[i][j];
                }
            
            }
            cout << "|" << endl;
        }
        for(int j = 0; j < l; j++){
                cout << "+--";
            }
            cout << "+" << endl;
    }else{
        cout << "A closed tour does not exist!" << endl;
    }

    
    for(int i = 0; i < h; i++) {
        delete[] grid[i];
    }
    delete[] grid;
    fin.close();
    fout.close();
    return 0;
}

