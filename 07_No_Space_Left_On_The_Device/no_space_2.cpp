/*
    Advent of Code 2022 - 07.12.2022

    Link to the problem: https://adventofcode.com/2022/day/7

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <fstream>
#include <unordered_map>

#include "NonBinaryNode.cpp"    // I know this is not the most elegant way to do this, but I don't feel like creating headers

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

double getRootSize(NonBinaryNode* currentDirectory){

    NonBinaryNode* root;
    NonBinaryNode* parent = currentDirectory->getParent();
    
    while(parent){
        root = parent;
        parent = parent->getParent();
    }

    return root->getSize();
}

NonBinaryNode* existsDirectory(NonBinaryNode *currentDirectory, std::string dirName){

    for (auto child : currentDirectory->getChildren()){
        if (child->getName() == dirName)
            return child;
    }

    return NULL;
}

void handleCD(std::string line, NonBinaryNode* &currentDirectory){

    std::string dirName = line.substr(5, line.length());

    if(dirName == ".."){    // Jump one directory back
        currentDirectory = currentDirectory->getParent();
        return;
    }
    if(dirName == "/"){     // Create root node --> There is only one "$ cd /" at the beginning. If there were more, this would be incorrect
        currentDirectory = new NonBinaryNode(NULL, "/");
        return;
    }
    else{                   // Change to an existing directory INSIDE OUR DIRECTORY
        NonBinaryNode* existingDirectory = existsDirectory(currentDirectory, dirName);
        currentDirectory = existingDirectory ? existingDirectory : currentDirectory;
    }
}

void increaseFathersSize(NonBinaryNode* currentDirectory, double fileSize, std::unordered_map<NonBinaryNode*, double> &allDirectories){

    NonBinaryNode *parent = currentDirectory->getParent();

    if (!parent)
        return;

    parent->increaseSize(fileSize);
    allDirectories[parent] = parent->getSize();
    
    if (parent->getParent())
        increaseFathersSize(parent, fileSize, allDirectories);  // Recursion goes brr
}

void handleLS(std::string lsOutput, NonBinaryNode* &currentDirectory, std::unordered_map<NonBinaryNode*, double> &allDirectories){

    std::string line;

    for(char c : lsOutput){

        if(c != '\n')
            line.push_back(c);
        else{
            if(line.substr(0, 3) == "dir"){   // If directory detected

                std::string dirName = line.substr(line.find(' ') + 1);
                if(!existsDirectory(currentDirectory, dirName))     // If the directory doesn't exist, create it
                    new NonBinaryNode(currentDirectory, dirName);
            }
            else{       // Sum up all the sizes of the directory

                double fileSize = stoi(line.substr(0, line.find(' ')));
                currentDirectory->increaseSize(fileSize);
                allDirectories[currentDirectory] = currentDirectory->getSize();

                increaseFathersSize(currentDirectory, fileSize, allDirectories);    // We must also increase the father(s)'s size
            }
            line.clear();
        }
    }
}


int main(){

    std::string example = "$ cd /\n$ ls\ndir a\n14848514 b.txt\n8504156 c.dat\ndir d\n$ cd a\n$ ls\ndir e\n29116 f\n2557 g\n62596 h.lst\n$ cd e\n$ ls\n584 i\n$ cd ..\n$ cd ..\n$ cd d\n$ ls\n4060174 j\n8033020 d.log\n5626152 d.ext\n7214296 k\n";

    std::string inputData = readInputText("input.txt");

    NonBinaryNode* currentDirectory = NULL;
    std::unordered_map <NonBinaryNode* , double> allDirectories;

    std::string inputInstructions = inputData;
    int len = inputInstructions.length();
    std::string line;

    for (int i = 0; i < len; i++){ // It is preferable to iterate like this to jump when $ ls --> i += lsOutput.length()

        char c = inputInstructions[i];

        if (c != '\n')
            line.push_back(c);
        else{

            if (line.substr(2, 2) == "cd") // If $ cd
                handleCD(line, currentDirectory);

            else if (line.substr(2, 2) == "ls"){ // If $ ls

                std::string restInstructions = inputInstructions.substr(i + 1);
                std::string lsOutput = restInstructions.substr(0, restInstructions.find('$'));

                handleLS(lsOutput, currentDirectory, allDirectories);

                i += lsOutput.length();     // Skip the "$ ls" output in the next iterations 
            }
            line.clear();
        }
    }

    
    double rootSize = getRootSize(currentDirectory);
    double freeSpace = 70000000 - rootSize;
    double neededSpace = 30000000 - freeSpace;

    double result = 0;

    std::cout << "The size of Root is " << std::fixed << rootSize << std::endl;

    std::unordered_map <NonBinaryNode*, double> bigDirectories;

    for(auto dir : allDirectories){
        if(dir.second > neededSpace)
            bigDirectories[dir.first] = dir.second;
    }

    // I need the smallest in this map 

    double smallest = rootSize;

    for(auto dir : bigDirectories){
        if(dir.second < smallest)
            smallest = dir.second;
    }
    
    std::cout << std::fixed << "The solution is " << smallest << std::endl;

    return 0;
}