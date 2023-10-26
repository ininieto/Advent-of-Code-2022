#include <iostream>
#include <vector>
#include <fstream>

/*
    Advent of Code 2022 - 12.12.2022

    Link to the problem: https://adventofcode.com/2022/day/12

    Author of the solution: Íñigo Nieto Cuadrado

*/

/*
    Initial approach: use the ascii code of every character except for S and E
    For every position check all the surroundings (good luck with columns xd)
    Sort them and jump to the highest IF only one jump

*/

int main(){

    const int nrows = 5, ncols = 8; 

    std::string example = "Sabqponm\nabcryxxl\naccszExk\nacctuvwj\nabdefghi\n";
    std::vector<std::vector <int>> grid(nrows, std::vector<int>(ncols));
    std::pair position(0, 0);

    // Fill in the grid with the ascii values of the characters
    int stringCount = 0;

    for(int i = 0; i < nrows; i++){
        for(int j = 0; j < ncols; j++){
            if(example[stringCount] == '\n')
                stringCount ++;
            grid[i][j] = int(example[stringCount]);
            stringCount ++;
        }
    }

    std::cout << "a";




    return 0;
}