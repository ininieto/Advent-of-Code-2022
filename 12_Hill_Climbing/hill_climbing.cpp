#include <vector>

#include "utils.cpp"
#include "Node.cpp"

/*
    Advent of Code 2022 - 12.12.2022

    Link to the problem: https://adventofcode.com/2022/day/12

    Author of the solution: Íñigo Nieto Cuadrado

*/

/*
    Current approach: Define a graph (kinda tree) where the root node is the Start node.
    The possible jumps are its children nodes. These nodes will have assigned the value (letter).

    Must go through all the graph following the Dijkstra algorithm: taken a node, must check
    all the children. Update the current distance until this point if necessary. When the end is
    reached, the minimum number of steps is already assigned to the end node. 
    
    In case we needed it, it could be possible to traverse the way backwards to check the complete
    path that minimizes the number of steps

*/

// This function will ONLY return the adjacent elements. Won't perform any further calculation

std::vector<std::pair<int, int>> getSurroundings(Node* currentNode, int nrows, int ncols){

    std::pair<int, int> position = currentNode->getPosition();
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

// Check the surroundings of the current node and decide which ones are eligible to jump into

std::vector<std::pair<int, int>> getPossibleJumps(Node* currentNode, std::vector<std::pair<int, int>> surroundings, std::vector<std::vector <int>> grid){

    std::pair<int, int> currentPosition = currentNode->getPosition();
    std::vector<std::pair<int, int>> possibleJumps;
    int currentElement = grid[currentPosition.first][currentPosition.second];

    // Check which of the surrounding elements are eligible to jump
    for(auto e : surroundings){
        if((grid[e.first][e.second] == currentElement || grid[e.first][e.second] == currentElement + 1) && !currentNode->getChecked())  // We can only jump to the same value or 1 higher
            possibleJumps.push_back(e);
    }

    return possibleJumps;
}

std::pair<int, int> jump(std::pair<int, int> position, std::vector<std::pair<int, int>> surroundings, std::vector<std::vector <int>> grid){

    int equalValues = -1;

    // Get the highest value of the possible surroundings --> will be the jump

    /*

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

            if(grid[possibleJumps[i].first][possibleJumps[i].second] == equalValues)    // Get the jumps whose values are repeated
                repeatedValuesJumps.push_back(possibleJumps[i]);
        }

        // Take a random one
        srand((unsigned) time(NULL));   // Generate a random seed
        int index = rand() % repeatedValuesJumps.size();
        return possibleJumps[index];
    }

    // Return the position associated to the highest value

    for(auto e : possibleJumps){
        if(grid[e.first][e.second] == highestValue)
            return e;
    }
    */

    return position; // In case there are no possible jumps, stay
}

int main(){

    const int nrows = 5, ncols = 8; 
    //const int nrows = 41, ncols = 66;
    int jumps = 0;

    std::string example = "Sabqponm\nabcryxxl\naccszExk\nacctuvwj\nabdefghi\n";
    std::string inputData = readInputText("input.txt");
    std::vector<std::vector <int>> grid(nrows, std::vector<int>(ncols));
    std::pair startPosition(-1, -1), endPosition(-1, -1);

    inputData = example;

    // Fill in the grid vector with the ascii values of the characters
    int stringCount = 0;

    for(int i = 0; i < nrows; i++){
        for(int j = 0; j < ncols; j++){

            if(inputData[stringCount] == '\n')
                stringCount ++;

            if(inputData[stringCount] == 'S'){
                startPosition = std::make_pair(i, j);
                grid[i][j] = int('a') - 1;
                stringCount ++;
                continue;
            }
                
            if(inputData[stringCount] == 'E'){
                endPosition = std::make_pair(i, j);
                grid[i][j] = int('z') + 1;
                stringCount ++;
                continue;
            }
            grid[i][j] = int(inputData[stringCount]);
            stringCount ++;
        }
    }

    // Crete the root node
    Node* startNode = new Node(NULL, startPosition, int('a') - 1, 0);
    Node *currentNode = startNode;

    // Disclaimer: Right now it is not working, as the checkedPositions map has been deleted

    // Main loop
    while (currentNode->getPosition() != endPosition){

        // Store in a vector all the surroundings
        std::vector<std::pair<int, int>> surroundings = getSurroundings(currentNode, nrows, ncols);

        // Scan the surroundings and get the ones eligible to jump into
        std::vector<std::pair<int, int>> possibleJumps = getPossibleJumps(currentNode, surroundings, grid);

        // Create the children nodes
        for(auto jumpPosition : possibleJumps){
            new Node(currentNode, jumpPosition, grid[jumpPosition.first][jumpPosition.second], currentNode->getMinDistance() + 1);
        }

        /*
        // Check the surroundings and decide a jump
        std::pair<int, int> newPosition = jump(currentNode->getPosition(), surroundings, grid);
        */

       currentNode->setChecked();   // The node is already checked. No need to check it again

       // Iterate all over the children 
    
        jumps++;
        // position = newPosition;
        // I already must have created the children nodes. I want something like currentNode = child;
    }
    
    std::cout << jumps << " jumps";

    return 0;
}