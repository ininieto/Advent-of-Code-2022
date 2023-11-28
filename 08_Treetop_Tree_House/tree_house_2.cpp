/*
    Advent of Code 2022 - 08.12.2022

    Link to the problem: https://adventofcode.com/2022/day/8

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <vector>
#include <fstream>

void countScoreTopLeft(std::vector<int> row, int treeIndex, int& scenicScore){

    int tempScore = 0;

    for(int i = treeIndex - 1; i >= 0; i--){
        if(row[i] < row[treeIndex])
            tempScore ++;
        else{
            tempScore ++;
            break;
        }
    }

    scenicScore *= tempScore;
}

void countScoreBottomRight(std::vector<int> row, int treeIndex, int& scenicScore){    // I could probably compact the two fucntions in 1 but meh

    int len = row.size();
    int tempScore = 0;

    for (int i = treeIndex + 1; i < len; i++){
        if (row[i] < row[treeIndex])
            tempScore ++;
        else{
            tempScore ++;
            break;
        }
    }

    scenicScore *= tempScore;
}

int main(){

    
    const int nrows = 99, ncols = 99;
    std::vector <std::vector<int>> rows(nrows, std::vector<int>(ncols));    // 2D vector with all the rows
    std::vector <std::vector<int>> cols(ncols, std::vector<int>(nrows));    // 2D vector with all the cols
    int highestScenicScore = 0;

    /*
    const int nrows = 5, ncols = 5;
    vector<vector<int>> exampleRows(nrows, vector<int>(ncols));
    vector<vector<int>> exampleCols(ncols, vector<int>(nrows));

    exampleRows = {{3, 0, 3, 7, 3},
                   {2, 5, 5, 1, 2},
                   {6, 5, 3, 3, 2},
                   {3, 3, 5, 4, 9},
                   {3, 5, 3, 9, 0}};

    exampleCols = {{3, 2, 6, 3, 3},
                   {0, 5, 5, 3, 5},
                   {3, 5, 3, 5, 3},
                   {7, 1, 3, 4, 9},
                   {3, 2, 2, 9, 0}};
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

    // Check visible
    
    for (int i = 1; i < nrows - 1; i++){    // Check only the inner trees
        std::vector<int> row = rows[i];
        for(int j = 1; j < ncols - 1; j++){
            int scenicScore = 1;
            std::vector<int> col = cols[j];
            countScoreTopLeft(row, j, scenicScore);     // Left
            countScoreBottomRight(row, j, scenicScore); // Right
            countScoreTopLeft(col, i, scenicScore);     // Top
            countScoreBottomRight(col, i, scenicScore); // Bottom

            if(scenicScore > highestScenicScore)
                highestScenicScore = scenicScore;
        }
    }
    std::cout << "The highest scenic score is " << highestScenicScore << '\n';
    return 0;
}