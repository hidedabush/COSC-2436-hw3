#include <fstream>
#include <iostream>
#include <vector>
#include "Queue.h"
#include "ArgumentManager.h"

using namespace std;


bool checkTourExist(int**grid){
    for(int i = 0; i < sizeof(grid); i++){
        for(int j = 0; j < sizeof(grid[i]); j++){
            if(grid[i][j] == 0){
                return false;
            }
        }
    }
    return true;

}

int main(int argc, char *argv[]) {
    ArgumentManager am(argc, argv);
    ifstream fin(am.get("input"));
    ofstream fout(am.get("output"));

    int l = 0, h = 0;
    fin >> l >> h; // length and height of the grid
    int** grid = new int*[h];
    for (int i = 0; i < h; i++) {
        grid[i] = new int[l];
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
    int horseMoves[8][2] = {
        {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
        {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
    };




    //print grid
    if(checkTourExist(grid)){
        fout << "A closed tour exists!" << endl;
        for(int i = 0; i < h; i++){
            fout << "+--+--+--+" << endl;
            for(int j = 0; j < l; j++){
                fout << "| " << grid[i][j];
            }
            fout << "|" << endl;
        }
        fout << "+--+--+--+" << endl;
    }else{
        fout << "A closed tour does not exist!" << endl;
    }

    
    for(int i = 0; i < h; i++) {
        delete[] grid[i];
    }
    delete[] grid;
    fin.close();
    fout.close();
    return 0;
}

