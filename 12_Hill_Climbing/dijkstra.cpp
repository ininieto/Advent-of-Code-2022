#include "dijkstra.h"

#include <iostream>
#include <vector>


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

// This function will be recursive. It will be called for the root node, and then, it
// will call itself for each child

void dijkstra(Node* currentNode, std::vector<std::vector <int>> grid){

    // Debug
    std::cout << "Soy el nodo de " << currentNode->getPosition().first << ", " << currentNode->getPosition().second << ". Mi valor es " << currentNode->getValue() << '\n';


    // Store in a vector all the surroundings
    std::vector<std::pair<int, int>> surroundings = getSurroundings(currentNode, NROWS, NCOLS);

    // Scan the surroundings and get the ones eligible to jump into
    std::vector<std::pair<int, int>> possibleJumps = getPossibleJumps(currentNode, surroundings, grid);

    // Create the children nodes
    for(auto jumpPosition : possibleJumps){
        new Node(currentNode, jumpPosition, grid[jumpPosition.first][jumpPosition.second], INFINITY);
    }

    

    // Store all the child nodes in a vector
    std::vector<Node*> children = currentNode->getChildren();

    // Calculate the distance for every child
    for(auto &child : children){
        child->setMinDistance(currentNode->getMinDistance() + 1);  // minimo entre el nuevo calculado y el que ya tenía
        child->setChecked();
        dijkstra(child, grid); // ONLY DEBUG
    }

    // Sort the children by its distance

    // Call this function for each of those childs

    // My concern is: will it be possible that for the same position various nodes
    // will be created? If I reach an element, I create a Node*. But if I reach the
    // same position using a different path, will I be able to identify it and use the
    // same Node* ? 

    // Also, when will I stop? How can I assure that I have reached the End Node*? 
    // I will probably need to define a function checkEndNode() or something similar

    // When should I set a Node* as checked?
}