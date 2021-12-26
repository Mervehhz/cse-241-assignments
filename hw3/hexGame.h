#ifndef HEADER_H_
#define HEADER_H_

using namespace std;

#include <random>
#include <fstream>
#include <string>
#include <vector>


enum cellStates{EMPTY = '.', USER = 'o', COMPUTER = 'x'};

class Hex{
    public:
        Hex();
        Hex(int boardSizeVal);
        Hex(int boardSizeVal, int modeValue);
        void creatBoard();
        void boardSizeInput();
        void getModeInput(int& modeValue);
        inline int getBoardSize() { return boardSize; };
        inline void setBoardSize(int boardSizeValue){ boardSize = boardSizeValue; };
        inline int getWidth() const { return boardSize; };
        inline int getHeight() const { return boardSize; };
        void setMode(int modeValue) { mode = modeValue; };
        int getMode() { return mode; };
        void inputLocationFromUser(int letter, int& counter, int& order);
        void play();    /*computer moves*/
        void play(int row, int column, cellStates cell, int letter);    /*user moves*/
        void playGame(char multiSingle);
        bool isGameEnded(char letter, int solve[][30]);
        void loadFileInformations(const string& fileName, int& counter);
        void saveFileInformations(const string& fileName);
        void setCounterPreviousValue(int& counter);
        bool isBoardLocation(string loc,  int& row, int& column);
        int solveHexGame(vector<vector<int> > solveHex, int solve[][30], int index);
        bool whoIsWinnerComputer(vector<vector<int> > solveHex, int solve[][30], int index1, int index2, int visited[][30]);
        bool whoIsWinnerUser(vector<vector<int> > solveHex, int solve[][30], int index1, int index2, int visited[][30]);
        bool outOfBorder(vector<vector<int> > solveHex, int index1, int index2, int visited[][30]);
        void upperCaseLetterWhoWin(int solve[][30]);
        void output();
        void configurations();
        inline void setCounter(int counterValue) { counter = counterValue; };
        inline int getCounter() const{ return counter; };
        inline void setIsFinish(int isFinishValue) { isFinish = isFinishValue; };   /*to contol games which finish in multiple games*/
        inline int getIsFinish() const { return isFinish; };
        static int getMarkedCellAllGame();
        int compareHexGame(Hex other);

    private:
        class Cell{
            public:
                Cell();
                Cell(int rowValue, int columnValue, char nameValue);
                inline void setColumn(int columnValue){ column = columnValue; };
                inline void setRow(int rowValue){ row = rowValue; };
                inline int getColumn() const { return column; };
                inline int getRow() const { return row; };
                inline char getName() const { return name; };
                inline void setName(char nameValue){ name = nameValue; };
            private:
                int row;
                int column;
                char name;
        };
        int boardSize,mode,counter,isFinish=0;
        static int markedCellAll;
        vector <vector<Cell> > hexCells;
};

#endif