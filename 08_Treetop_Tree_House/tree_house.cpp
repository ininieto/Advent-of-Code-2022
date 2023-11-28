/*
    Advent of Code 2022 - 08.12.2022

    Link to the problem: https://adventofcode.com/2022/day/8

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <vector>
#include <fstream>


bool checkVisibleTopLeft(std::vector<int> row, int treeIndex, int& visibleTrees){

    for(int i = 0; i < treeIndex; i++){
        if(row[i] >= row[treeIndex])  // If there is a taller tree
            return false;
    }
    visibleTrees ++;
    return true;
}

bool checkVisibleBottomRight(std::vector<int> row, int treeIndex, int& visibleTrees){    // I could probably compact the two fucntions in 1 but meh

    int len = row.size();

    for(int i = treeIndex + 1; i < len; i++){
        if(row[i] >= row[treeIndex])  // If there is a taller tree
            return false;
    }
    visibleTrees ++;
    return true;
}

int main(){

    const int nrows = 99, ncols = 99;
    std::vector <std::vector<int>> rows(nrows, std::vector<int>(ncols));    // 2D vector with all the rows
    std::vector <std::vector<int>> cols(ncols, std::vector<int>(nrows));    // 2D vector with all the cols
    int visibleTrees = 0;

    /*
    vector<vector<int>> example(nrows, vector<int>(ncols));

    example = {{3, 0, 3, 7, 3},
               {2, 5, 5, 1, 2},
               {6, 5, 3, 3, 2},
               {3, 3, 5, 4, 9},
               {3, 5, 3, 9, 0}};
    */

    // Read input data from txt file
    std::fstream inputfile;

    inputfile.open("input.txt", std::ios::in);
    if(inputfile.is_open()){
        int i = 0;
        std::string tp;
        while(getline(inputfile, tp)){
            for(int j = 0; j < ncols; j++){
                rows[i][j] = tp[j] - '0';   // Fill in rows vector
                cols[j][i] = tp[j] - '0';   // Fill in cols vector
            }
            i++;
        }
    }
    inputfile.close();

    // Calculate trees on the edges
    visibleTrees += 2*nrows + 2*(ncols - 2);

    // Check visible
    
    for (int i = 1; i < nrows - 1; i++){    // Check only the inner trees
        std::vector<int> row = rows[i];
        for(int j = 1; j < ncols - 1; j++){
            std::vector<int> col = cols[j];
            if (checkVisibleTopLeft(row, j, visibleTrees))          // Left
                continue;
            else if (checkVisibleBottomRight(row, j, visibleTrees)) // Right
                continue;
            else if (checkVisibleTopLeft(col, i, visibleTrees))     // Top
                continue;
            else if (checkVisibleBottomRight(col, i, visibleTrees)) // Bottom
                continue;
        }
    }

    std::cout << "There are " << visibleTrees << " visible trees" << '\n';

    return 0;
}