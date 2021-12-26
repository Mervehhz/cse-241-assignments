#include <iostream>
#include "hexGame.h"
#include "hexVector.h"

using namespace std;

namespace mervesHex{

    hexVector :: hexVector()
        : AbstractHex() {}
    
    hexVector :: hexVector(int boardSizeVal)
        : AbstractHex(boardSizeVal) {}
    
    hexVector :: hexVector(int boardSizeVal, int modeValue)
        : AbstractHex(boardSizeVal,modeValue) {}
    
    void hexVector :: creatBoard(){

        vector<Cell> subCells;
        cellStates cell = EMPTY;

        for(int i=0;i<getSize();i++){
            for(int k=0;k<getSize();k++)
                    subCells.push_back(Cell(i,k,static_cast<char>(cell)));
            hexCells.push_back(subCells);   /*pushing to hexcells vector of vector the objects to represent the cells.*/
        }
    }

    bool hexVector :: isBoardLocation(string loc, Cell& position){

        /*because of i = 2, for ex: A 1 , then 1 is at second index*/
        auto i=2;
        decltype (0) num;
        cellStates cell=EMPTY;

        /*converting*/
        position.setColumn(static_cast<int>(loc[0]));
        for(int k=i;loc[k] != '\0' && loc[k] != '\n';k++)
            num = num*(k-i)*10 + loc[k]-'0';
        position.setRow(num);

        /*if user enters invalid input, then it returns false.*/
        return (position.getColumn() < 'A' || (position.getColumn() > 'A'+getSize())) || (position.getRow() < 1 || position.getRow() > getSize()) || (hexCells[position.getRow()-1][position.getColumn()-'A'].getName() != cell || loc.length()<3);
    }

    void hexVector :: print(ostream & outStream) const{

        int k;
    
        outStream << "\t\t\tX DOMAIN\n\n\t";
        /*to write the letter of column*/
        for(k='a';k<getSize()+'a';k++)   outStream <<static_cast<char>(k)<<"\t";
        outStream <<"\n";

        for(int i=0;i<getSize();i++){
            outStream << i+1<<"\t";           /*to print row number*/
            for(k=0;k<getSize();k++)
                outStream << hexCells[i][k].getName() << "\t";

            if((i+1) == getSize()/2)
                outStream << "O DOMAIN";
            outStream <<"\n\n";
        }
    }

    void hexVector :: readFromFile(const string& fileName){

        int temp,size = getSize();
        char ch;
        string str;
        ifstream inStream;
        cellStates cell1 = EMPTY, cell2 = USER, cell3 = COMPUTER;
        vector<Cell> temporary;

        inStream.open(fileName);

        if(inStream.fail())
            cerr << "error opening the file : " << fileName;
        else{
            /*because of additional information in first line,in file*/
            getline(inStream,str);
            temp = str.find("u");
        
            if(str.substr(temp) == "user versus computer")    setMode(0);  
            else                                              setMode(1);

            
            temp = str.find(":");   /*for board size*/
            setSize(str[temp+1]-'0');    /*setting new board size(in loaded game)*/

            getline(inStream,str);
            temp = str.find(":");    /*taking order*/
            setOrder(str[temp+1]-'0');

            /*reading file to hexcells vector*/
         
            for(int i=0;!inStream.eof();){
                temporary.clear();
                temp = 0;
                for(int k=0;k<getSize();){
                    inStream >> ch;

                    if(ch == cell1 || ch == cell2 || ch == cell3){

                        /*for example if normal game board size is 5 and loaded game is 6, then new space is allocated in hexcells*/
                        if(size < i+1){
                            temp = 1;
                            temporary.push_back(Cell(i,k,ch));
                        }
                        else
                            hexCells[i][k].setName(ch);
                        
                        k++;

                        if( k== getSize())
                            i++;
                    }
                }
                if(temp)
                    hexCells.push_back(temporary);

                cout << "\n";
            }
        }
        inStream.close();
        setCounterPreviousValue();
    }

    /* in this algorithm, the counter of the board read from the file is set. */
    void hexVector :: setCounterPreviousValue(){

        int temp=0;
        cellStates cell=USER;

        for(int i=0;i<getSize();i++)
            for(int k=0;k<getSize();k++)
                if(hexCells[i][k].getName() == cell)
                    temp++;
        
        setCounter(temp-1);
    }

    void hexVector :: play(Cell position){

        setLastMove(position);
        hexCells[position.getRow()-1][position.getColumn()-'A'].setName(position.getName());
    }

    void hexVector :: play(){

        int row1,column1;
        Cell position;
        cellStates cell=COMPUTER,temp=EMPTY;
        random_device rd;
        mt19937 gen(rd());

        do{
            /*this block generates random numbers for computer moves between boundaries*/
            uniform_int_distribution<> row(1,getSize());
            uniform_int_distribution<> column('A','A' + getSize()-1);
            row1 = row(gen);
            column1 = column(gen);
        /*if generated location not empty, then it generates location new one*/
        }while(hexCells[row1-1][column1-'A'].getName() != temp);
        hexCells[row1-1][column1-'A'].setName(cell);

        /* in this function, the position placed on the board is also last play*/
        position.setRow(row1);
        position.setColumn(column1);
        position.setName(cell);

        setLastMove(position);

        cout << "\n\nmove which computer's choice is ->> " << static_cast<char>(column1) << row1 << endl;
    }

    bool hexVector :: isEnd(char letter, int solve[][30]){

        vector<vector<int> > solveHex;
        vector<int> temp;
        int index;
        cellStates cell = COMPUTER;
        solveHex.clear();

        for(int i=0;i<getSize();i++){
            temp.clear();
            for(int j=0;j<getSize();j++){
                if(hexCells[i][j].getName() == letter)/* for example :   ...x.. then 000100 in solvehex vector */ 
                    temp.push_back(1);
                else
                    temp.push_back(0);
            }
            solveHex.push_back(temp);
        }

        /*control to know which letter*/
        if(letter == cell)    index = 0;
        else                  index = 1;

        if(solveHexGame(solveHex,solve,index))
            return true;
        else
            return false;
    }

    void hexVector :: upperCaseLetterWhoWin(int solve[][30]){

        for(int i=0;i<getSize();i++)
            for(int k=0;k<getSize();k++)
                if(solve[i][k] == 1)
                    hexCells[i][k].setName(hexCells[i][k].getName()-32);
    }

    /* in this function, board is done in the first version*/
    void hexVector :: reset(){

        cellStates cell = EMPTY;

        for(int i=0;i<getSize();i++)
            for(int k=0;k<getSize();k++)
                hexCells[i][k].setName(cell);
        
        setIsFinish(0);    /* if it's a finished game, it is changed*/
        
        system("clear");
        print(cout);

        inputLocationFromUser(0);    /* due to 'o' letter (user 1) always start first */
        
        system("clear");
        print(cout);

        menu();

        if(getCounter() % 2 == 0 && !getMode()){
            play();
            system("clear");
            print(cout);
            menu();
        }
        setCounter(0);
    }

    Cell hexVector :: lastMove() const{

        return lastPlay;
    }

    char hexVector :: operator ()(int first, int second) const{

        return hexCells[first-1][second-1].getName();
    }

    /* it returns number of moves('o' and 'x') */
    void hexVector :: numberOfMoves(){

        cellStates cell = EMPTY;
        int temp = 0;

        for(int i=0;i<getSize();i++)
            for(int k=0;k<getSize();k++)
                if(hexCells[i][k].getName() != cell)
                    temp++;
        
        setNumberOfMoves(temp);
    }
}