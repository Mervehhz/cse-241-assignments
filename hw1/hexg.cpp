#include <iostream>
#include <random>
#include "hexg.h"

using namespace std;

void boardSizeInput(int& boardSize){

    do{
        cout << "please enter the board size !" << "\n";
        cin >> boardSize;
    }while(boardSize < 6 || boardSize > 12);
}

void creatingBoard(char board[][12], int boardSize){

    for(int i=0;i<boardSize;i++)
        for(int k=0;k<boardSize;k++)
            board[i][k] = '.';
}

void whichModePlay(int& mode){

    do{
        cout << "if computer vs user,then press 0, otherwise press 1.\n";
        cin >> mode;
    }while((mode != 0) && (mode != 1));
}

void printBoardToScreen(char board[][12], int boardSize){

    int k;
    
    cout << "\t\t\tX DOMAIN\n\n\t";
    /*to write the letter of column*/
    for(k='a';k<boardSize+'a';k++)   cout <<static_cast<char>(k)<<"\t";
    cout <<"\n";

    for(int i=0;i<boardSize;i++){
        cout << i+1<<"\t";
        for(k=0;k<boardSize;k++)
            cout <<board[i][k] << "\t";

        if((i+1) == boardSize/2)
            cout << "O DOMAIN";
        cout <<"\n\n";
    }
}

void inputLocationFromUser(char board[][12], int boardSize){

    int cl,row;
    char column;

    do{
        cout << "\nplease enter first column second space and third row (format is for ex:A 1)\n";
        cin >> column >> row;
        cl = static_cast<int>(column);
    /*if user's input is invalid, then loop continues*/
    }while((cl < 'A' || (cl > 'A'+boardSize)) || (row < 1 || row > boardSize) || (board[row-1][cl-'A'] != '.'));
    board[row-1][cl-'A'] = 'o';
}

void inputLocationFromComputer(char board[][12], int boardSize){

    int row1,column1;
    random_device rd;
    mt19937 gen(rd());

    do{
        /*this block generates random numbers for computer moves between boundaries*/
        uniform_int_distribution<> row(1,boardSize);
        uniform_int_distribution<> column('A','A' + boardSize-1);
        row1 = row(gen);
        column1 = column(gen);
    /*if generated location not empty, then it generates location new one*/
    }while(board[row1-1][column1-'A'] != '.');
    board[row1-1][column1-'A'] = 'x';

    cout << "\n\nmove which computer's choice is ->> " << static_cast<char>(column1) << row1 << endl; 
}

/*this algorithm makes the indices with the incoming letter 1 and the other indices 0 */
bool checkFirstLetter(char board[][12], int boardSize, char letter, int solve[][12]){

    int solveHex[12][12] = {0},index;

    for(int i=0;i<12;i++)
        for(int j=0;j<12;j++){
            if(board[i][j] == letter)
                solveHex[i][j] = 1;
            else 
                solveHex[i][j] = 0;
        }
    /*control to know which letter*/
    if(letter == 'x')    index = 0;
    else                 index = 1;

    if(solveHexGame(solveHex,boardSize,index,solve))
        return true;
    else
        return false;
}

int solveHexGame(int solveHex[][12], int boardSize, int index, int solve[][12]){

    int flag=0,visited[12][12] = {0};

    /*in this block the x's in the first row or the O's in the first column
    are sent to the function one by one, because if a letter does not satisfy
    the termination condition, the other letter is checked.*/
    for(int i=0;i<boardSize;i++){

        /*for computer moves*/
        if(!index){
            if(solveHex[0][i] == 1){
                if(whoIsWinnerComputer(solveHex,solve,boardSize,0,i,visited)){
                    flag=1;
                    return flag;
                }
            }
        }
        /*for user moves*/
        else{
            if(solveHex[i][0] == 1){
                if(whoIsWinnerUser(solveHex,solve,boardSize,i,0,visited)){
                    flag=1;
                    return flag;
                }
           }
        }
    }
    return flag;
}

