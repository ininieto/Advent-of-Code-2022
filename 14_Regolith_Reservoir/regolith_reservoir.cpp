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


// Function to split a std::string by a specific delimitator
std::vector<std::string> split(std::string text, std::string delim){

    std::vector<std::string> splittedText;
    size_t pos = 0;
    std::string token;

    while((pos = text.find(delim)) != std::string::npos){
        token = text.substr(0, pos);
        splittedText.push_back(token);
        text.erase(0, pos + delim.length());
    }

    splittedText.push_back(text);// The last element is not added to the vector otherwise
    return splittedText;
}

int main(){


    std::string example = "498,4 -> 498,6 -> 496,6\n503,4 -> 502,4 -> 502,9 -> 494,9";

    // Split the string by lines
    std::vector<std::string> splittedExample = split(example, "\n");

    // Store the data in a vector

    // std::vector<std::vector<std::pair<int, int>>> rockPositions;

    for(std::string line: splittedExample){
        
        std::vector<std::string> instruction = split(line, " -> "); // Separate the 

        std::vector<std::pair<int, int>> rocks;
        for(std::string position: instruction){
            // Separate the x and y coord, convert to int and store in a vector (the line looks illegible tbh)
            rocks.push_back(std::make_pair(stoi(position.substr(0, position.find(','))), stoi(position.substr(position.find(',') + 1))));   // Store the coordinates in a vector
        }

        // It could be good to place the rocks in the grid here, but I still don't know the high/wide :( Must be done later
    }



    
    int high = 10, wide = 10; // I know it for the example, in the real problem I will need to guess this
    
    
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

