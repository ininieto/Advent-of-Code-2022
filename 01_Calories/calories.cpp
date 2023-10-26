#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

/*
    Advent of Code 2022 - 01.12.2022
    
    Link to the problem: https://adventofcode.com/2022/day/1

    Author of the solution: Íñigo Nieto Cuadrado

*/

int main(){

    // Read input data from txt file
    fstream inputfile;

    string inputData;

    inputfile.open("input.txt", ios::in);
    if(inputfile.is_open()){
        string tp;
        while(getline(inputfile, tp)){
            inputData += tp;
            inputData += "\n";
        }
    }

    // Now I need to find a double \n -> different elf

    string tempNum = "";
    vector <int> elfCount;
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

    std::cout << "The highest is " << highestSumElf << endl;
    
    int topThree = highestSumElf + secondHighest + thirdHighest;

    std::cout << "The top three carry " << topThree << endl;

    return 0;
}