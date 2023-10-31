#include <iostream>
#include <fstream>

#include "dijkstra.h"

std::string readInputText(std::string inputText){

    // Read input data from txt file
    std::fstream inputfile;
    std::string inputData;

    inputfile.open(inputText, std::ios::in);
    if (inputfile.is_open()){
        std::string tp;
        while (getline(inputfile, tp)){
            inputData += tp;
            inputData += "\n";
        }
    }
    return inputData;
}