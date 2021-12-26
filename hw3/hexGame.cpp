#include <iostream>
#include "hexGame.h"

using namespace std;

Hex :: Hex()
    :boardSize(5){}

Hex :: Hex(int boardSizeVal, int modeValue)
    :boardSize(boardSizeVal), mode(modeValue){}

Hex :: Hex(int boardSizeVal)
    : boardSize(boardSizeVal){}

Hex :: Cell :: Cell(int rowValue, int columnValue, char nameValue)
    :row(rowValue), column(columnValue), name(nameValue){}

void Hex :: creatBoard(){
    
    vector<Cell> subCells;
    cellStates cell = EMPTY;

    for(int i=0;i<boardSize;i++){
        for(int k=0;k<boardSize;k++)
                subCells.push_back(Cell(i,k,static_cast<char>(cell)));
    hexCells.push_back(subCells);   /*pushing to hexcells vector of vector the objects to represent the cells.*/
    }
}

void Hex :: boardSizeInput(){

    int boardSizeValue;
    hexCells.clear();
    do{
        cout << "please enter the board size !" << "\n";
        cin >> boardSizeValue;
        
        if(boardSizeValue < 5)
            cerr << "Error.. please enter boardsize greater than 5 !!!\n";

    }while(boardSizeValue < 5);
    setBoardSize(boardSizeValue);
}

void Hex :: getModeInput(int& modeValue){

    do{
        cout << "if computer vs user,then press 0, otherwise press 1.\n";
        cin >> modeValue;

        if((modeValue != 0) && (modeValue != 1))
            cerr << "Error.. please enter 0 for user vs computer, 1 for user vs user !!\n";

    }while((modeValue != 0) && (modeValue != 1));
    setMode(modeValue);
}

void Hex :: playGame(char multiSingle){    /*multisingle variable is 'm' or 's' to represent the multi game or single game*/

    int letter,order=0,flag=1;
    int solve[30][30];
    cellStates cell;
    
    system("clear");
    output();

    for(;getCounter()<(boardSize*boardSize)/2 && flag;setCounter(counter++)){    /*counter variable is to check that game is ended*/
        letter=0;
        inputLocationFromUser(letter,counter,order);

        cell = USER;
        if(isGameEnded(static_cast<char>(cell),solve)){
            upperCaseLetterWhoWin(solve);    
            system("clear");
            output();
            cout << "the letter O won(user1)\n\n";
            if(multiSingle == 'm'){
                setIsFinish(1);    /*putting 1 in the variable isfinish as an indicator that the game is over in the multigame.*/
                flag = 0;
            }
            else 
                exit(1);    /*program is ended when single game*/
        }
        if(multiSingle == 's' || flag){    /*checking if the game is over in the multigame so that the rest of the code does not execute*/
            output();    
            system("clear");

            if(!mode)
                play();
            else{
                letter=1;
                output();
                inputLocationFromUser(letter,counter,order);
                system("clear");
            }

            cell = COMPUTER;
            if(isGameEnded(cell,solve)){
                upperCaseLetterWhoWin(solve);    
                system("clear");
                output();
                cout << "the letter X won(user1)\n\n";
                if(multiSingle == 'm'){
                    setIsFinish(1);
                    flag = 0;
                }
                else 
                    exit(1);
            }
            output();
        }
        /*to execute only once on each step in multigame*/
        if(multiSingle == 'm')
            flag = 0;
   }

    if(counter == (boardSize*boardSize)/2)
        cout << "\nboth of you failed. out of place !\n";
}

void Hex :: configurations(){

    int modeValue;

    boardSizeInput();
    creatBoard();
    getModeInput(modeValue);
}

