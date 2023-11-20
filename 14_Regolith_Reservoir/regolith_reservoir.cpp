/*
    Advent of Code 2022 - 14.12.2022

    Link to the problem: https://adventofcode.com/2022/day/14

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <vector>

int main(){

    int high = 10; // I know it for the example, in the real problem I will need to guess this
    int wide = 10;

    std::string example = "498,4 -> 498,6 -> 496,6\n503,4 -> 502,4 -> 502,9 -> 494,9\n";

    std::vector<std::vector<char>> grid(high, std::vector<char>(wide));

    // Set the grid to empty
    for (auto &row : grid){
        for (auto &element : row){
            element = '.';
        }
    }

    // Set the Sand Source
    grid[0][6] = '+';

    


    

    return 0;
}

