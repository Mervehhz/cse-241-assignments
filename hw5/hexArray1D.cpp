#include <iostream>
#include <stdlib.h>
#include "hexGame.h"
#include "hexArray1D.h"

using namespace std;

namespace mervesHex{

    hexArray1D :: hexArray1D()
        : AbstractHex(){}

    
    hexArray1D :: hexArray1D(int boardSizeVal)
        : AbstractHex(boardSizeVal){}

    
    hexArray1D :: hexArray1D(int boardSizeVal, int modeValue)
        : AbstractHex(boardSizeVal,modeValue){}


    /* copy constructor of big-three */
    hexArray1D :: hexArray1D(const hexArray1D& dynamicObject)
        :AbstractHex()
    {

        setMode(dynamicObject.getMode());
        setOrder(dynamicObject.getOrder());
        setIsFinish(dynamicObject.getIsFinish());

        if(this->getSize() != dynamicObject.getSize()){
            
            setSize(dynamicObject.getSize());
            free(this->hexCells);
            hexCells = (Cell*) malloc(dynamicObject.getSize() * dynamicObject.getSize() * sizeof(Cell));
        }
        for(int i=0;i<dynamicObject.getSize()*dynamicObject.getSize();i++)
            hexCells[i].setName(dynamicObject[i]);
    }

    char hexArray1D :: operator[](int index) const{

        return hexCells[index].getName();
    }

    /* overloading assignment operator of big-three */
    hexArray1D& hexArray1D :: operator=(const hexArray1D& rightSide){
        
        setMode(rightSide.getMode());
        setOrder(rightSide.getOrder());
        setIsFinish(rightSide.getIsFinish());

        if(this->getSize() != rightSide.getSize()){
            
            setSize(rightSide.getSize());
            free(this->hexCells);
            hexCells = (Cell*) malloc(rightSide.getSize() * rightSide.getSize() * sizeof(Cell));
        }
        for(int i=0;i<rightSide.getSize()*rightSide.getSize();i++)
            hexCells[i].setName(rightSide[i]);
        
        return *this;
    }
    
    void hexArray1D :: creatBoard(){

        cellStates cell = EMPTY;
        hexCells = (Cell*) malloc(getSize() * getSize() * sizeof(Cell));    /* allocating memory for board */

        for(int i=0;i<getSize()*getSize();i++)
            hexCells[i].setName(cell);

    }

    void hexArray1D :: print(ostream & outStream) const {

        int k, flag=0;
    
        outStream << "\t\t\tX DOMAIN\n\n\t";
        /*to write the letter of column*/
        for(k='a';k<getSize()+'a';k++)   outStream <<static_cast<char>(k)<<"\t";

        for(int i=0,k=1;i<getSize()*getSize();i++){

            if(i == 0){
                outStream << "\n\n";
                outStream << k <<"\t";           /*to print row number*/
                k++;
            }
            
            outStream << hexCells[i].getName() << "\t";

            if((i+1) % getSize() == 0 && k <= getSize()){

                if(k-1 == getSize()/2 +1 && !flag){
                    flag = 1;
                    outStream << "O DOMAIN";
                }

                outStream << "\n\n";
                outStream << k <<"\t";           /*to print row number*/
                k++;
            }
        }
    }

