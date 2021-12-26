#include "hexGame.h"
#include <iostream>

using namespace std;

namespace mervesHex{

    AbstractHex :: AbstractHex()
                : boardSize(5) {}
    
    AbstractHex :: AbstractHex(int boardSizeVal){

        /*error handling*/
        if(boardSizeVal < 5)
            cerr << "ERROR ! board size can not less than 5\n\n";
        else
            boardSize = boardSizeVal;
    }

    AbstractHex :: AbstractHex(int boardSizeVal, int modeValue){

        if(boardSizeVal < 5)
            cerr << "ERROR ! board size can not less than 5\n\n";
        else
            boardSize = boardSizeVal;

        /*error handling*/
        if(modeValue != 1 && modeValue != 0)
            cerr << "ERROR ! invalid input. Try again.\n\n";
        else 
            mode = modeValue;
    }

    void AbstractHex :: setSize(int boardSizeVal){
        
        //reset();
        boardSize = boardSizeVal;
    }

    void AbstractHex :: getBoardSizeInput(){

        int boardSizeValue;

        do{
            cout << "\nplease enter the board size !" << "\n";
            cin >> boardSizeValue;
            
            if(boardSizeValue < 5)
                cerr << "\n\nError.. please enter boardsize greater than 5 !!!\n";

        }while(boardSizeValue < 5);
        boardSize = boardSizeValue;
    }

    void AbstractHex :: getModeInput(){

        int modeValue;

        do{
            cout << "if computer vs user,then press 0, otherwise press 1.\n";
            cin >> modeValue;

            if((modeValue != 0) && (modeValue != 1))
                cerr << "Error.. please enter 0 for user vs computer, 1 for user vs user !!\n";

        }while((modeValue != 0) && (modeValue != 1));
        setMode(modeValue);
    }

    void AbstractHex :: playGame(){

        int letter,flag=1;
        int solve[30][30];
        cellStates cell;
        
        setCounter(0);
        system("clear");
        print(cout);

        for(;getCounter()<(boardSize*boardSize)/2 && flag;setCounter(getCounter())){    /*counter variable is to check that game is ended*/
            letter=0;
            setOrder(1);
            if(lastMove().getName() != 'o')    /* to two times do not print 'o' letter when user resets the board*/
                inputLocationFromUser(letter);
                
            system("clear");
            print(cout);
            menu();

            cell = USER;
            if(isEnd(static_cast<char>(cell),solve)){
                upperCaseLetterWhoWin(solve);    
                system("clear");
                print(cout);
                cout << "the letter O won(user1)\n\n";
                setNumberOfMoves(0);
                setIsFinish(1);    /*putting 1 in the variable isfinish as an indicator that the game is over in the multigame.*/
                flag = 0;
            }
            if((!getIsFinish() || flag) && lastMove().getName() != 'x'){

                if(!mode)
                    play();
                else{
                    letter=1;
                    setOrder(2);
                    print(cout);
                    inputLocationFromUser(letter);
                }
                
                cell = COMPUTER;
                if(isEnd(cell,solve)){
                    upperCaseLetterWhoWin(solve);    
                    system("clear");
                    print(cout);
                    cout << "the letter X won(user1)\n\n";
                    setNumberOfMoves(0);
                    setIsFinish(1);
                    flag = 0;
                }
            
                if(!getIsFinish()){
                    print(cout);
                    menu();
                }
            }
            if(!getIsFinish())
                print(cout);
        }

        cout <<"\n";
        if(getCounter() == (boardSize*boardSize)/2+1)
            cout << "\nboth of you failed. out of place !\n";
    }

    void AbstractHex :: inputLocationFromUser(int letter){

        string loc,fileName;
        int flag=0;
        Cell position;

        /*if user's input is invalid, then loop continues*/
        while(!flag){
            cout << "\nplease enter first column second space and third row (format is for ex:A 1)\n";
            cin >> ws;
            getline(cin,loc);
            
            /*this funtion finds first occurence space*/
            int temp = loc.find(" ");

            /* compare function compares the first temp(4) characters to a string by starting at the zeroth index, and returns 0 if they are the same.*/
            if(loc.compare(0,temp,"LOAD") == 0 || loc.compare(0,temp,"load") == 0){
                readFromFile(loc.substr(temp));     /*substr func gets sub-string after a character space*/
                system("clear");
                print(cout);

                if(getMode()){
                    /*if the order is in first user after going to and from load function, it executes*/
                    if(getOrder() == 1)
                        inputLocationFromUser(0);
                    /*if the order is in second user after going to and from load function, it executes*/
                    else 
                        inputLocationFromUser(1);
                }
                /* if the mod is pve, the order is always in the user('o') */
                else
                    inputLocationFromUser(0);

                flag=1;
            }
            else if(loc.compare(0,temp,"SAVE") == 0 || loc.compare(0,temp,"save") == 0){
                writeToFile(loc.substr(temp));
                inputLocationFromUser(letter);
                flag=1;
            }
            else if(!isBoardLocation(loc,position)){
                position.setName(letter == 0 ? 'o':'x');
                play(position);
                flag=1;
            }
            else{
                cerr << "Error.. please enter valid input !!\n";
                flag = 0;
            }
        }
    }

    int AbstractHex :: solveHexGame(vector<vector<int> > solveHex, int solve[][30], int index) const{

        int flag=0;
        int visited[30][30]={0};

        /*in this block the x's in the first row or the O's in the first column
        are sent to the function one by one, because if a letter does not satisfy
        the termination condition, the other letter is checked.*/
        for(int i=0;i<boardSize;i++){

            /*for computer moves*/
            if(!index){
                if(solveHex[0][i] == 1){
                    if(whoIsWinnerComputer(solveHex,solve,0,i,visited)){
                        flag=1;
                        return flag;
                    }
                }
            }
            /*for user moves*/
            else{
                if(solveHex[i][0] == 1){
                    if(whoIsWinnerUser(solveHex,solve,i,0,visited)){
                        flag=1;
                        return flag;
                    }
                }
            }
        }
        return flag;
    }