void Hex :: inputLocationFromUser(int letter, int& counter, int& order){

    string loc,fileName;
    int row,column,flag=0;
    cellStates cell = USER;

    /*if user's input is invalid, then loop continues*/
    while(!flag){
        cout << "\nplease enter first column second space and third row (format is for ex:A 1)\n";
        cin >> ws;
        getline(cin,loc);
        
        /*this funtion finds first occurence space*/
        int temp = loc.find(" ");

        /* compare function compares the first temp(4) characters to a string by starting at the zeroth index, and returns 0 if they are the same.*/
        if(loc.compare(0,temp,"LOAD") == 0 || loc.compare(0,temp,"load") == 0){
            loadFileInformations(loc.substr(temp),counter);     /*substr func gets sub-string after a character space*/
            system("clear");
            output();
            /*if the order is in first user after going to and from load function, it executes*/
            if(order % 2 == 0)
                inputLocationFromUser(letter,counter,order);
            /*if the order is in second user after going to and from load function, it executes*/
            else 
                play();
            flag=1;
        }
        else if(loc.compare(0,temp,"SAVE") == 0 || loc.compare(0,temp,"save") == 0){
            saveFileInformations(loc.substr(temp));
            inputLocationFromUser(letter,counter,order);
            flag=1;
        }
        else if(!isBoardLocation(loc,row,column)){
            play(row,column,cell,letter);
            flag=1;
        }
        else{
            cerr << "Error.. please enter valid input !!\n";
            flag = 0;
        }
    }
    order++;
}

bool Hex :: isBoardLocation(string loc, int& row, int& column){ 

    /*because of i = 2, for ex: A 1 , then 1 is at second index*/
    auto i=2;
    decltype (0) num;
    cellStates cell=EMPTY;

    /*converting*/
    column = static_cast<int>(loc[0]);
    for(int k=i;loc[k] != '\0' && loc[k] != '\n';k++)
        num = num*(k-i)*10 + loc[k]-'0';
    row = num;

    /*if user enters invalid input, then it returns false.*/
    return (column < 'A' || (column > 'A'+getBoardSize())) || (row < 1 || row > getBoardSize()) || (hexCells[row-1][column-'A'].getName() != cell || loc.length()<3);
}

/*in this algorithm, name is putted into the hexcells vector according to the location the user entered*/
void Hex :: play(int row, int column, cellStates cell, int letter){
 
    if(!letter)
        hexCells[row-1][column-'A'].setName(cell);
    else{
        cell = COMPUTER;
        hexCells[row-1][column-'A'].setName(cell);
    }
}

void Hex :: play(){

    int row1,column1;
    cellStates cell=COMPUTER,temp=EMPTY;
    random_device rd;
    mt19937 gen(rd());

    do{
        /*this block generates random numbers for computer moves between boundaries*/
        uniform_int_distribution<> row(1,boardSize);
        uniform_int_distribution<> column('A','A' + boardSize-1);
        row1 = row(gen);
        column1 = column(gen);
    /*if generated location not empty, then it generates location new one*/
    }while(hexCells[row1-1][column1-'A'].getName() != temp);
    hexCells[row1-1][column1-'A'].setName(cell);

    cout << "\n\nmove which computer's choice is ->> " << static_cast<char>(column1) << row1 << endl; 
}