    void hexArray1D :: readFromFile(const string& fileName){

        int size = getSize(),temp;
        char ch;
        string str;
        ifstream inStream;
        cellStates cell1 = EMPTY, cell2 = USER, cell3 = COMPUTER;

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


            /*reading file to hexcells array*/
            for(int i=0;!inStream.eof();){
            
                inStream >> ch;    /* taking one by one */

                if(ch == cell1 || ch == cell2 || ch == cell3){

                    /*for example if normal game board size is 5 and loaded game is 6, then new space is allocated in hexcells*/
                    if(size*size < i+1){
                        
                        hexCells = (Cell *)realloc(hexCells,(i+1)*sizeof(Cell));
                        hexCells[i].setName(ch);
                    }
                    else
                        hexCells[i].setName(ch);

                    i++;
                }
                cout << "\n";
            }
        }
        inStream.close();
        setCounterPreviousValue();
    }

    /* in this algorithm, the counter of the board read from the file is set. */
    void hexArray1D :: setCounterPreviousValue(){

        int temp=0;
        cellStates cell=USER;

        for(int i=0;i<getSize()*getSize();i++)
            if(hexCells[i].getName() == cell)
                    temp++;
        
        setCounter(temp-1);
    }

    bool hexArray1D :: isBoardLocation(string loc, Cell& position){

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
        return (position.getColumn() < 'A' || (position.getColumn() > 'A'+getSize())) || (position.getRow() < 1 || position.getRow() > getSize()) || (hexCells[(position.getRow()-1)*getSize() + position.getColumn()-'A'].getName() != cell || loc.length()<3);
    }

    void hexArray1D :: play(){

        int row1,column1;
        cellStates cell=COMPUTER,temp=EMPTY;
        random_device rd;
        mt19937 gen(rd());
        Cell position;
        
        do{
            /*this block generates random numbers for computer moves between boundaries*/
            uniform_int_distribution<> row(1,getSize());
            uniform_int_distribution<> column('A','A' + getSize()-1);
            row1 = row(gen);
            column1 = column(gen);
        /*if generated location not empty, then it generates location new one*/
        }while(hexCells[(row1-1)*getSize() + column1-'A'].getName() != temp);
        hexCells[(row1-1)*getSize() + column1-'A'].setName(cell);

        /* in this function, the position placed on the board is also last play */
        position.setRow(row1);
        position.setColumn(column1);
        position.setName(cell);

        setLastMove(position);

        cout << "\n\nmove which computer's choice is ->> " << static_cast<char>(column1) << row1 << endl; 
    }

    void hexArray1D :: play(Cell position){

        setLastMove(position);
        hexCells[(position.getRow()-1)*getSize() + position.getColumn()-'A'].setName(position.getName());
    }

    bool hexArray1D :: isEnd(char letter, int solve[][30]){

        vector<vector<int> > solveHex;
        vector<int> temp;
        int index;
        cellStates cell = COMPUTER;
        solveHex.clear();

        for(int i=1;i<=getSize()*getSize();i++){

            if(hexCells[i-1].getName() == letter)/* for example :   ...x.. then 000100 in solvehex vector */ 
                temp.push_back(1);
            else
                temp.push_back(0);
            
            if(i % getSize() == 0){
                solveHex.push_back(temp);
                temp.clear();
            }
        }

        /*control to know which letter*/
        if(letter == cell)    index = 0;
        else                  index = 1;

        if(solveHexGame(solveHex,solve,index))
            return true;
        else
            return false;
    }

    void hexArray1D :: upperCaseLetterWhoWin(int solve[][30]){

        for(int i=0,j=0;i<getSize();i++)
            for(int k=0;k<getSize();k++,j++)
                if(solve[i][k] == 1)
                    hexCells[j].setName(hexCells[j].getName()-32);
    }

    /* it returns number of moves('o' and 'x') */
    void hexArray1D :: numberOfMoves(){

        cellStates cell = EMPTY;
        int temp = 0;

        for(int i=0;i<getSize()*getSize();i++)
            if(hexCells[i].getName() != cell)
                temp++;
        setNumberOfMoves(temp);
    }

    void hexArray1D :: reset(){

        cellStates cell = EMPTY;

        for(int i=0;i<getSize()*getSize();i++)
            hexCells[i].setName(cell);
        
        setIsFinish(0);    /* if it's a finished game, it is changed*/
        
        system("clear");
        print(cout);

        inputLocationFromUser(0);    /* due to 'o' letter (user 1) always start first */
        
        system("clear");
        print(cout);

        menu();

        /* if game is in pve mode, then play() function is called */
        if(getCounter() % 2 == 0 && !getMode()){
            play();
            system("clear");
            print(cout);
            menu();
        }
        setCounter(0);
    }

    Cell hexArray1D :: lastMove() const{

        return lastPlay;
    }

    char hexArray1D :: operator ()(int first, int second) const{

        return hexCells[(first-1)*getSize() + second].getName();
    }

    hexArray1D :: ~hexArray1D(){

        free(hexCells);
    }
}