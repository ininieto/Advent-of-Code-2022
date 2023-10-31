#ifndef DIJKSTRA
#define DIJKSTRA

#pragma once
#include <iostream>
#include <vector>

#include "Node.h"

#define INFINITY 999999
#define NROWS 5 // Will be 41 in real problem
#define NCOLS 8 // Will be 66 in real problem

std::string readInputText(std::string inputText);
std::vector<std::pair<int, int>> getSurroundings(Node* currentNode, int nrows, int ncols);
std::vector<std::pair<int, int>> getPossibleJumps(Node* currentNode, std::vector<std::pair<int, int>> surroundings, std::vector<std::vector <int>> grid);
std::pair<int, int> jump(std::pair<int, int> position, std::vector<std::pair<int, int>> surroundings, std::vector<std::vector <int>> grid);
void dijkstra(Node* currentNode);

#endif