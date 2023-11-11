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

std::vector<std::list<int>> readInfo(std::vector<std::string> pair){

    // Iterate all over the strings and save the data in lists

    std::vector<std::list<int>> packetLists;

    for(std::string packet: pair){

        std::list<int> packetList;

        // Remove the first and last bracket, as it is always there
        packet.erase(packet.begin());
        packet.pop_back();

        for(int i = 0; i < packet.length(); i++){

            if(packet[i] == '[' && i != 0){   // Start of list inside packet

            }
            else if(packet[i] == ']' && i != packet.length() - 1){  // End of list inside packet

            }
            else if(packet[i] == ','){  // Separation of number OR LIST

            }
            else{   // Number
                packetList.push_back(packet[i] - '0');

            }
        }

        packetLists.push_back(packetList);

    }

    return packetLists;

}

void compareLists(std::vector<std::list<int>> packetLists){

    // Compare the lists


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