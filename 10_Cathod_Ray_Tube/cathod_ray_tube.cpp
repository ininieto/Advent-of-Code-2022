/*
    Advent of Code 2022 - 10.12.2022

    Link to the problem: https://adventofcode.com/2022/day/10

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <unordered_map>
#include <fstream>

// Read input data from txt file
std::string readInputText(std::string inputText){

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

void checkCycle(int &cycle, int xReg, std::unordered_map<int, int> &signalStrength){

    cycle ++;

    if(signalStrength.find(cycle) != signalStrength.end())
        signalStrength[cycle] = cycle * xReg;
}

void handleAddx(int &cycle, int num, int &xReg, std::unordered_map<int, int> &signalStrength){

    checkCycle(cycle, xReg, signalStrength);
    checkCycle(cycle, xReg, signalStrength);
    xReg += num;
}

int main(){

    int cycle = 0;  // Not sure if should be initialized to 0 or 1
    int xReg = 1;
    std::unordered_map<int, int> signalStrength = {{20, -1}, {60, -1}, {100, -1}, {140, -1}, {180, -1}, {220, -1}};    // 20th cycle, 60th, 100th, ... , 220th
    int totalStrength = 0;

    std::string shortExample = "noop\naddx 3\naddx -5\n";
    std::string longExample = readInputText("long_example.txt");
    std::string inputData = readInputText("input.txt");

    std::string line;

    for(char c : inputData){

        if(c != '\n')   
            line.push_back(c);
        else{

            std::string operation = line.substr(0, line.find(' '));

            if(operation == "noop")
                checkCycle(cycle, xReg, signalStrength);
            else {
                int num = stoi(line.substr(line.find(' ') + 1));
                handleAddx(cycle, num, xReg, signalStrength);
            }
            line.clear();
        }
    }

    for(auto strength : signalStrength){
        totalStrength += strength.second;
    }

    std::cout << "The solution is " << totalStrength << std::endl;


    return 0;
}