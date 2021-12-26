#ifndef HEADER_H
#define HEADER_H

using namespace std;

#include <random>
#include <fstream>
#include <string>
#include <vector>

enum cellStates {EMPTY = '.', USER = 'o', COMPUTER = 'x'};

namespace mervesHex{

    class Cell{

    public:
        explicit Cell() :row(0), column(0), name('.'){};
        explicit Cell(int rowValue, int columnValue, char nameValue) :row(rowValue), column(columnValue), name(nameValue){};
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


    class AbstractHex{

    public :
        explicit AbstractHex();
        explicit AbstractHex(int boardSizeVal);
        explicit AbstractHex(int boardSizeVal, int modeValue);
        inline int getSize() const { return boardSize; };
        void setSize(int boardSizeVal);
        void getBoardSizeInput();
        inline int getMode() const { return mode; };
        inline void setMode(int modeVal) { mode = modeVal; };
        void getModeInput();
        virtual void creatBoard() = 0;
        virtual void print(ostream & outStream) const = 0;
        inline void setOrder(int ord) { order = ord; };
        inline int getOrder() const { return order; };
        void inputLocationFromUser(int letter);
        virtual void readFromFile(const string& fileName) = 0;
        void writeToFile(const string& fileName);
        virtual bool isBoardLocation(string loc, Cell& position) = 0;
        virtual void play() = 0;
        virtual void play(Cell position) = 0;
        virtual void setCounterPreviousValue() = 0;
        void playGame();
        virtual bool isEnd(char letter, int solve[][30]) = 0;
        int solveHexGame(vector<vector<int> > solveHex, int solve[][30], int index) const;
        bool whoIsWinnerComputer(vector<vector<int> > solveHex, int solve[][30], int index1, int index2, int visited[][30]) const;
        bool whoIsWinnerUser(vector<vector<int> > solveHex, int solve[][30], int index1, int index2, int visited[][30]) const;
        bool outOfBorder(vector<vector<int> > solveHex, int index1, int index2, int visited[][30]) const;
        virtual void upperCaseLetterWhoWin(int solve[][30]) = 0;
        inline void setIsFinish(int isFinishValue) { isFinish = isFinishValue; };   /*to contol games which finish in multiple games*/
        inline int getIsFinish() const { return isFinish; };
        inline void setCounter(int count) { counter = count; };
        inline int getCounter() const { return counter; };
        void menu();
        inline int getNumberOfMoves() const { return numOfMoves; };
        inline void setNumberOfMoves(int number) { numOfMoves = number; };
        virtual void numberOfMoves() = 0;
        virtual void reset() = 0;
        bool operator ==(const AbstractHex& rightSide);
        virtual Cell lastMove() const = 0 ;
        virtual char operator ()(int first, int second) const = 0;

    private :
        int boardSize,mode,order, isFinish=0,numOfMoves=0,counter;
    };
}

#endif