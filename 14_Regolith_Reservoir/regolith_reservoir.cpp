/*
    Advent of Code 2022 - 14.12.2022

    Link to the problem: https://adventofcode.com/2022/day/14

    Author of the solution: Íñigo Nieto Cuadrado

*/

/*
    First approach:
        - At first I need to read the instructions, and like that I can guess the wide and high of the grid
        - To read the instructions I guess I'll store the values in std::pairs
        - With that done it should be really easy to place # in the grid
        - With that done, we can jump to the algorithm. I think I will do it recursively
        - I'm unsure about how to determine if we fall in abyss. Maybe if y_coord < lowest_rock

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

