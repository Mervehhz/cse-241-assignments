#ifndef HEADER_H_
#define HEADE_H_

#include <random>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

enum cellStates{ EMPTY = '.', USER = 'o', COMPUTER = 'x'};

class Hex{

public:

    class Cell{
    public:
        explicit Cell();
        explicit Cell(int rowValue, int columnValue, char nameValue);
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

    /*default constructor, it sets the board size to 5*/
    explicit Hex();
    explicit Hex(int boardSizeVal);
    explicit Hex(int boardSizeVal, int modeValue);
    inline int getWidth() const { return boardSize; };
    inline int getHeight() const { return boardSize; };
    inline int getBoardSize() const { return boardSize; };
    inline void setBoardSize(int boardSizeVal) { boardSize = boardSizeVal; };
    void getBoardSizeInput();
    inline int getMode() const { return mode; };
    inline void setMode(int modeVal) { mode = modeVal; };
    void getModeInput();
    inline void setCounter(int counterVal) { counter = counterVal; };
    inline int getCounter() const { return counter; };
    void configurations();
    void creatBoard();
    void output();
    void inputLocationFromUser(int letter, int& counter, int control);
    void play(int row, int column, int letter);
    bool isBoardLocation(string loc,  int& row, int& column);
    void loadFileInformations(const string& fileName, int& counter);
    void saveFileInformations(const string& fileName);
    void setCounterPreviousValue(int& counter);
    Cell play();
    inline void setMultiSingle(int mulsin) { multiSingle = mulsin; };
    inline char getMultiSingle() const { return multiSingle; };
    void playGame();
    bool isGameEnded(char letter, int solve[][30]);
    int solveHexGame(int solveHex[][30], int solve[][30], int index);
    bool whoIsWinnerComputer(int solveHex[][30], int solve[][30], int index1, int index2, int visited[][30]);
    bool whoIsWinnerUser(int solveHex[][30], int solve[][30], int index1, int index2, int visited[][30]);
    bool outOfBorder(int solveHex[][30], int index1, int index2, int visited[][30]);
    void upperCaseLetterWhoWin(int solve[][30]);
    inline void setIsFinish(int isFinishValue) { isFinish = isFinishValue; };   /*to contol games which finish in multiple games*/
    inline int getIsFinish() const { return isFinish; };
    inline void setOrder(int ord) { order = ord; };
    inline int getOrder() const { return order; };
    static int getMarkedCellAllGame();
    void undoLastPlay(int& flag2, int& flag3, int check);
    friend bool operator ==(const Hex& leftSide, const Hex& rightSide);
    Hex operator --();    /* prefix */
    Hex operator --(int ignoreMe);    /* postfix */
    friend ostream& operator <<(ostream& outStream, const Hex& game);
    friend istream& operator >>(istream& inStream, Hex& game);
    inline int getScore() const { return score; };
    inline void setScore(int scoreVal) { score = scoreVal; }; 
    int takeScore();
    bool helperFunction(int row, int col, int visited[][30], int temp[][30]);
    bool outOfBorder2(int row, int col, int visited[][30], int temp[][30]);
    //~Hex();
    
private:
    int boardSize,mode,counter,isFinish = 0,oldCounter=0,order,score;
    char multiSingle;
    Cell ** hexCells;
    static int markedCellAll;
    Cell lastPlay;
};

#endif