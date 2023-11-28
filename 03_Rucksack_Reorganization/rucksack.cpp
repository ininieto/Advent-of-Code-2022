/*
    Advent of Code 2022 - 03.12.2022
    
    Link to the problem: https://adventofcode.com/2022/day/3

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>

/*
    I need to assign a priority to each letter like:
    a = 1,  b = 2,  ... z = 26
    A = 27, B = 28, ... Z = 52

    The ascii code for lowercase letters is:
    a = 97, b = 98, ... z = 122
    A = 65, B = 66, ... Z = 52

    For lowercase letters I need to substract 96, and for Uppercase, 38
*/

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

int obtainPriority(char c){

    // Obtain ascii code
    int ascii = int(c);
    
    if(ascii > 96 && ascii < 123){  // If lowercase
        return ascii - 96;        
    }
    else if(ascii > 65 && ascii < 91){ // If uppercase
        return ascii - 38;
    }

    return -1; // Error
}

int main(){

    std::string example = "vJrwpWtwJgWrhcsFMMfFFhFp\njqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL\nPmmdzqPrVvPwwTWBwg\nwMqvLMZHhHMvwLHjbvcjnnSBnvTQFn\nttgJtRGJQctTZtZT\nCrZsJsPPZsGzwwsLwLmpwMDw\n";
    std::string inputData = readInputText("input.txt");
    
    std::string rucksack = "";
    std::unordered_map <char, int> elementsFirstCompartment; // Map that will contain all the characters of the compartment

    char elementInCommon = ' ';
    int totalPriority = 0;

    for(char c : inputData){

        // Separate the rucksacks
        if(c != '\n')
            rucksack.push_back(c);
        else{
            // Divide rucksack in two compartments
            int len = rucksack.length();
            std::string firstCompartment = rucksack.substr(0, len/2);
            std::string secondCompartment = rucksack.substr(len/2, len);

            // Find element in common

            // Fill in a map with the characters of firstCompartment
            for(char e : firstCompartment){
                if(!elementsFirstCompartment[e])
                    elementsFirstCompartment[e] = 1;
                else
                    elementsFirstCompartment[e] ++;
            }

            for(char e : secondCompartment){

                if(elementsFirstCompartment.find(e) != 0){
                    elementInCommon = e;
                    rucksack = "";
                    firstCompartment = "";
                    secondCompartment = "";
                    elementsFirstCompartment.clear();
                    break;
                }
            }
            // Calculate priority
            totalPriority += obtainPriority(elementInCommon);
        }
    }
        std::cout << "The total priority is " << totalPriority << '\n';
        return 0;
}