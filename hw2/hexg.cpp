#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include "hexg.h"

using namespace std;

/*for enum type that determines cell states*/
enum cellBoard {EMPTY='.',USER='o',COMPUTER='x'};

void boardSizeInput(int& boardSize){

    do{
        cout << "please enter the board size !" << "\n";
        cin >> boardSize;
        
        if(boardSize < 6 || boardSize > 12)
            cerr << "Error.. please enter boardsize between 6 and 12 !!!\n";

    }while(boardSize < 6 || boardSize > 12);
}

void creatingBoard(char board[][12], int boardSize){

    cellBoard cell = EMPTY;

    for(int i=0;i<boardSize;i++)
        for(int k=0;k<boardSize;k++)
            board[i][k] = cell;
}

void whichModePlay(int& mode){

    do{
        cout << "if computer vs user,then press 0, otherwise press 1.\n";
        cin >> mode;

        if((mode != 0) && (mode != 1))
            cerr << "Error.. please enter 0 for user vs computer, 1 for user vs user !!\n";

    }while((mode != 0) && (mode != 1));
}

void printBoardToScreen(char board[][12], int boardSize){

    int k;
    
    cout << "\t\t\tX DOMAIN\n\n\t";
    /*to write the letter of column*/
    for(k='a';k<boardSize+'a';k++)   cout <<static_cast<char>(k)<<"\t";
    cout <<"\n";

    for(int i=0;i<boardSize;i++){
        cout << i+1<<"\t";          /*to print row number*/
        for(k=0;k<boardSize;k++)
            cout <<board[i][k] << "\t";

        if((i+1) == boardSize/2)
            cout << "O DOMAIN";
        cout <<"\n\n";
    }
}

void inputLocationFromUser(char board[][12], int boardSize, int& mode, int& counter, int letter, int& order){

    string loc,word,fileName;
    int row,column,flag=0;
    cellBoard cell = USER;

    /*if user's input is invalid, then loop continues*/
    while(!flag){
        cout << "\nplease enter first column second space and third row (format is for ex:A 1)\n";
        cin >> ws;
        getline(cin,loc);
        
        /*this funtion finds first occurence space*/
        int temp = loc.find(" ");

        /* compare function compares the first temp(4) characters to a string by starting at the zeroth index, and returns 0 if they are the same.*/
        if(loc.compare(0,temp,"LOAD") == 0 || loc.compare(0,temp,"load") == 0){
            loadFileInformations(board,boardSize,loc.substr(temp),counter,mode);     /*substr func gets sub-string after a character space*/
            system("clear");
            printBoardToScreen(board,boardSize);
            if(order % 2 == 0)
                inputLocationFromUser(board,boardSize,mode,counter,letter,order);
            else 
                inputLocationFromComputer(board,boardSize);
            flag=1;
        }
        else if(loc.compare(0,temp,"SAVE") == 0 || loc.compare(0,temp,"save") == 0){
            saveFileInformations(board,boardSize,mode,loc.substr(temp));
            inputLocationFromUser(board,boardSize,mode,counter,letter,order);
            flag=1;
        }
        else if(!isBoardLocation(loc,row,column,boardSize,board)){
            if(!letter)
                board[row-1][column-'A'] = cell;
            else{
                cell = COMPUTER;
                board[row-1][column-'A'] = cell;
            }
            flag=1;
        }
        else{
            cerr << "Error.. please enter valid input !!\n";
            flag = 0;
        }
    }
    order++;
}

bool isBoardLocation(string loc, int& row, int& column, int boardSize, char board[][12]){

    /*because of i = 2, for ex: A 1 , then 1 is at second index*/
    auto i=2;
    decltype (0) num;
    cellBoard cell=EMPTY;

    /*converting*/
    column = static_cast<int>(loc[0]);
    for(int k=i;loc[k] != '\0' && loc[k] != '\n';k++)
        num = num*(k-i)*10 + loc[k]-'0';
    row = num;

    /*if user enters invalid input, then it returns false.*/
    return (column < 'A' || (column > 'A'+boardSize)) || (row < 1 || row > boardSize) || (board[row-1][column-'A'] != cell || loc.length()<3);
}

void inputLocationFromComputer(char board[][12], int boardSize){

    int row1,column1;
    cellBoard cell=COMPUTER,temp=EMPTY;
    random_device rd;
    mt19937 gen(rd());

    do{
        /*this block generates random numbers for computer moves between boundaries*/
        uniform_int_distribution<> row(1,boardSize);
        uniform_int_distribution<> column('A','A' + boardSize-1);
        row1 = row(gen);
        column1 = column(gen);
    /*if generated location not empty, then it generates location new one*/
    }while(board[row1-1][column1-'A'] != temp);
    board[row1-1][column1-'A'] = cell;

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
    if(index1 == boardSize){
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
            /*control that it doesn't go back to places it's gone before*/
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

void loadFileInformations(char board[][12], int boardSize, const string& fileName, int& counter, int& mode){
    
    string str;
    ifstream inStream;
    inStream.open(fileName);

    if(inStream.fail())
        cerr << "error opening the file : " << fileName;
    else{
        /*because of additional information in first line,in file*/
        getline(inStream,str);
        int temp = str.find("u");
    
        if(str.substr(temp) == "user versus computer")
            mode = 0;
        else
            mode = 1;

        /*reading file to board[][] array*/
        while(!inStream.eof()){
            for(int i=0;i<boardSize;i++)
                for(int k=0;k<boardSize;k++)
                    inStream >> board[i][k];
        }
    }
    inStream.close();
    setCounterPreviousValue(board,boardSize,counter);
}

/*this func equals the counter, which keeps track of how many steps left to finish the game, to the counter in the loaded game.*/
void setCounterPreviousValue(char board[][12], int boardSize, int& counter){

    int temp=0;
    cellBoard cell=USER;

    for(int i=0;i<boardSize;i++)
        for(int k=0;k<boardSize;k++)
            if(board[i][k] == cell)
                temp++;
    
    counter = temp-1;
}

void saveFileInformations(char board[][12], int boardSize, int mode, const string& fileName){
    
    int k;
    ofstream outStream;
    outStream.open(fileName);
    
    if(outStream.fail())
        cerr << "error opening the file " <<fileName;
    else{
        /*writing to file*/
        outStream << "board size is : " << boardSize << "\t";
        outStream << "mode is : ";
        if(mode == 0)
            outStream << "user versus computer\n";
        else 
            outStream << "user versus user\n";

        for(int i=0;i<boardSize;i++){
            for(k=0;k<boardSize;k++)
                outStream <<board[i][k] << "\t";
            outStream <<"\n\n";
        }
    }
    outStream.close();
}