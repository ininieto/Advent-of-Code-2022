/*
    Advent of Code 2022 - 12.12.2022

    Link to the problem: https://adventofcode.com/2022/day/12

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <vector>

#include "dijkstra.h"
#include "Node.h"

/*
    Current approach: Define a graph (kinda tree) where the root node is the Start node.
    The possible jumps are its children nodes. These nodes will have assigned the value (letter).

    Must go through all the graph following the Dijkstra algorithm: taken a node, must check
    all the children. Update the current distance until this point if necessary. When the end is
    reached, the minimum number of steps is already assigned to the end node. 
    
    In case we needed it, it could be possible to traverse the way backwards to check the complete
    path that minimizes the number of steps

*/

int main(){

    std::string example = "Sabqponm\nabcryxxl\naccszExk\nacctuvwj\nabdefghi\n";
    std::string inputData = readInputText("input.txt");
    std::vector<std::vector <int>> grid(NROWS, std::vector<int>(NCOLS));
    std::pair startPosition(-1, -1), endPosition(-1, -1);

    inputData = example;

    // Fill in the grid vector with the ascii values of the characters
    int stringCount = 0;

    for(int i = 0; i < NROWS; i++){
        for(int j = 0; j < NCOLS; j++){

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

    int jumps = 0;

    // Crete the root node
    Node* startNode = new Node(NULL, startPosition, int('a') - 1, 0);
    Node *currentNode = startNode;

    // Change of strategy: will change all the shifted code for a recursive function. 

        // Store in a vector all the surroundings
        std::vector<std::pair<int, int>> surroundings = getSurroundings(currentNode, NROWS, NCOLS);

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

    
    std::cout << jumps << " jumps";

    return 0;
}