bool whoIsWinnerComputer(int solveHex[][12], int solve[][12], int boardSize, int index1, int index2, int visited[][12]){

    /*if program reach until last row , game over and the letter wins*/
    if(index1 == boardSize-1){
        solve[index1][index2] = 1;
        return true;
    }
    
    if(outOfBorder(solveHex,index1,index2,boardSize,visited)){

        solve[index1][index2] = 1;

        /*northwest*/
        if((!visited[index1-1][index2-1]))
            if(whoIsWinnerComputer(solveHex,solve,boardSize,index1-1,index2-1,visited))
                return true;
        /*north*/
        if((!visited[index1-1][index2]))
            if(whoIsWinnerComputer(solveHex,solve,boardSize,index1-1,index2,visited))
                return true;
        /*northeast*/
        if((!visited[index1-1][index2+1]))
            if(whoIsWinnerComputer(solveHex,solve,boardSize,index1-1,index2+1,visited))
                return true;
        /*southwest*/
        if((!visited[index1+1][index2-1]))
            if(whoIsWinnerComputer(solveHex,solve,boardSize,index1+1,index2-1,visited))
                return true;
        /*south*/
        if((!visited[index1+1][index2]))
            if(whoIsWinnerComputer(solveHex,solve,boardSize,index1+1,index2,visited))
                return true;
        /*southeast*/
        if((!visited[index1+1][index2+1]))
            if(whoIsWinnerComputer(solveHex,solve,boardSize,index1+1,index2+1,visited))
                return true;

        /*if none of the above steps work then
        unmark as part of solution path*/
        solve[index1][index2] = 0;
        return false;
    }
    return false;
}

bool whoIsWinnerUser(int solveHex[][12], int solve[][12], int boardSize, int index1, int index2, int visited[][12]){

    if(index2 == boardSize){
        solve[index1][index2] = 1;
        return true;
    }
    
    if(outOfBorder(solveHex,index1,index2,boardSize,visited)){

        solve[index1][index2] = 1;

        /*northwest*/
        if(!(visited[index1-1][index2-1]))
            if(whoIsWinnerUser(solveHex,solve,boardSize,index1-1,index2-1,visited))
                return true;
        /*north*/
        if(!(visited[index1][index2-1]))
            if(whoIsWinnerUser(solveHex,solve,boardSize,index1,index2-1,visited))
                return true;
        /*northeast*/
        if(!(visited[index1+1][index2-1]))
            if(whoIsWinnerUser(solveHex,solve,boardSize,index1+1,index2-1,visited))
                return true;
        /*southwest*/
        if(!(visited[index1-1][index2+1]))
            if(whoIsWinnerUser(solveHex,solve,boardSize,index1-1,index2+1,visited))
            return true;
        /*south*/
        if(!(visited[index1][index2+1]))
            if(whoIsWinnerUser(solveHex,solve,boardSize,index1,index2+1,visited))
                return true;
        /*southeast*/
        if(!(visited[index1+1][index2+1]))
            if(whoIsWinnerUser(solveHex,solve,boardSize,index1+1,index2+1,visited))
                return true;

        solve[index1][index2] = 0;
        return false;
    }
    return false;
}

bool outOfBorder(int solveHex[][12], int index1, int index2, int boardSize, int visited[][12]){

    int flag = 0;

    if(index1 >= 0 && index1 < boardSize && index2 >= 0 && index2 < boardSize)
        flag = 1;
    
    if(flag)
        if(solveHex[index1][index2] == 1){
            visited[index1][index2] = 1;
            return true;
        }

    return false;
}

void upperCaseLetterWhoWin(int solve[][12], char board[][12], int boardSize){

    for(int i=0;i<boardSize;i++)
        for(int k=0;k<boardSize;k++)
            if(solve[i][k] == 1)
                board[i][k] -= 32;
}