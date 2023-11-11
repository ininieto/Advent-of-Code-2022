/*
    Advent of Code 2022 - 13.12.2022

    Link to the problem: https://adventofcode.com/2022/day/13

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <fstream>
#include <vector>

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

int main(){

    std::string example = readInputText("example.txt");
    std::string inputData = readInputText("input.txt");

    std::string line;
    std::vector<std::string> pair;

    for(char c: example){
        if(c != '\n')
            line.push_back(c);
        else{

            if(line == "")  // If space between two lists
                pair.clear();
            else{
                pair.push_back(line);
                line.clear();
            }
        }
    }



    return 0;
}