#ifndef DIJKSTRA
#define DIJKSTRA

#pragma once
#include <vector>
#include "Node.h"

#define NROWS 41  // 5 for example, 41 for real problem, 41 for second input
#define NCOLS 167 // 8 for example, 66 for real problem, 167 for second input

std::vector<std::pair<int, int>> getSurroundings(Node* currentNode, int nrows, int ncols);
std::vector<std::pair<int, int>> getPossibleJumps(Node* currentNode, std::vector<std::pair<int, int>> surroundings, std::vector<std::vector <int>> grid);
void checkIfNodeExists(Node* currentNode, Node* &targetNode, std::pair<int, int> targetPosition);
int dijkstra(Node* startNode, Node* currentNode, std::vector<Node*> unexploredNodes, std::vector<std::vector <int>> grid, std::pair<int, int> endPosition);


#endif