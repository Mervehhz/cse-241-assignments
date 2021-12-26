#include <iostream>
#include "hexg.h"

using namespace std;

int main(){

    int boardSize,mode,counter=0,solve[12][12] = {0},letter,order=0;
    const int MAX_SIZE = 12;
    char board[MAX_SIZE][MAX_SIZE];

    boardSizeInput(boardSize);
    creatingBoard(board,boardSize);
    whichModePlay(mode);
    printBoardToScreen(board,boardSize);
    
    for(;counter<(boardSize*boardSize)/2;counter++){
        letter=0;
        inputLocationFromUser(board,boardSize,mode,counter,letter,order);

        if(checkFirstLetter(board,boardSize,'o',solve)){
            upperCaseLetterWhoWin(solve,board,boardSize);    
            system("clear");
            printBoardToScreen(board,boardSize);
            cout << "the letter O won(user1)\n\n";
            exit(1);
        }
        printBoardToScreen(board,boardSize);    
        system("clear");

        if(!mode)
            inputLocationFromComputer(board,boardSize);
        else{
            letter=1;
            printBoardToScreen(board,boardSize);
            inputLocationFromUser(board,boardSize,mode,counter,letter,order);
            system("clear");
        }

        if(checkFirstLetter(board,boardSize,'x',solve)){
            upperCaseLetterWhoWin(solve,board,boardSize);    
            system("clear");
            printBoardToScreen(board,boardSize);
            cout << "the letter X won(user1)\n\n";
            exit(1);
        }
         printBoardToScreen(board,boardSize);
    }

    if(counter == (boardSize*boardSize)/2)
        cout << "\nboth of you failed. out of place !\n";
    
    return 0;
}