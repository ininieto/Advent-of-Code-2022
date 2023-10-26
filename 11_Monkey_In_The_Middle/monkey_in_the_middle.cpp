#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <fstream>

/*
    Advent of Code 2022 - 11.12.2022

    Link to the problem: https://adventofcode.com/2022/day/11

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

void handleStartingItems(std::string items, std::vector<std::pair<int, int>> &monkeyItems){

    std::string item;

    for(char c : items){
        if(c == ' ')
            continue;
        if(c != ',')
            item.push_back(c);
        else{
            monkeyItems.push_back(std::make_pair(stoi(item), -1));
            item.clear();
        }
    }
    monkeyItems.push_back(std::make_pair(stoi(item), -1));  // Last element 
}

void handleOperation(std::string operation, std::vector<std::pair<int, int>> &monkeyItems){

    // The operation will always be new = old (something) --> we just need to check that something

    char op = operation[10];
    std::string operand = operation.substr(12);

    for(auto &item : monkeyItems){

        if(op == '+'){
            if(operand == "old")
                item.first += item.first;
            else
                item.first += stoi(operand);
        }
        else{
            if(operand == "old")
                item.first *= item.first;
            else
                item.first *= stoi(operand);
        }

        item.first /= 3;  // Monkey gets bored
    }
}

void handleTest(std::string test, std::vector<std::pair<int, int>> &monkeyItems, int &inspectedElements){

    // The test will always be to check if it's divisible by something
    int numDivisible = stoi(test.substr(test.find("by ") + 3));

    for(auto &item : monkeyItems){
        inspectedElements ++;

        if(item.first % numDivisible == 0)
            item.second = 1;
        else
            item.second = 0;
    }
}

void handleTrue(std::string action, std::vector<std::vector<std::pair<int, int>>> &monkeyItems, int numMonkey){

    // The action will always be: Throw to Monkey ...
    int targetMonkey = stoi(action.substr(action.find("monkey") + 7)); 
    //std::vector<int> indexesToRemove;
    std::vector<int> elementsToRemove;

    for(int i = 0; i < monkeyItems[numMonkey].size(); i++){  // I prefer to do a classic C-style loop to take count of the indexes
        auto item = monkeyItems[numMonkey][i];

        if(item.second == 0)
            continue;
        else{
            monkeyItems[targetMonkey].push_back(std::make_pair(item.first, -1));
            elementsToRemove.push_back(item.first);
        }
    }

    // Known bug --> When I remove an element from the vector, the rest of the indexes change. Must fix
    // Maybe not the most beautiful code, but works :)

    for(int i = 0; i < elementsToRemove.size(); i++){
        for(int j = 0; j < monkeyItems[numMonkey].size(); j++){

            if(elementsToRemove[i] == monkeyItems[numMonkey][j].first){
                monkeyItems[numMonkey].erase(monkeyItems[numMonkey].begin() + j);
                break;
            }
        }
    }
}

void handleFalse(std::string action, std::vector<std::vector<std::pair<int, int>>> &monkeyItems, int numMonkey){

    // The action will always be: Throw to Monkey ...
    int targetMonkey = stoi(action.substr(action.find("monkey") + 7)); 
    // std::vector<int> indexesToRemove;
    std::vector<int> elementsToRemove;

    for(int i = 0; i < monkeyItems[numMonkey].size(); i++){     // I prefer to do a classic C-style loop to take count of the indexes
        auto item = monkeyItems[numMonkey][i];

        if(item.second == 1)
            continue;
        else{
            monkeyItems[targetMonkey].push_back(std::make_pair(item.first, -1));
            elementsToRemove.push_back(item.first);
        }
    }

    // Known bug --> When I remove an element from the vector, the rest of the indexes change. Must fix
    // Maybe not the most beautiful code, but works :)

    for(int i = 0; i < elementsToRemove.size(); i++){
        for(int j = 0; j < monkeyItems[numMonkey].size(); j++){

            if(elementsToRemove[i] == monkeyItems[numMonkey][j].first){
                monkeyItems[numMonkey].erase(monkeyItems[numMonkey].begin() + j);
                break;
            }
        }
    }
}

int main(){

    //std::string example = readInputText("example.txt");
    std::string inputData = readInputText("input.txt");

    std::vector<std::string> instructions;  
    std::string instruction;
    int instructionCounter = 0;

    // Loop to read all the instructions
    for(char c : inputData){
        instruction.push_back(c);

        if(c == '\n'){
            instructionCounter++;
            if (instructionCounter == 7){   // Here we have in instruction
                instructions.push_back(instruction);
                instruction.clear();
                instructionCounter = 0;
            }
        }
    }

    int numMonkeys = instructions.size();
    std::vector<std::vector<std::pair<int, int>>> monkeyItems (numMonkeys);    // We define it here not to waste so much memory. Now we know haw many instructions we need
    std::unordered_map<int, int> inspectedElements (numMonkeys);

    // Initialize the map to 0
    for(int i = 0; i < numMonkeys; i++){
        inspectedElements[i] = 0;
    }

    // Big loop
    for (int i = 0; i < 20; i++){

        for (std::string instruction : instructions){

            int numMonkey = stoi(instruction.substr(instruction.find(' ') + 1, 1));

            std::string line;
            for (char c : instruction){
                if (c != '\n')
                    line.push_back(c);
                else{

                    std::string information;
                    try{
                        information = line.substr(line.find(':') + 2); // When line is Monkey, there is no string after : --> exception was thrown
                    }
                    catch (...){} // catch any kind of exceptions

                    std::string operation = line.substr(0, line.find(':')); // Read the operation that must be executed

                    if (operation == "  Starting items" && i == 0)
                        handleStartingItems(information, monkeyItems[numMonkey]);

                    else if (operation == "  Operation")
                        handleOperation(information, monkeyItems[numMonkey]);

                    else if (operation == "  Test")
                        handleTest(information, monkeyItems[numMonkey], inspectedElements[numMonkey]);

                    else if (operation == "    If true")
                        handleTrue(information, monkeyItems, numMonkey);

                    else if (operation == "    If false")
                        handleFalse(information, monkeyItems, numMonkey);

                    line.clear();
                }
            }
        }   
    }

    // Now we need the two monkeys with the most interactions

    // Create a vector of pairs from the map's begin and end
    std::vector<std::pair<int, int>> mapItems(inspectedElements.begin(), inspectedElements.end());

    // Sort the vector of pairs in descending order by the values
    std::sort(mapItems.begin(), mapItems.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second > b.second;
    });

    std::cout << "The result is " << mapItems[0].second * mapItems[1].second << "\n";  

    return 0;
}