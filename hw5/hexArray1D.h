#include <iostream>
#include "hexGame.h"

using namespace std;

namespace mervesHex{

    class hexArray1D : public AbstractHex{

    public : 
        explicit hexArray1D();
        explicit hexArray1D(int boardSizeVal);
        explicit hexArray1D(int boardSizeVal, int modeValue);
        explicit hexArray1D(const hexArray1D& dynamicObject);
        hexArray1D& operator=(const hexArray1D& rightSide);
        char operator[](int index) const;
        void creatBoard();
        void print(ostream & outStream) const;
        void readFromFile(const string& fileName);
        void setCounterPreviousValue();
        bool isBoardLocation(string loc, Cell& position);
        void play();
        void play(Cell position);
        bool isEnd(char letter, int solve[][30]);
        void upperCaseLetterWhoWin(int solve[][30]);
        void numberOfMoves();
        void reset();
        inline void setLastMove(Cell lastP) { lastPlay = lastP; };
        Cell lastMove() const;
        char operator ()(int first, int second) const;
        virtual ~hexArray1D();

    private : 
        Cell * hexCells, lastPlay;
    };
}