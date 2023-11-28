/*
    Advent of Code 2022 - 03.12.2022
    
    Link to the problem: https://adventofcode.com/2022/day/3

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <vector>

/*
    I need to assign a priority to each letter like:
    a = 1,  b = 2,  ... z = 26
    A = 27, B = 28, ... Z = 52

    The ascii code for lowercase letters is:ç
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
    
    
    std::string rucksacks[3]; // Array that will contain groups of three rucksacks

    std::unordered_map <char, int> elementsFirstRucksack; // Map that will contain all the characters of the first rucksack

    char elementInCommon = ' ';
    std::vector <char> elementsInCommon;
    int totalPriority = 0;

    int rucksackCount = 0; // Variable to count the three rucksacks in a group


    for(char c : inputData){

        if(c != '\n')
            rucksacks[rucksackCount].push_back(c);
        else{

            rucksackCount++;

            if (rucksackCount == 3){
                // Find element in common

                // Fill in a map with the characters of firstRucksack
                for (char e : rucksacks[0]){
                    if (!elementsFirstRucksack[e])
                        elementsFirstRucksack[e] = 1;
                    else
                        elementsFirstRucksack[e]++;
                }

                // Check elements in common with second rucksack

                for (char e : rucksacks[1]){

                    if (elementsFirstRucksack.find(e) != 0 && 
                        find(elementsInCommon.begin(), elementsInCommon.end(), e) == elementsInCommon.end()){

                        elementsInCommon.push_back(e);
                    }
                }

                // Check element in common with third rucksack

                for (char e : rucksacks[2]){

                    if(find(elementsInCommon.begin(), elementsInCommon.end(), e) != elementsInCommon.end()){
                        elementInCommon = e;
                        break;
                    }
                }

                // Calculate priority
                totalPriority += obtainPriority(elementInCommon);

                // Reset variables
                rucksackCount = 0;
                for(int i = 0; i < 3; i++){
                    rucksacks[i].clear();
                }
                elementsFirstRucksack.clear();
                elementInCommon = ' ';
                elementsInCommon.clear();
            }
        }
    }

        std::cout << "The total priority is " << totalPriority << '\n';

        return 0;
}