/*
    Advent of Code 2022 - 06.12.2022

    Link to the problem: https://adventofcode.com/2022/day/6

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <unordered_map>
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

    std::string example1 = "bvwbjplbgvbhsrlpgdmjqwftvncz";
    std::string example2 = "nppdvjthqldpwncqszvftbrmjlhg";
    std::string example3 = "nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg";
    std::string example4 = "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw";
    std::string inputData = readInputText("input.txt");

    int len = inputData.length(); 
    int maxBufferSize = 4;
    std::unordered_map <char, int> buffer;
    int solution;

    for(int i = 0; i < len; i++){

        if(i < maxBufferSize){  // Fill in the buffer
            if(!buffer[inputData[i]])
                buffer[inputData[i]] = 1;
            else
                buffer[inputData[i]] ++;
        }
        else{

            // Check if all elements are different
            if(buffer.size() == maxBufferSize){
                solution = i;
                break;
            }
            
            // Shift the buffer

            // Include new character
            if(!buffer[inputData[i]])
                buffer[inputData[i]] = 1;
            else{
                buffer[inputData[i]] ++;
            }

            // Eliminate the first element
            if(buffer[inputData[i - maxBufferSize]] > 1)
                buffer[inputData[i - maxBufferSize]] --;
            else
                buffer.erase(inputData[i - maxBufferSize]);            
        }
    }

    std::cout << "The solution is " << solution << '\n';

    return 0;
}