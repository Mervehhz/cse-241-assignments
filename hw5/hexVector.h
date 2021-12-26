#include <iostream>
#include "hexGame.h"

using namespace std;

namespace mervesHex{

    class hexVector : public AbstractHex {

    public :
        explicit hexVector();
        explicit hexVector(int boardSizeVal);
        explicit hexVector(int boardSizeVal, int modeValue);
        void creatBoard();
        void print(ostream & outStream) const;
        void readFromFile(const string& fileName);
        void setCounterPreviousValue();
        bool isBoardLocation(string loc, Cell& position);
        void play();
        void play(Cell position);
        bool isEnd(char letter, int solve[][30]);
        void upperCaseLetterWhoWin(int solve[][30]);
        void reset();
        void numberOfMoves();
        inline void setLastMove(Cell lastP) { lastPlay = lastP; };
        Cell lastMove() const;
        char operator ()(int first, int second) const;
    
    private :
        vector <vector<Cell> > hexCells;
        Cell lastPlay;
    };
}