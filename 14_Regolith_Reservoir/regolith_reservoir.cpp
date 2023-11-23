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
    std::cout << '\n';
}

void placeRocksInGrid(std::vector<std::vector<std::pair<int, int>>> rockPositions, std::vector<std::vector<char>> &grid, int offset){

    for(auto line: rockPositions){
        for(int i = 1; i < line.size(); i++){

            std::pair<int, int> prevCorner = line[i - 1];
            std::pair<int, int> corner = line[i];

            int xDiff = abs(corner.first - prevCorner.first);

            if(xDiff == 0){

                int x = corner.first - offset;
                int yStart = (prevCorner.second < corner.second) ? prevCorner.second : corner.second;
                int yEnd = (prevCorner.second < corner.second) ? corner.second + 1 : prevCorner.second + 1;
                 
                for(int y = yStart; y < yEnd; y++) grid[y][x] = '#';
            }
            else{   // If yDiff == 0
                int y = corner.second;
                int xStart = (prevCorner.first < corner.first) ? prevCorner.first : corner.first;
                int xEnd = (prevCorner.first < corner.first) ? corner.first + 1: prevCorner.first + 1;

                for(int x = xStart - offset; x < xEnd - offset; x++) grid[corner.second][x] = '#';
            }
        }  
    }
}

/*  
    This function will check whether the sand block can fall or will stay still
    The function will call itself recursively until the block stops
*/
bool sandFlow(std::pair<int, int> initialPosition, std::vector<std::vector<char>> &grid){

    int limHigh = grid.size() - 2;
    int limWide = grid[0].size() - 2;

    if(initialPosition.first > limHigh || initialPosition.second < 0 || initialPosition.second > limWide)   // If out of bounds
        return true;

    if(grid[initialPosition.first + 1][initialPosition.second] == '.')             // Check bottom position
        return sandFlow(std::make_pair(initialPosition.first + 1, initialPosition.second), grid);
    else if(grid[initialPosition.first + 1][initialPosition.second - 1] == '.')    // Check bottom-left position
        return sandFlow(std::make_pair(initialPosition.first + 1, initialPosition.second - 1), grid);
    else if(grid[initialPosition.first + 1][initialPosition.second + 1] == '.')    // Check bottom-right position
        return sandFlow(std::make_pair(initialPosition.first + 1, initialPosition.second + 1), grid);

    // Place the sandball if the ball cannot move more 
    grid[initialPosition.first][initialPosition.second] = 'o';
    return false;
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

    int high = maxY + 1;    
    int wide = maxX - minX + 1;

    // This will be our reference
    int offset = minX - 1;  // We establish a margin on each side. Substracting one will center the grid
    
   // Define the grid 
    std::vector<std::vector<char>> grid(high + 1, std::vector<char>(wide + 2)); // Added margins: one row down and one column on each side

    // Set the grid to empty (in this case represented with .)
    for (auto &row : grid){
        for (auto &element : row){
            element = '.';
        }
    }

    // Set the Sand Source
    std::pair<int, int> sourcePosition = std::make_pair(0, 500 - offset);
    grid[sourcePosition.first][sourcePosition.second] = '+';

    // Set the rocks in the grid
    placeRocksInGrid(rockPositions, grid, offset);

    // Big loop
    int numBalls = 0;
    while(!sandFlow(sourcePosition, grid)) numBalls ++;

    // Log the results
    printGrid(grid);
    std::cout << "The result is " << numBalls << '\n';

    return 0;
}

