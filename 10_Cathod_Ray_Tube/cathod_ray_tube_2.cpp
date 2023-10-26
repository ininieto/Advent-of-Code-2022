#include <iostream>
#include <vector>
#include <fstream>
/*
    Advent of Code 2022 - 10.12.2022

    Link to the problem: https://adventofcode.com/2022/day/10

    Author of the solution: Íñigo Nieto Cuadrado

*/

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

void checkCycle(int &cycle, int xReg, std::vector<std::vector<char>> &crt){

    cycle ++;
    
    // Position that the CRT is drawing
    int crtDrawingRow = cycle / 40; // Integer part only
    int crtDrawingPosition = (cycle % 40) - 1; // Must start in 0

    for(int i = 0; i < 3; i++){
        if(xReg -1 +i == crtDrawingPosition)
            crt[crtDrawingRow][crtDrawingPosition] = '#';
    }
}

void handleAddx(int &cycle, int num, int &xReg, std::vector<std::vector<char>> &crt){

    checkCycle(cycle, xReg, crt);
    checkCycle(cycle, xReg, crt);
    xReg += num;
}

void printCRT(std::vector<std::vector<char>> crt){
    
    std::cout << std::endl;

    for (auto row : crt){
        for (auto pixel : row)
            std::cout << pixel;
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main(){

    const int wide = 40, high = 6;
    int cycle = 0;
    int xReg = 1;
    std::vector<std::vector<char>> crt(high, std::vector<char>(wide)); // 2D vector with all the CRT

    // Initialize the CRT
    for(auto &row : crt){
        for(auto &pixel : row)
            pixel = '.';
    }   

    std::string example = readInputText("example.txt");
    std::string inputData = readInputText("input.txt");
    std::string line;

    for(char c : inputData){

        if(c != '\n')   
            line.push_back(c);
        else{
            std::string operation = line.substr(0, line.find(' '));

            if(operation == "noop")
                checkCycle(cycle, xReg, crt);
            else {
                int num = stoi(line.substr(line.find(' ') + 1));
                handleAddx(cycle, num, xReg, crt);
            }
            line.clear();
        }
    }
    printCRT(crt);
    return 0;
}