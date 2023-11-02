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
        if(grid[e.first][e.second] == currentElement || grid[e.first][e.second] == currentElement + 1)  // We can only jump to the same value or 1 higher
            possibleJumps.push_back(e);
    }

    return possibleJumps;
}

// I need a function to check if a node already exists given the position
bool checkIfNodeExists(Node* startNode, Node* currentNode, std::pair<int, int> targetPosition){


    // Take the children of the start node
    std::vector<Node*> children = startNode->getChildren();

    std::vector<bool> visited;

    // Iterate all over the children

    for (auto child : children){

        if (child->getPosition() == targetPosition)
            return true;
    }

    return false;
}

// This function will be recursive. It will be called for the root node, and then, it
// will call itself for each child

int dijkstra(Node* startNode, Node* currentNode, std::vector<Node*> unexploredNodes, std::vector<std::vector <int>> grid, std::pair<int, int> endPosition){

    // Debug
    std::cout << "The current position is " << currentNode->getPosition().first << ", " << currentNode->getPosition().second << ". The min distance is " << currentNode->getMinDistance() << '\n';

    // Check if we have already finished
    if(currentNode->getPosition() == endPosition){
        return currentNode->getMinDistance();
    }

    // KNOWN BUG: Después de escanear la posición (9, 49) pasa a buscar la (-1, -1) y peta
    // Vale es porque ha escaneado 1000 nodos y el vector allNodes está muriendo
    // Necesito comprobar si un nodo ya existe de otra manera --> Seguramente algún BFS o DFS

    if(currentNode->getPosition() == std::make_pair(9, 49)){
        std::cout << "debug";
    }

    // Set the current node as explored
    currentNode->setExplored();

    // Erase element from vector unexploredNodes
    for(int i = 0; i < unexploredNodes.size(); i++){
        if(unexploredNodes[i] == currentNode){
            unexploredNodes.erase(unexploredNodes.begin() + i);
            break;
        }
    }

    // Store in a vector all the surroundings
    std::vector<std::pair<int, int>> surroundings = getSurroundings(currentNode, NROWS, NCOLS);

    // Scan the surroundings and get the ones eligible to jump into
    std::vector<std::pair<int, int>> possibleJumps = getPossibleJumps(currentNode, surroundings, grid);


    // TODO: Check if a Node for this position already exists before creating it
    


    // Create the children nodes
    for(auto jumpPosition : possibleJumps){

        bool nodeExists = checkIfNodeExists(startNode, currentNode, jumpPosition); // Test the function

        bool existingNode = false;

        // Check if a Node already exists for this position
        /*
        for(auto node : allNodes){
            if(node->getPosition() == jumpPosition){    // I must check ALL the nodes before creating a new one 
                existingNode = true;
                break;
            }
        }
        */
        if(!existingNode){

            Node* newNode = new Node(currentNode, jumpPosition, grid[jumpPosition.first][jumpPosition.second], INT_MAX);    // Create the node
            //allNodes.push_back(newNode);
            unexploredNodes.push_back(newNode); 
        }
        // Should I do something if it exists??   
    }

    // Store all the child nodes in a vector
    std::vector<Node*> children = currentNode->getChildren();

    // Calculate the distance for every child
    for(auto &child : children){
        child->setMinDistance(std::min(currentNode->getMinDistance() + 1, child->getMinDistance()));  
    }

    // Find the unexplored Node with the smallest distance
    Node* smallestDistanceNode = new Node(NULL, std::make_pair(-1, -1), -1, INT_MAX);
    smallestDistanceNode->setMinDistance(INT_MAX);

    for(auto unexploredNode : unexploredNodes){
        if(unexploredNode->getMinDistance() < smallestDistanceNode->getMinDistance())
            smallestDistanceNode = unexploredNode;
    }   

    // Repeat the algorithm with the smallestDistanceNode
    dijkstra(startNode, smallestDistanceNode, unexploredNodes, grid, endPosition);

    // Set this Node* to explored and call the dijkstra function again


    // My concern is: will it be possible that for the same position various nodes
    // will be created? If I reach an element, I create a Node*. But if I reach the
    // same position using a different path, will I be able to identify it and use the
    // same Node* ? 

    // Also, when will I stop? How can I assure that I have reached the End Node*? 
    // I will probably need to define a function checkEndNode() or something similar

    return currentNode->getMinDistance();
}