bool Hex :: isGameEnded(char letter, int solve[][30]){

    vector<vector<int> > solveHex;
    vector<int> temp;
    int index;
    cellStates cell = COMPUTER;
    solveHex.clear();

    for(int i=0;i<boardSize;i++){
        temp.clear();
        for(int j=0;j<boardSize;j++){
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

int Hex :: solveHexGame(vector<vector<int> > solveHex, int solve[][30], int index){

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

bool Hex :: whoIsWinnerComputer(vector<vector<int> > solveHex, int solve[][30], int index1, int index2, int visited[][30]){

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

bool Hex :: whoIsWinnerUser(vector<vector<int> > solveHex, int solve[][30], int index1, int index2, int visited[][30]){

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

bool Hex :: outOfBorder(vector<vector<int> > solveHex, int index1, int index2, int visited[][30]){

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

void Hex :: upperCaseLetterWhoWin(int solve[][30]){

    for(int i=0;i<boardSize;i++)
        for(int k=0;k<boardSize;k++)
            if(solve[i][k] == 1)
                hexCells[i][k].setName(hexCells[i][k].getName()-32);
}

void Hex :: loadFileInformations(const string& fileName, int& counter){

    int flag=1,size = getBoardSize();
    char ch;
    string str;
    ifstream inStream;
    inStream.open(fileName);
    vector<Cell> temporary;

    if(inStream.fail())
        cerr << "error opening the file : " << fileName;
    else{
        /*because of additional information in first line,in file*/
        getline(inStream,str);
        int temp = str.find("u");
    
        if(str.substr(temp) == "user versus computer")
            setMode(0);
        else
            setMode(1);
        
        int temp2 = str.find(":");   /*for board size*/
        setBoardSize(str[temp2+1]-'0');    /*setting new board size(in loaded game)*/
        /*reading file to hexcells vector*/
        while(!inStream.eof() && flag){
            for(int i=0;i<boardSize;i++){
                temporary.clear();
                for(int k=0;k<boardSize;k++){
                    inStream >> ch;

                    /*for example if normal game board size is 5 and loaded game is 6, then new space is allocated in hexcells*/
                    if(size < i+1)
                        temporary.push_back(Cell(i,k,ch));
                    else
                        hexCells[i][k].setName(ch);
                }
                if(size < i+1)
                    hexCells.push_back(temporary);

                cout << "\n";
                /*if it doesnt end of file but board is taken exactly, then it executes*/
                if(i == boardSize-1)
                    flag = 0;
            }
        }
    }
    inStream.close();
    setCounterPreviousValue(counter);
}

/*in this function, sets the counter that provides the termination condition for the loaded game.*/
void Hex :: setCounterPreviousValue(int& counter){

    int temp=0;
    cellStates cell=USER;

    for(int i=0;i<boardSize;i++)
        for(int k=0;k<boardSize;k++)
            if(hexCells[i][k].getName() == cell)
                temp++;
    
    counter = temp-1;
}

void Hex :: saveFileInformations(const string& fileName){
    
    int k;
    ofstream outStream;
    outStream.open(fileName);
    
    if(outStream.fail())
        cerr << "error opening the file " <<fileName;
    else{
        /*writing to file*/
        outStream << "board size is:" << boardSize << "\t";
        outStream << "mode is : ";
        if(mode == 0)
            outStream << "user versus computer\n";
        else 
            outStream << "user versus user\n";

        for(int i=0;i<boardSize;i++){
            for(k=0;k<boardSize;k++)
                outStream <<hexCells[i][k].getName() << "\t";
            outStream <<"\n\n";
        }
    }
    outStream.close();
}

void Hex :: output(){

    int k;
    
    cout << "\t\t\tX DOMAIN\n\n\t";
    /*to write the letter of column*/
    for(k='a';k<boardSize+'a';k++)   cout <<static_cast<char>(k)<<"\t";
    cout <<"\n";

    for(int i=0;i<boardSize;i++){
        cout << i+1<<"\t";           /*to print row number*/
        for(k=0;k<boardSize;k++)
            cout << hexCells[i][k].getName() << "\t";

        if((i+1) == boardSize/2)
            cout << "O DOMAIN";
        cout <<"\n\n";
    }
}

int  Hex :: compareHexGame(Hex other){

    cellStates cell = USER,cell2 = EMPTY;
    int first=0,second=0,flag;

    for(int i=0;i<getBoardSize();i++){
        for(int k=0;k<getBoardSize();k++){
            /*for user vs computer*/
            if(!getMode()){
                if(hexCells[i][k].getName() == cell)
                    first++;
            }
            /*for user vs user*/
            else{
                if(hexCells[i][k].getName() != cell2)
                    first++;
            }
        }
    }

    /*for other*/
    for(int i=0;i<other.getBoardSize();i++){
        for(int k=0;k<other.getBoardSize();k++){
            if(!(other.getMode())){
                if(other.hexCells[i][k].getName() == cell)
                    second++;
            }
            else{
                if(other.hexCells[i][k].getName() != cell2)
                    second++;
            }
        }
    }
    if(first > second)
        flag = 1;
    else if(first < second)
        flag = 0;
    else
        flag = 2;
    return flag;
}

int Hex :: getMarkedCellAllGame(){

    markedCellAll += 2;
    return markedCellAll;
}