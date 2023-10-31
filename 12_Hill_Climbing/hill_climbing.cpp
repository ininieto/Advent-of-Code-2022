/*
    Advent of Code 2022 - 12.12.2022

    Link to the problem: https://adventofcode.com/2022/day/12

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <vector>

#include "utils.h"
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
    // std::string inputData = readInputText("input.txt");
    std::vector<std::vector <int>> grid(NROWS, std::vector<int>(NCOLS));
    std::pair startPosition(-1, -1), endPosition(-1, -1);

    std::string inputData = example;

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

    std::vector<Node*> unexploredNodes; // I need to keep track of the unexplored Nodes

    // Call the dijkstra function on the Start Node. The function is recursive: will call itself throughout the graph
    dijkstra(currentNode, unexploredNodes, grid);
    
    std::cout << jumps << " jumps";

    return 0;
}