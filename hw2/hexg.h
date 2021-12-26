#ifndef HEADER_H_
#define HEADER_H_

using namespace std;

void boardSizeInput(int&);
void creatingBoard(char board[][12], int boardSize = 12);
void whichModePlay(int&);
void printBoardToScreen(char board[][12], int boardSize = 12);
void inputLocationFromUser(char board[][12], int, int&, int&, int, int&);
void inputLocationFromComputer(char board[][12], int);
bool checkFirstLetter(char board[][12], int, char,int solve[][12]);
int solveHexGame(int solveHex[][12], int, int, int solve[][12]);
bool whoIsWinnerComputer(int solveHex[][12], int solve[][12], int, int, int, int visited[][12]);
bool whoIsWinnerUser(int solveHex[][12], int solve[][12], int, int, int, int visited[][12]);
bool outOfBorder(int solveHex[][12], int, int, int, int visited[][12]);
void upperCaseLetterWhoWin(int solve[][12], char board[][12], int);
void loadFileInformations(char board[][12], int boardSize, const string& fileName, int& counter, int& mode);
void saveFileInformations(char board[][12], int boardSize, int mode, const string& fileName);
bool isBoardLocation(string loc, int& row, int& column, int boardSize, char board[][12]);
void setCounterPreviousValue(char board[][12], int boardSize, int& counter);

#endif