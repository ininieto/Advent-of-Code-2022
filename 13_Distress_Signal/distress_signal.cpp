/*
    Advent of Code 2022 - 13.12.2022

    Link to the problem: https://adventofcode.com/2022/day/13

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <list>


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

// Iterate all over the strings and save the data in lists
// TODO: Is it really worth to use lists? 
std::vector<std::list<int>> readInfo(std::vector<std::string> pair){

    std::vector<std::list<int>> packetLists;

    for(std::string packet: pair){

        std::list<int> packetList;
        int numBrackets = 0;

        // Skip the first and the last character to omit the [ ] 

        for(int i = 1; i < packet.length() - 1; i++){

            char c = packet[i];

            // TODO: Implement all the complicated logic (maybe add a variable int numOpenLists to take account of the lists inside lists)

            if(c == '['){   // Start of list inside packet
                numBrackets ++;
            }
            else if(c == ']'){  // End of list inside packet

            }
            else if(c == ',')  // Separation of number OR LIST
                continue;
                
            else{   // Number
                packetList.push_back(c - '0');  // Insert the number as an int

            }
        }

        packetLists.push_back(packetList);

    }

    return packetLists;

}

// Compare the lists elment by element
void compareLists(std::vector<std::list<int>> packetLists){

    // I'll start with the simple case: list to list
    int lenList1 = packetLists[0].size();
    int lenList2 = packetLists[1].size();   // I need both to compare which has more elements

    // We know that for Case 1 both lists have the same number of elements. Will need to refine this

    for(auto e: packetLists[0]){
        std::cout << e << ' ';
    }
    std::cout << '\n';

    for(auto e: packetLists[1]){
        std::cout << e << ' ';
    }

    std::cout << '\n';
    std::cout << '\n';

    
    





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

            if(line == ""){  // If space between two lists

                std::vector<std::list<int>> packetLists = readInfo(pair);
                compareLists(packetLists);
 
                pair.clear();
            }
            else{
                pair.push_back(line);
                line.clear();
            }
        }
    }



    return 0;
}