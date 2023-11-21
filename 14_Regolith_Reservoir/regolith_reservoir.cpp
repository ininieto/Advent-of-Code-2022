/*
    Advent of Code 2022 - 14.12.2022

    Link to the problem: https://adventofcode.com/2022/day/14

    Author of the solution: Íñigo Nieto Cuadrado

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

void printGrid(std::vector<std::vector<char>> grid){

    for(int i = 0; i < grid.size(); i++){
        std::cout << i << ' ';
        for(int j = 0; j < grid[i].size(); j++){
            std::cout << grid[i][j];
        }
        std::cout << '\n';
    }
}

void placeRocksInGrid(std::vector<std::vector<std::pair<int, int>>> rockPositions, std::vector<std::vector<char>> &grid, int conversion){

    for(auto line: rockPositions){
        for(int i = 1; i < line.size(); i++){

            std::pair<int, int> prevCorner = line[i - 1];
            std::pair<int, int> corner = line[i];

            int xDiff = abs(corner.first - prevCorner.first);

            if(xDiff == 0){

                int x = corner.first - conversion;
                int yStart = (prevCorner.second < corner.second) ? prevCorner.second : corner.second;
                int yEnd = (prevCorner.second < corner.second) ? corner.second + 1 : prevCorner.second + 1;
                 
                for(int y = yStart; y < yEnd; y++){
                    grid[y][x] = '#';
                }
            }
            else{   // If yDiff == 0
                int y = corner.second;
                int xStart = (prevCorner.first < corner.first) ? prevCorner.first : corner.first;
                int xEnd = (prevCorner.first < corner.first) ? corner.first + 1: prevCorner.first + 1;

                for(int x = xStart - conversion; x < xEnd - conversion; x++){
                    grid[corner.second][x] = '#';
                }
            }
        }  
    }
}

int main(){

    std::string example = "498,4 -> 498,6 -> 496,6\n503,4 -> 502,4 -> 502,9 -> 494,9\n";
    std::string inputData = readInputText("input.txt");

    // Split the string by lines
    std::vector<std::string> splittedExample = split(example, "\n");
    std::vector<std::string> splittedData = split(inputData, "\n");

    // Store the data in a vector

    std::vector<std::vector<std::pair<int, int>>> rockPositions;

    for(std::string line: splittedData){
        
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
    int conversion = minX;
    
   // Define the grid 
    std::vector<std::vector<char>> grid(high, std::vector<char>(wide));

    // Set the grid to empty (in this case represented with .)
    for (auto &row : grid){
        for (auto &element : row){
            element = '.';
        }
    }

    // Set the Sand Source
    grid[0][500 - conversion] = '+';


    // Set the rocks in the grid
    placeRocksInGrid(rockPositions, grid, conversion);

    printGrid(grid);


    return 0;
}

