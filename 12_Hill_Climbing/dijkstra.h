#ifndef DIJKSTRA
#define DIJKSTRA

#pragma once
#include <iostream>
#include <vector>

#include "Node.h"

#define INFINITY 999999

std::string readInputText(std::string inputText);
std::vector<std::pair<int, int>> getSurroundings(Node* currentNode, int nrows, int ncols);
std::vector<std::pair<int, int>> getPossibleJumps(Node* currentNode, std::vector<std::pair<int, int>> surroundings, std::vector<std::vector <int>> grid);
std::pair<int, int> jump(std::pair<int, int> position, std::vector<std::pair<int, int>> surroundings, std::vector<std::vector <int>> grid);


#endif