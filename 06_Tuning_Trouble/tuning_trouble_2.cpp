#include <iostream>
#include <unordered_map>
#include <fstream>

using namespace std;

/*
    Advent of Code 2022 - 05.12.2022

    Link to the problem: https://adventofcode.com/2022/day/5

    Author of the solution: Íñigo Nieto Cuadrado

*/

int main(){

    string example1 = "bvwbjplbgvbhsrlpgdmjqwftvncz";
    string example2 = "nppdvjthqldpwncqszvftbrmjlhg";
    string example3 = "nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg";
    string example4 = "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw";

    
    // Read input data from txt file
    fstream inputfile;
    string inputData;

    inputfile.open("input.txt", ios::in);
    if (inputfile.is_open()){
        string tp;
        while (getline(inputfile, tp)){
            inputData += tp;
            inputData += "\n";
        }
    }

    //inputData = example4;

    int len = inputData.length(); 
    int maxBufferSize = 14;
    unordered_map <char, int> buffer;
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

    cout << "The solution is " << solution << endl;

    return 0;
}