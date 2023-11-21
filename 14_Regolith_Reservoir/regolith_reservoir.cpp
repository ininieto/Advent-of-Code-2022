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
#include <fstream>
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

    if(text.length() > 0)
        splittedText.push_back(text);

    return splittedText;
}

// Read input data from txt file
std::string readInputText(std::string inputText){

    std::fstream inputfile;
    std::string inputData;

    inputfile.open(inputText, std::ios::in);
    if (inputfile.is_open()){
        std::string tp;
        while (getline(inputfile, tp)){
            inputData += tp;
            inputData += "\n";
        }
    }
    return inputData;
}

int main(){

    std::string example = "498,4 -> 498,6 -> 496,6\n503,4 -> 502,4 -> 502,9 -> 494,9\n";
    std::string inputData = readInputText("input.txt");

    // Split the string by lines
    std::vector<std::string> splittedExample = split(example, "\n");
    std::vector<std::string> splittedData = split(inputData, "\n");

    // Store the data in a vector

    std::vector<std::vector<std::pair<int, int>>> rockPositions;

    for(std::string line: splittedExample){
        
        std::vector<std::string> instruction = split(line, " -> "); 

        std::vector<std::pair<int, int>> rocks;
        for(std::string position: instruction){
            // Separate the x and y coord, convert to int and store in a vector (the line looks illegible tbh)
            rocks.push_back(std::make_pair(stoi(position.substr(0, position.find(','))), stoi(position.substr(position.find(',') + 1))));   // Store the coordinates in a vector
        }
        // Fill in the big vector
        rockPositions.push_back(rocks);
    }

    // Guess the dimensions of our grid
    int minX = INT_MAX, maxX = -1, maxY = -1;

    // Obtain the highest and lowest position of X and Y
    for(auto line: rockPositions){
        for(auto corner: line){
            if(corner.first > maxX)
                maxX = corner.first;
            if(corner.second > maxY)
                maxY = corner.second;
            if(corner.first < minX)
                minX = corner.first;
        }  
    }

    int high = maxY + 1;    // Could be possible to establish margins 
    int wide = maxX - minX + 1;
    
   // Define the grid 
    std::vector<std::vector<char>> grid(high, std::vector<char>(wide));

    // Set the grid to empty (in this case represented with .)
    for (auto &row : grid){
        for (auto &element : row){
            element = '.';
        }
    }

    // Set the Sand Source
    grid[0][6] = '+';

    // Debug: Print the grid
    for (auto &row : grid){
        for (auto &element : row){
            std::cout << element;
        }
        std::cout << '\n';
    }

    return 0;
}

