#ifndef DIJKSTRA
#define DIJKSTRA

#pragma once
#include <vector>
#include "Node.h"

#define NROWS 5 // Will be 41 in real problem
#define NCOLS 8 // Will be 66 in real problem

std::vector<std::pair<int, int>> getSurroundings(Node* currentNode, int nrows, int ncols);
std::vector<std::pair<int, int>> getPossibleJumps(Node* currentNode, std::vector<std::pair<int, int>> surroundings, std::vector<std::vector <int>> grid);
int dijkstra(Node* currentNode, std::vector<Node*> unexploredNodes, std::vector<Node*> allNodes, std::vector<std::vector <int>> grid, std::pair<int, int> endPosition);

#endif