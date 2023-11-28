/*
    Advent of Code 2022 - 04.12.2022

    Link to the problem: https://adventofcode.com/2022/day/4

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <string>
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

int checkOverlap(int lowerBound1, int upperBound1, int lowerBound2, int upperBound2){

    if(upperBound1 >= lowerBound2 && lowerBound1 <= upperBound2)
        return 1;
    else if(lowerBound1 <= upperBound2 && upperBound1 >= lowerBound2)
        return 1;
    else
        return 0;
}

int main(){

    std::string example = "2-4,6-8\n2-3,4-5\n5-7,7-9\n2-8,3-7\n6-6,4-6\n2-6,4-8\n";
    std::string inputData = readInputText("input.txt");

    int lowerBound1 = 0, upperBound1 = 0; // Input for the first Elf of the pair
    int lowerBound2 = 0, upperBound2 = 0; // Input for the second Elf of the pair

    std::string line;

    int totalOverlap = 0;

    for (char c : inputData){

        if (c != '\n')
            line.push_back(c);
        else{
            // Fill in the variables

            for (int i = 0; i < line.length(); i++){

                if (line[i] == '-' && lowerBound1 == 0)
                    lowerBound1 = stoi(line.substr(0, i));
                else if (line[i] == ',')
                    upperBound1 = stoi(line.substr(line.find('-') + 1, i));
                else if (line[i] == '-' && lowerBound1 > 0){
                    lowerBound2 = stoi(line.substr(line.find(',') + 1, i));
                    upperBound2 = stoi(line.substr(i + 1, line.length()));
                    break;
                }
            }
            // Check if there exists overlap
            totalOverlap += checkOverlap(lowerBound1, upperBound1, lowerBound2, upperBound2);

            // Reset all the variables
            line.clear();
            lowerBound1 = 0;
            upperBound1 = 0;
            lowerBound2 = 0;
            upperBound2 = 0;
        }
    }
    std::cout << "The amount of overlaps is " << totalOverlap << '\n';

    return 0;
}