    bool AbstractHex :: whoIsWinnerComputer(vector<vector<int> > solveHex, int solve[][30], int index1, int index2, int visited[][30]) const{

        /*if program reach until last row , game over and the letter wins*/
        if(index1 == boardSize){
            solve[index1][index2] = 1;
            return true;
        }
        
        if(outOfBorder(solveHex,index1,index2,visited)){

            solve[index1][index2] = 1;

            /*northwest*/
            if((!visited[index1-1][index2-1]))
                if(whoIsWinnerComputer(solveHex,solve,index1-1,index2-1,visited))
                    return true;
            /*north*/
            if((!visited[index1-1][index2]))
                if(whoIsWinnerComputer(solveHex,solve,index1-1,index2,visited))
                    return true;
            /*northeast*/
            if((!visited[index1-1][index2+1]))
                if(whoIsWinnerComputer(solveHex,solve,index1-1,index2+1,visited))
                    return true;
            /*southwest*/
            if((!visited[index1+1][index2-1]))
                if(whoIsWinnerComputer(solveHex,solve,index1+1,index2-1,visited))
                    return true;
            /*south*/
            if((!visited[index1+1][index2]))
                if(whoIsWinnerComputer(solveHex,solve,index1+1,index2,visited))
                    return true;
            /*southeast*/
            if((!visited[index1+1][index2+1]))
                if(whoIsWinnerComputer(solveHex,solve,index1+1,index2+1,visited))
                    return true;

            /*if none of the above steps work then
            unmark as part of solution path*/
            solve[index1][index2] = 0;
            return false;
        }
        return false;
    }

    bool AbstractHex :: whoIsWinnerUser(vector<vector<int> > solveHex, int solve[][30], int index1, int index2, int visited[][30]) const{

        if(index2 == boardSize){
            solve[index1][index2] = 1;
            return true;
        }
        
        if(outOfBorder(solveHex,index1,index2,visited)){

            solve[index1][index2] = 1;

            /*northwest*/
            if(!(visited[index1-1][index2-1]))
                if(whoIsWinnerUser(solveHex,solve,index1-1,index2-1,visited))
                    return true;
            /*north*/
            if(!(visited[index1][index2-1]))
                if(whoIsWinnerUser(solveHex,solve,index1,index2-1,visited))
                    return true;
            /*northeast*/
            if(!(visited[index1+1][index2-1]))
                if(whoIsWinnerUser(solveHex,solve,index1+1,index2-1,visited))
                    return true;
            /*southwest*/
            if(!(visited[index1-1][index2+1]))
                if(whoIsWinnerUser(solveHex,solve,index1-1,index2+1,visited))
                return true;
            /*south*/
            if(!(visited[index1][index2+1]))
                if(whoIsWinnerUser(solveHex,solve,index1,index2+1,visited))
                    return true;
            /*southeast*/
            if(!(visited[index1+1][index2+1]))
                if(whoIsWinnerUser(solveHex,solve,index1+1,index2+1,visited))
                    return true;

            solve[index1][index2] = 0;
            return false;
        }
        return false;
    }

    bool AbstractHex :: outOfBorder(vector<vector<int> > solveHex, int index1, int index2, int visited[][30]) const{

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

    /* this algorithm returns true if the boards of the two given games are exactly the same */
    bool AbstractHex :: operator ==(const AbstractHex& rightSide){

        if(this->getSize() == rightSide.getSize()){    /* it checks board sizes of games first*/
           for(int i=0;i<this->getSize();i++)
               for(int k=0;k<this->getSize();k++)
                    if(this->operator()(i,k) != rightSide(i,k))
                        return false;
            
            return true;
        }

        else
            return false;
    }

    void AbstractHex :: writeToFile(const string& fileName){

        ofstream outStream;
        outStream.open(fileName);
        
        if(outStream.fail())
            cerr << "error opening the file " <<fileName;
        else{
            /*writing to file*/
            outStream << "board size is:" << getSize() << "\t";
            outStream << "mode is : ";
            if(getMode() == 0)
                outStream << "user versus computer\n";
            else 
                outStream << "user versus user\n";
            
            outStream << "order:" << getOrder() << "\n";

            print(outStream);
        }
        outStream.close();
    }

    void AbstractHex :: menu(){

        int choice,first,second;
        Cell temp;

        do{
            cout << "\n\n,,,,,,,make your choice,,,,,,,\n\n";
            cout << "\n1--> reset the board"
            <<"\n2--> returns the cell content"
            <<"\n3--> take last move"
            <<"\n4--> take number of moves"
            <<"\n0--> none of the above\n";

            cin >> choice;
 
        }while(choice !=0 && choice != 1 && choice != 2 && choice != 3 && choice != 4);

        switch(choice){

            case 1 :    reset();            
            break;
            case 2 :
                do{
                    cout<< "\nchoice first index(1-size)\n";
                    cin >> first;
                    cout << "\nchoice second index(1-size)\n";
                    cin >> second;
                }while(first < 1 || first > getSize() || second < 1 || second > getSize()); 
            
                cout << "\nThe cell content is " << (*this)(first,second);
                
            break;
            case 3 :
                temp = lastMove();
                cout << "The last move is " << temp.getRow() << ". row " << temp.getColumn()-'A'+1 << ". column " << "content is " << temp.getName() << "\n\n";
            break;
            case 4 :
                numberOfMoves();
                cout << "The number of moves is " << getNumberOfMoves() << "\n\n";
            break;
        }
    }
}