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
    for(auto s : surroundings){
        if(grid[s.first][s.second] <= currentElement + 1)  // We can only jump to lower value, same value or 1 higher
            possibleJumps.push_back(s);
    }

    return possibleJumps;
}

// Recursive function that searchs all over the graph to check if there already exists a node. By reference, it is possible to "return" the target node
void checkIfNodeExists(Node* currentNode, Node* &targetNode, std::pair<int, int> targetPosition){

    if(currentNode == NULL)
        return;

    // Check if the node has the target position
    if(currentNode->getPosition() == targetPosition){
        targetNode = currentNode;
        return;
    }
    
    std::vector<Node*> children = currentNode->getChildren();

    for (auto child : children)
        checkIfNodeExists(child, targetNode, targetPosition);

    return;
}

// This function will be recursive. It will be called for the root node, and then, call itself for each child

int dijkstra(Node* startNode, Node* currentNode, std::vector<Node*> unexploredNodes, std::vector<std::vector <int>> grid, std::pair<int, int> endPosition, int &numNodes){

    // Debug
    std::cout << "The current position is (" << currentNode->getPosition().first << ", " << currentNode->getPosition().second << "). The min distance is " << currentNode->getMinDistance() << " and the value is " << currentNode->getValue() << '\n';


    // Check if we have already finished
    if(currentNode->getValue() == 123)
        return currentNode->getMinDistance();


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


    // If necessary, create the children nodes
    for(auto jumpPosition : possibleJumps){

        Node* existingNode = NULL;  // If the node already exists, this variable will store it
        checkIfNodeExists(startNode, existingNode, jumpPosition);   // Must search from startNode in order to check the whole graph

        if(!existingNode){ // If hasn't been explored

            Node* newNode = new Node(currentNode, jumpPosition, grid[jumpPosition.first][jumpPosition.second], INT_MAX);    // Create the node
            unexploredNodes.push_back(newNode); 
        }
        else{
            // The node already exists -> Must re-calculathe its minimum distance
            existingNode->setMinDistance(std::min(currentNode->getMinDistance() + 1, existingNode->getMinDistance()));    

            if(currentNode->getMinDistance() + 1 < existingNode->getMinDistance()) // Never happens, but just in case
                existingNode->setParent(currentNode);   
        }
    }

    // Store all the child nodes in a vector
    std::vector<Node*> children = currentNode->getChildren();

    // Calculate the distance for every child
    for(auto &child : children){
        child->setMinDistance(std::min(currentNode->getMinDistance() + 1, child->getMinDistance()));  
    }

    // Find the unexplored Node with the smallest distance
    Node* smallestDistanceNode = unexploredNodes[0]; // Take a random one

    for(auto unexploredNode : unexploredNodes){
        if(unexploredNode->getMinDistance() < smallestDistanceNode->getMinDistance())
            smallestDistanceNode = unexploredNode;
    }   

    // Repeat the algorithm with the smallestDistanceNode
    return dijkstra(startNode, smallestDistanceNode, unexploredNodes, grid, endPosition, numNodes);

}