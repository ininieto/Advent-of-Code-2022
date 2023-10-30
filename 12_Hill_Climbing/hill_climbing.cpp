#include <vector>

#include "utils.cpp"
#include "Node.cpp"

/*
    Advent of Code 2022 - 12.12.2022

    Link to the problem: https://adventofcode.com/2022/day/12

    Author of the solution: Íñigo Nieto Cuadrado

*/

// This function will ONLY return the adjacent elements. Won't perform any further calculation

std::vector<std::pair<int, int>> getSurroundings(std::pair<int, int> position, int nrows, int ncols){

    std::vector<std::pair<int, int>> surroundings;

    std::pair<int, int> up = std::make_pair(position.first - 1, position.second);
    std::pair<int, int> down = std::make_pair(position.first + 1, position.second);
    std::pair<int, int> left = std::make_pair(position.first, position.second - 1);
    std::pair<int, int> right = std::make_pair(position.first, position.second + 1);

    if(position == std::make_pair(0, 0)){   // Top left corner
        
        surroundings.push_back(right);
        surroundings.push_back(down); 
    }
    else if(position == std::make_pair(0, ncols - 1)){  // Top right corner

        surroundings.push_back(left);
        surroundings.push_back(down); 
    }
    else if(position == std::make_pair(nrows - 1, 0)){  // Bottom left corner

        surroundings.push_back(right);
        surroundings.push_back(up); 
    }
    else if(position == std::make_pair(nrows - 1, ncols - 1)){  // Bottom right corner

        surroundings.push_back(left); 
        surroundings.push_back(up); 
    }
    else if(position.first == 0){   // First row

        surroundings.push_back(left); 
        surroundings.push_back(right); 
        surroundings.push_back(down); 
    }
    else if(position.first == nrows - 1){   // Last row

        surroundings.push_back(left); 
        surroundings.push_back(right); 
        surroundings.push_back(up); 
    }
    else if(position.second == 0){  // First column

        surroundings.push_back(right); 
        surroundings.push_back(up); 
        surroundings.push_back(down); 
    }
    else if(position.second == ncols - 1){   // Last column

        surroundings.push_back(left); 
        surroundings.push_back(up); 
        surroundings.push_back(down); 
    }
    else{   // No weird cases
        surroundings.push_back(right); 
        surroundings.push_back(left); 
        surroundings.push_back(up); 
        surroundings.push_back(down); 
    }
    return surroundings;
}

std::pair<int, int> jump(std::pair<int, int> position, std::vector<std::pair<int, int>> surroundings, std::vector<std::vector <int>> rows){

    std::vector<int> surroundingElements;
    std::vector<std::pair<int, int>> possibleJumps;
    int currentElement = rows[position.first][position.second];
    int equalValues = -1;

    // Check which of the surrounding elements are eligible to jump
    for(auto e : surroundings){
        if(rows[e.first][e.second] == currentElement || rows[e.first][e.second] == currentElement + 1){  // We can only jump to the same value or 1 higher
            surroundingElements.push_back(rows[e.first][e.second]);
            possibleJumps.push_back(e);
        }
    }

    // Get the highest value of the possible surroundings --> will be the jump

    int highestValue = 0;

    for(auto e : surroundingElements){
        if(e > highestValue)
            highestValue = e;
        else if(e == highestValue)  // If there exist 2 (or more) elements with the same value we'll take a random one
            equalValues = e;
    }

    // Check if there are repeated values

    if(equalValues != -1){

        std::vector<std::pair<int, int>> repeatedValuesJumps;

        for(int i = 0; i < possibleJumps.size(); i++){ // Get indexes of the equal values

            if(rows[possibleJumps[i].first][possibleJumps[i].second] == equalValues)    // Get the jumps whose values are repeated
                repeatedValuesJumps.push_back(possibleJumps[i]);
        }

        // Take a random one
        srand((unsigned) time(NULL));   // Generate a random seed
        int index = rand() % repeatedValuesJumps.size();
        return possibleJumps[index];
    }

    // Return the position associated to the highest value

    for(auto e : possibleJumps){
        if(rows[e.first][e.second] == highestValue)
            return e;
    }

    return position; // In case there are no possible jumps, stay
}

int main(){

    const int nrows = 5, ncols = 8; 
    //const int nrows = 41, ncols = 66;
    int jumps = 0;

    std::string example = "Sabqponm\nabcryxxl\naccszExk\nacctuvwj\nabdefghi\n";
    std::string inputData = readInputText("input.txt");
    std::vector<std::vector <int>> rows(nrows, std::vector<int>(ncols));
    std::pair position(-1, -1), startPosition(-1, -1), endPosition(-1, -1);

    inputData = example;

    // Fill in the rows and cols vectors with the ascii values of the characters
    int stringCount = 0;

    for(int i = 0; i < nrows; i++){
        for(int j = 0; j < ncols; j++){

            if(inputData[stringCount] == '\n')
                stringCount ++;

            if(inputData[stringCount] == 'S'){
                startPosition = std::make_pair(i, j);
                rows[i][j] = int('a') - 1;
                stringCount ++;
                continue;
            }
                
            if(inputData[stringCount] == 'E'){
                endPosition = std::make_pair(i, j);
                rows[i][j] = int('z') + 1;
                stringCount ++;
                continue;
            }
            rows[i][j] = int(inputData[stringCount]);
            stringCount ++;
        }
    }

    position = startPosition;

    // Crete the root node
    Node* Start = new Node(NULL, startPosition, int('a') - 1);

    // Disclaimer: Right now it is not working, as the checkedPositions map has been deleted

    // Main loop
    while (position != endPosition){

        // Store in a vector all the surroundings
        std::vector<std::pair<int, int>> surroundings = getSurroundings(position, nrows, ncols);

        // Check the surroundings and decide a jump
        std::pair<int, int> newPosition = jump(position, surroundings, rows);
    
        jumps++;
        position = newPosition;
    }
    
    std::cout << jumps << " jumps";

    return 0;
}