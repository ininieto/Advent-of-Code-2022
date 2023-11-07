/*
    Advent of Code 2022 - 12.12.2022

    Link to the problem: https://adventofcode.com/2022/day/12

    Author of the solution: Íñigo Nieto Cuadrado

*/

/*
    IMPORTANT UPDATE: I just discovered that it is possible to jump to a position with a lower value. I got a result
    of 341 Jumps, but that is too high. I know the solution is between 240 and 341. Probably I will need to rewrite 
    some functions to take this into account


*/

#include <iostream>
#include <vector>

#include "utils.h"
#include "dijkstra.h"
#include "Node.h"

int main(){

    std::string example = "Sabqponm\nabcryxxl\naccszExk\nacctuvwj\nabdefghi\n";
    // std::string inputData = readInputText("input.txt");
    std::string inputData = readInputText("second_input.txt");
    std::vector<std::vector <int>> grid(NROWS, std::vector<int>(NCOLS));
    std::pair startPosition(-1, -1), endPosition(-1, -1);

    // std::string inputData = example;

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

    // Crete the root node
    Node* startNode = new Node(NULL, startPosition, int('a') - 1, 0);
    Node *currentNode = startNode;

    std::vector<Node*> unexploredNodes; // I need to keep track of the unexplored Nodes

    // Call the dijkstra function on the Start Node. The function is recursive: will call itself throughout the graph
    int minJumps = dijkstra(startNode, currentNode, unexploredNodes, grid, endPosition);
    
    std::cout << minJumps << " jumps";

    return 0;
}