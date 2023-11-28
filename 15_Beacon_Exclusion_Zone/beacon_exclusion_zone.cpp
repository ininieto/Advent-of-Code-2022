/*
    Advent of Code 2022 - 15.12.2022

    Link to the problem: https://adventofcode.com/2022/day/15

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <vector>
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


// Function to split a std::string by a specific delimitator
std::vector<std::string> split(std::string text, std::string delim){

    std::vector<std::string> splittedText;
    size_t pos = 0;
    std::string token;

    while((pos = text.find(delim)) != std::string::npos){
        token = text.substr(0, pos);
        splittedText.push_back(token);
        text.erase(0, pos + delim.length());
    }

    if(text.length() > 0)
        splittedText.push_back(text);

    return splittedText;
}


int main(){

    std::string example = readInputText("example.txt");
    std::string inputData = readInputText("input.txt");




    return 0;
}