/*
    Advent of Code 2022 - 05.12.2022

    Link to the problem: https://adventofcode.com/2022/day/5

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <stack>
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

int main(){

    // Define the example set
    /*
    const int numStacks = 3;
    string inputData[numStacks] = {"ZN", "MCD", "P"};
    stack <char> stacks[numStacks];
    string instructions = "move 1 from 2 to 1\nmove 3 from 1 to 3\nmove 2 from 2 to 1\nmove 1 from 1 to 2\n";
    */

    // Define the input dataset
    
    const int numStacks = 9;
    std::string inputData[numStacks] = {"WMLF", "BZVMF", "HVRSLQ", "FSVQPMTJ", "LSW", "FVPMRJW", "JQCPNRF", "VHPSZWRB", "BMJCGHZW"};
    std::stack <char> stacks[numStacks];
    std::string instructions = readInputText("input.txt");

    // Fill in the stacks
    for(int i = 0; i < numStacks; i++){
        for (char c : inputData[i]){
            stacks[i].push(c);
        }
    }

    std::string instructionLine;
    std::string word;

    int quantity = -1, initialStack = -1, targetStack = -1;

    for(char c : instructions){ // Read all the instructions

        if(c != '\n')
            instructionLine.push_back(c); // Collect all the characters of a line
        else{
            for(char e : instructionLine){  // Separate the words of an instruction
                if(e != ' ')
                    word.push_back(e);
                else{                       // Fill in the variables
                    if(word == "move" || word == "from" || word == "to")
                        word.clear();
                    else if(quantity == -1){
                        quantity = stoi(word);
                        word.clear();
                    }
                    else if(initialStack == -1){
                        initialStack = stoi(word) - 1;  // We must substract 1 as our indexes start in 0
                        word.clear();
                    }
                }
            }

            if(targetStack == -1){ // The last variable won't be read otherwise
                targetStack = stoi(word) - 1;
                word.clear();
            }

            // Perform the instructions
            for(int j = 0; j < quantity; j++){
                stacks[targetStack].push(stacks[initialStack].top());
                stacks[initialStack].pop();
            }
            
            // Reset all the variables
            instructionLine.clear();
            word.clear();
            quantity = -1;
            initialStack = -1;
            targetStack = -1;
        }
    }
    std::string solution;

    for(int i = 0; i < numStacks; i++){
        solution.push_back(stacks[i].top());
    }

    std::cout << "The solution is " << solution << '\n';

    return 0;
}