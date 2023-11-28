/*
    Advent of Code 2022 - 02.12.2022
    
    Link to the problem: https://adventofcode.com/2022/day/2

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <string>
#include <fstream>

/*
    The first column is the opponent's choice, so the second is ours.
    In our choice: Rock (X) = 1, Paper (Y) = 2, Scissors (Z) = 3
    Result = {Loss: 0, Draw: 3, Win: 6}

*/

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

char setMyChoice(char firstColumn, char secondColumn){

    if (secondColumn == 'X'){ // I need to lose

        if (firstColumn == 'A') // Opponent has Rock --> I need scissors (Z)
            return 'Z';
        else if (firstColumn == 'B') // Opponent has Paper --> I need Rock (X)
            return 'X';
        else if (firstColumn == 'C') // Opponent has Scissors --> I need Paper (Y)
            return 'Y';
    }
    else if (secondColumn == 'Y'){   // I need to draw
        if (firstColumn == 'A') // Opponent has Rock --> I need Rock (X)
            return 'X';
        else if (firstColumn == 'B') // Opponent has Paper --> I need Paper (Y)
            return 'Y';
        else if (firstColumn == 'C') // Opponent has Scissors --> I need Scissors (Z)
            return 'Z';
    }
    else if (secondColumn == 'Z'){     // I need to win
        if (firstColumn == 'A') // Opponent has Rock --> I need Paper (Y)
            return 'Y';
        else if (firstColumn == 'B') // Opponent has Paper --> I need Scissors (Z)
            return 'Z';
        else if (firstColumn == 'C') // Opponent has Scissors --> I need Rock (X)
            return 'X';
    }

    return -1;      // Error
}

int main(){

    std::string example = "A Y\nB X\nC Z\n";
    std::string inputData = readInputText("input.txt");

    char opponentsChoice = ' ';
    char secondColumn = ' ';
    int totalScore = 0;

    for (char c : inputData){                           // Iterate over the inputData as characters

        // Fill in the choices

        if (opponentsChoice == ' ' || secondColumn == ' '){

            if (opponentsChoice == ' ')
                opponentsChoice = c;
            else if (c == ' ')
                continue;
            else if (secondColumn == ' ')
                secondColumn = c;
        }
        else{

            char myChoice = setMyChoice(opponentsChoice, secondColumn);
            totalScore += assignSecondColumn(myChoice);  // Assign choiceScore
            totalScore += assignGameScore(opponentsChoice, myChoice);

            opponentsChoice = ' ';
            secondColumn = ' ';
        }

    }

    std::cout << "The final score is " << totalScore << '\n';

    return 0;
}