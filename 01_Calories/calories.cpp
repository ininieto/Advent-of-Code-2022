/*
    Advent of Code 2022 - 01.12.2022
    
    Link to the problem: https://adventofcode.com/2022/day/1

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

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

    std::string inputData = readInputText("input.txt");

    // Now I need to find a double \n -> different elf

    std::string tempNum = "";
    std::vector <int> elfCount;
    bool lastCharWasLineBreak = false;
    int highestSumElf = 0;
    int secondHighest = 0;
    int thirdHighest = 0;

    for (char c : inputData){                           // Iterate over the inputData as characters
        if (c != '\n'){                                 // If there is no line break
            tempNum.push_back(c);                       // Append all the numbers to form the real number
            lastCharWasLineBreak = false;
        }
        else{
            if (lastCharWasLineBreak){
                int elfSum = reduce(elfCount.begin(), elfCount.end());      // Calculate the sum of the vector

                if(elfSum > highestSumElf){             // check if it's the highest
                    thirdHighest = secondHighest;
                    secondHighest = highestSumElf;
                    highestSumElf = elfSum;
                }
                else if(elfSum > secondHighest){        // check if it's the second
                    thirdHighest = secondHighest;
                    secondHighest = elfSum;
                }
                else if(elfSum > thirdHighest){         // check if it's the third
                    thirdHighest = elfSum;
                }

                elfCount.clear();                       // reset the vector
            }
            else{
                elfCount.push_back(stoi(tempNum));      // stoi converts string to int
                tempNum = "";
                lastCharWasLineBreak = true;
            }
        }
    }

    std::cout << "The highest is " << highestSumElf << '\n';
    
    int topThree = highestSumElf + secondHighest + thirdHighest;

    std::cout << "The top three carry " << topThree << '\n';

    return 0;
}