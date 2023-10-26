#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/*
    Advent of Code 2022 - 02.12.2022
    
    Link to the problem: https://adventofcode.com/2022/day/2

    Author of the solution: Íñigo Nieto Cuadrado

*/

/*
    The first column is the opponent's choice, so the second is ours.
    In our choice: Rock (X) = 1, Paper (Y) = 2, Scissors (Z) = 3
    Result = {Loss: 0, Draw: 3, Win: 6}

*/

int assignSecondColumn(char myChoice)
{
    switch (myChoice){
    case 'X':
        return 1;
    case 'Y':
        return 2;
    case 'Z':
        return 3;
    default:
        return -1;      // Error
    }
}

int assignGameScore(char opponentsChoice, char myChoice)
{

    if (opponentsChoice == 'A' && myChoice == 'Y' || // Win
        opponentsChoice == 'B' && myChoice == 'Z' ||
        opponentsChoice == 'C' && myChoice == 'X')
    {
        return 6;
    }
    else if (opponentsChoice == 'A' && myChoice == 'X' || // Draw
             opponentsChoice == 'B' && myChoice == 'Y' ||
             opponentsChoice == 'C' && myChoice == 'Z')
    {

        return 3;
    }
    else{       // Loss
        return 0;
    }

    return -1;      // Error
}

int main(){

    string example = "A Y\nB X\nC Z\n";

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

    char opponentsChoice = ' ';
    char myChoice = ' ';
    int totalScore = 0;

    for (char c : inputData){                           // Iterate over the inputData as characters

        // Fill in the choices

        if (opponentsChoice == ' ' || myChoice == ' '){

            if (opponentsChoice == ' ')
                opponentsChoice = c;
            else if (c == ' ')
                continue;
            else if (myChoice == ' ')
                myChoice = c;
        }
        else{

            totalScore += assignSecondColumn(myChoice);  // Assign choiceScore
            totalScore += assignGameScore(opponentsChoice, myChoice);

            opponentsChoice = ' ';
            myChoice = ' ';
        }

    }

    cout << "The final score is " << totalScore;

    return 0;
}