#include <iostream>
#include "hexGame.h"

using namespace std;

Hex :: Hex()
    :boardSize(5){}

Hex :: Hex(int boardSizeVal){

    /*error handling*/
    if(boardSizeVal < 5)
        cerr << "ERROR ! board size can not less than 5\n\n";
    else
        boardSize = boardSizeVal;
}

Hex :: Hex(int boardSizeVal, int modeVal){
    
    if(boardSizeVal < 5)
        cerr << "ERROR ! board size can not less than 5\n\n";
    else
        boardSize = boardSizeVal;

    /*error handling*/
    if(modeVal != 1 && modeVal != 0)
        cerr << "ERROR ! invalid input. Try again.\n\n";
    else 
        mode = modeVal;
}

void Hex :: getBoardSizeInput(){

    int boardSizeValue;

    do{
        cout << "please enter the board size !" << "\n";
        cin >> boardSizeValue;
        
        if(boardSizeValue < 5)
            cerr << "Error.. please enter boardsize greater than 5 !!!\n";

    }while(boardSizeValue < 5);
    setBoardSize(boardSizeValue);
}

/*pve = 0, pvp = 1*/
void Hex :: getModeInput(){

    int modeValue;

    do{
        cout << "if computer vs user,then press 0, otherwise press 1.\n";
        cin >> modeValue;

        if((modeValue != 0) && (modeValue != 1))
            cerr << "Error.. please enter 0 for user vs computer, 1 for user vs user !!\n";

    }while((modeValue != 0) && (modeValue != 1));
    setMode(modeValue);
}

Hex :: Cell :: Cell()
            : row(0),column(0),name('.') {}

Hex :: Cell :: Cell(int rowValue, int columnValue, char nameValue)
            :row(rowValue),column(columnValue),name(nameValue) {}

/*creating and filling hexCells with '.'*/
void Hex :: creatBoard(){
    
    cellStates cell = EMPTY;
    Hex :: Cell temp;

    hexCells = new Hex :: Cell*[getBoardSize()];

    for(int k=0;k<getBoardSize();k++){
        hexCells[k] = new Hex :: Cell[getBoardSize()];
        for(int j=0;j<getBoardSize();j++){
            temp = Cell(k,j,static_cast<char> (cell));
            hexCells[k][j] = temp;
        }
    }
}

void Hex :: output(){

    cout << *this;    /*printing board with overloading (<<) insertion*/
}

void Hex :: configurations(){

    getBoardSizeInput();
    creatBoard();
    getModeInput();
    setScore(0);
    setOrder(1);
}

void Hex :: playGame(){

    int letter,flag=1, solve[30][30] = {0}, flag2=0, flag3=0;
    cellStates cell;
    Cell computerLocation;

    do{
        /*setting letter, for ex : order is 1 , then letter setting 0 that is USER ('o')*/
        if(getOrder() == 1)
            letter = 0;
        
        else 
            letter = 1;
    
        if(getMode())    /*for good display on the screen*/
            system("clear");

        output();
        inputLocationFromUser(letter,counter,0);

        system("clear");
        output();
        
        /*if mode is pvp*/
        if(getMode()){

            flag2 = 0;    /*if user wants the undo last play with pre decrement, then flag2 is setted 1 in undoLastPlay() function*/
            undoLastPlay(flag2,flag3,1);

            system("clear");
            output();
        }

        /*if user wants undo last play with predecrement in pvp mode.*/
        /*this block is implemented because of if user wants undo last play then new entry must take.*/
        if(flag2 && getMode()){

            inputLocationFromUser(letter,counter,0);
            flag2 = 0;
            
            system("clear");
            output();
            undoLastPlay(flag2,flag3,0);
        }

        if(oldCounter){
            setCounter((boardSize*boardSize)/2);
            oldCounter = 0;
        }

        cell = USER;
        if(isGameEnded(static_cast<char>(cell), solve)){
            upperCaseLetterWhoWin(solve);    
            system("clear");
            output();

            cout << "the user score is : " << getScore() + 1<< endl;
            cout << "the letter O won(user1)\n\n";
            if(getMultiSingle() == 'm'){
                setIsFinish(1);    /*putting 1 in the variable isfinish as an indicator that the game is over in the multigame.*/
                flag = 0;
            }
            else 
                exit(1);    /*program is ended when single game*/
        }

        if(getMultiSingle() == 's' || flag){    /*checking if the game is over in the multigame so that the rest of the code does not execute*/
            system("clear");
            output();    

            if(!getMode()){

                flag2 = flag3 = 0;
                undoLastPlay(flag2,flag3,0);

                /*if user wants undo last play(pre or post doesnt matter), then it does not execute computer move because it waits that user enters move.*/
                if(!flag2 && !flag3)
                    computerLocation = play();

                system("clear");
                output();
                cout << "\n\nmove which computer's choice is ->> " << static_cast<char>(computerLocation.getColumn() + 'A') << computerLocation.getRow()+1 << endl;
            }
            else{

                if(getOrder() == 1)
                    letter = 0;
                
                else 
                    letter = 1;
                
                inputLocationFromUser(letter,counter,0);

                system("clear");
                output();
            }

            /*score taking only works in pve mode*/
            if(!getMode()){
                setScore(takeScore());
                cout << "the user score is : " <<getScore()<< endl;
            }

            cell = COMPUTER;
            if(isGameEnded(cell,solve)){
                upperCaseLetterWhoWin(solve);    
                system("clear");
                output();
                cout << "the letter X won(user1)\n\n";
                if(getMultiSingle() == 'm'){
                    setIsFinish(1);
                    flag = 0;
                }
                else 
                    exit(1);
            }
        }
        /*to execute only once on each step in multigame*/
        if(getMultiSingle() == 'm')
            flag = 0;
        
        /*if game is on pvp, then for the second user, undo last play is asked again*/
        if(getMode() && !getIsFinish())
            undoLastPlay(flag2,flag3,1);

        if(oldCounter){
            setCounter((boardSize*boardSize)/2);    /*to implement only one time when user want to undo play with post decrement*/
            oldCounter = 0;
        }
        
        setCounter(getCounter()+1);
            
   }while(getCounter()<(boardSize*boardSize)/2 && flag);   /*counter variable is to check that game is ended*/

    if(counter == (boardSize*boardSize)/2)
        cout << "\nboth of you failed. out of place !\n";

}

void Hex :: undoLastPlay(int& flag2, int& flag3, int check){

    char undo;

    if(!getIsFinish()){
        
        cout << "\ndo you want undo your move ? (pre-decrement), if you want, then press 'y' or 'Y'\n";
        cin >> undo;
        
        if(undo == 'y' || undo == 'Y'){
            flag3 = 1;    /*indicator that user say yes pre decrement*/

            /*if second user wants to undo last play in pvp mode*/
            if(getOrder() == 1 && getMode() && check)
                setOrder(2);

            else if(getMode() && getOrder() == 2)
                setOrder(1);

            else if(!check)
                setOrder(1);

            --(*this);
        }

        undo = '\0';

        cout << "\ndo you want undo your move ? (post-decrement), if you want, then press 'y' or 'Y'\n";
        cin >> undo;
        
        if(undo == 'y' || undo == 'Y'){
            flag2 = 1;     /*indicator that user say yes post decrement*/
            this->operator--(undo);
        }
    }
}

int Hex :: takeScore(){

    cellStates cell = USER;
    int temp[30][30],max=getScore(), visited[30][30] = {0};

    for(int i=0;i<getBoardSize();i++){
        for(int k=0;k<getBoardSize();k++){
            if(hexCells[i][k].getName() == static_cast<char> (cell))
                temp[i][k] = 1;
            
            else 
                temp[i][k] = 0;
            
        }
    }

    /* each USER cell is sent one by one to helperfunction()*/
    for(int i=0;i<getBoardSize();i++){
        for(int k=0;k<getBoardSize();k++)
            if(temp[i][k] == 1){
                setScore(0);
                helperFunction(i,k,visited,temp);
                if(getScore() > max){
                    setScore(getScore());
                    max = getScore();
                }
            }
    }
    return max;
}

bool Hex :: helperFunction(int row, int col, int visited[][30], int temp[][30]){
    
    if(outOfBorder2(row,col,visited,temp)){

        setScore(getScore()+1);
        /*northwest*/
        if(!(visited[row-1][col-1]))
            if(helperFunction(row-1,col-1,visited,temp))
                return true;
        
        /*north*/
        if(!(visited[row][col-1]))
            if(helperFunction(row,col-1,visited,temp))
                return true;
            
        /*northeast*/
        if(!(visited[row+1][col-1]))
            if(helperFunction(row+1,col-1,visited,temp))
                return true;
            
        /*southwest*/
        if(!(visited[row-1][col+1]))
            if(helperFunction(row-1,col+1,visited,temp))
                return true;

        /*south*/
        if(!(visited[row][col+1]))
            if(helperFunction(row,col+1,visited,temp))
                return true;
     
        /*southeast*/
        if(!(visited[row+1][col+1]))
            if(helperFunction(row+1,col+1,visited,temp))
                return true;
    }
    return true;
}

bool Hex :: outOfBorder2(int row, int col, int visited[][30], int temp[][30]){

    int flag = 0;

    if(row >= 0 && row < getBoardSize() && col >= 0 && col < getBoardSize())
        flag = 1;
    
    if(flag)
        if(temp[row][col] == 1){
            /*control that it doesn't go back to places it's gone before*/
            visited[row][col] = 1;
            return true;
        }
    return false;

}

void Hex :: inputLocationFromUser(int letter, int& counter, int control){

    string loc,fileName;
    int row,column,flag=0,flag2 = 0,flag3 = 0, flag4 = 0;
    Hex :: Cell computerLocation; /*because of, if the any game is loaded and if the game is pve and if order of computer, then computer plays*/

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

            if(!getMode()){

                inputLocationFromUser(letter,counter,control);
                system("clear");
                output();

                undoLastPlay(flag3,flag4,0);
                
                system("clear");
                output();

                if(!flag3 && !flag4)
                    computerLocation = play();

                system("clear");
                output();
                cout << "\n\nmove which computer's choice is ->> " << static_cast<char>(computerLocation.getColumn()) << computerLocation.getRow() << endl; 
            }
            else{
                 /*if the order is in first user after going to and from load function, it executes*/
                if(getOrder() == 1)
                    inputLocationFromUser(0,counter,control);
                
                /*if the order is in second user after going to and from load function, it executes*/
                else
                    inputLocationFromUser(1,counter,control);
                control = 1;
            }
            flag=1;
        }
        else if(loc.compare(0,temp,"SAVE") == 0 || loc.compare(0,temp,"save") == 0){

            saveFileInformations(loc.substr(temp));
            inputLocationFromUser(letter,counter,control);
            flag=1;
        }
        else if(!isBoardLocation(loc,row,column)){
            play(row,column,letter);
            flag=1;
        }
        else{
            cerr << "Error.. please enter valid input !!\n";
            flag = 0;
        }
    }
    /*exchange of order each time*/
    if(!control){
        if(getOrder() == 1){
            flag2 = 1;
            setOrder(2);
        }

        if(getOrder() == 2 && !flag2)
            setOrder(1);
    }
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

void Hex :: play(int row, int column, int letter){

    cellStates cell = USER;

    if(!letter)
        hexCells[row-1][column-'A'].setName(cell);
    else{
        cell = COMPUTER;
        hexCells[row-1][column-'A'].setName(cell);
    }
    /*for the remember that last play*/
    lastPlay.setRow(row-1);
    lastPlay.setColumn(column-'A');
    lastPlay.setName(cell);
}

Hex :: Cell Hex :: play(){

    int row1,column1,flag2 = 0;
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

    /*change of oreder x to o in pve mode*/
    if(getOrder() == 1){
        flag2 = 1;
        setOrder(2);
    }

    if(getOrder() == 2 && !flag2)
        setOrder(1);

    return hexCells[row1-1][column1-'A'];
}

bool Hex :: isGameEnded(char letter, int solve[][30]){

    int index;
    cellStates cell = COMPUTER;
    int solveHex[30][30];

    for(int i=0;i<boardSize;i++){
        for(int j=0;j<boardSize;j++){
            if(hexCells[i][j].getName() == letter)/* for example :   ...x.. then 000100 in solvehex vector */ 
                solveHex[i][j] = 1;
            else
                solveHex[i][j] = 0;
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

int Hex :: solveHexGame(int solveHex[][30], int solve[][30], int index){

    int flag=0, visited[30][30] = {0};
    vector<int> temp;

    /*in this block the x's in the first row or the O's in the first column
    are sent to the function one by one, because if a letter does not satisfy
    the termination condition, the other letter is checked.*/
    for(int i=0;i<getBoardSize();i++){

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

bool Hex :: whoIsWinnerComputer(int solveHex[][30], int solve[][30], int index1, int index2, int visited[][30]){

    /*if program reach until last row , game over and the letter wins*/
    if(index1 == getBoardSize()){
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

bool Hex :: whoIsWinnerUser(int solveHex[][30], int solve[][30], int index1, int index2, int visited[][30]){

    if(index2 == getBoardSize()){
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

bool Hex :: outOfBorder(int solveHex[][30], int index1, int index2, int visited[][30]){

    int flag = 0;

    if(index1 >= 0 && index1 < getBoardSize() && index2 >= 0 && index2 < getBoardSize())
        flag = 1;
    
    if(flag)
        if(solveHex[index1][index2] == 1){
            /*control that it doesn't go back to places it's gone before*/
            visited[index1][index2] = 1;
            return true;
        }
    return false;
}

void Hex :: loadFileInformations(const string& fileName, int& counter){

    int temp2,temp;
    string str;
    ifstream inStream;
    inStream.open(fileName);

    if(inStream.fail())
        cerr << "error opening the file : " << fileName;
    else{
        /*because of additional information in first line,in file*/
        getline(inStream,str);
        temp = str.find("u");
    
        if(str.substr(temp) == "user versus computer")
            setMode(0);
        else
            setMode(1);
        
        temp2 = str.find(":");   /*for board size*/
        setBoardSize(str[temp2+1]-'0');    /*setting new board size(in loaded game)*/

        getline(inStream,str);
        temp = str.find(":");    /*taking order*/
        setOrder(str[temp+1]-'0');

        /*allocating memory for hexCells again*/
        hexCells = new Hex :: Cell*[getBoardSize()];
        for(int i=0;i<getBoardSize();i++)
                hexCells[i] = new Hex :: Cell[getBoardSize()];

        inStream >> *this;    /*taking board with overloading extraction operator*/
    }
    inStream.close();
    setCounterPreviousValue(counter);
}

/*in this function, sets the counter that provides the termination condition for the loaded game.*/
void Hex :: setCounterPreviousValue(int& counter){

    int temp=0;
    cellStates cell=USER;

    for(int i=0;i<getBoardSize();i++)
        for(int k=0;k<getBoardSize();k++)
            if(hexCells[i][k].getName() == cell)
                temp++;
    
    counter = temp-1;
}

void Hex :: saveFileInformations(const string& fileName){
    
    ofstream outStream;
    outStream.open(fileName);
    
    if(outStream.fail())
        cerr << "error opening the file " <<fileName;
    else{
        /*writing to file*/
        outStream << "board size is:" << getBoardSize() << "\t";
        outStream << "mode is : ";
        if(getMode() == 0)
            outStream << "user versus computer\n";
        else 
            outStream << "user versus user\n";
        
        outStream << "order:" << getOrder() << "\n";

        outStream << *this;    /*writing board with overloading extraction operator*/
    }
    outStream.close();
}

int Hex :: getMarkedCellAllGame(){

    markedCellAll += 2;
    return markedCellAll;
}

bool operator ==(const Hex& leftSide, const Hex& rightSide){

    cellStates cell = USER,cell2 = EMPTY;
    int first=0,second=0;

    for(int i=0;i<leftSide.getBoardSize();i++){
        for(int k=0;k<leftSide.getBoardSize();k++){
            /*for user vs computer*/
            if(!leftSide.getMode()){
                if(leftSide.hexCells[i][k].getName() == cell)
                    first++;
            }
            /*for user vs user*/
            else{
                if(leftSide.hexCells[i][k].getName() != cell2)
                    first++;
            }
        }
    }

    /*for rightSide*/
    for(int i=0;i<rightSide.getBoardSize();i++){
        for(int k=0;k<rightSide.getBoardSize();k++){
            if(!(rightSide.getMode())){
                if(rightSide.hexCells[i][k].getName() == cell)
                    second++;
            }
            else{
                if(rightSide.hexCells[i][k].getName() != cell2)
                    second++;
            }
        }
    }
    if(first > second)
        cout << "first game has more marked cell second game\n\n";
    
    else if(second > first)
        cout << "second game has more marked cell first game\n\n";

    return (first == second);
}

Hex Hex :: operator --(){

    for(int i=0;i<getBoardSize();i++)
        for(int k=0;k<getBoardSize();k++)
            if(lastPlay.getRow() == i && lastPlay.getColumn() == k)    /*if loop comes to lastplay location then it deletes move in lastplay location*/
                hexCells[i][k].setName('.');

    this->output();
    this->playGame();    /*to take new entry*/

    return *this;
}

Hex Hex :: operator --(int ignoreMe){

    Cell temp = lastPlay;
    cellStates cell = EMPTY;
    int flag = 1;

    oldCounter = getCounter()+1;    /*storing old counter because of i will change counter*/

    if(getMode()){
        if(getOrder() == 2){
            flag = 0;
            setOrder(1);
        }
        
        if(getOrder() == 1 && flag)
            setOrder(2);
    }

    else 
        if(getOrder() == 2)
            setOrder(1);

    this->output();
    this->playGame();

    for(int i=0;i<getBoardSize();i++)
        for(int k=0;k<getBoardSize();k++)
            if(temp.getRow() == i && temp.getColumn() == k)
                hexCells[i][k].setName(static_cast<char> (cell));

    setCounter(oldCounter);   /*setting again the counter*/

    return *this;
}

ostream& operator <<(ostream& outStream, const Hex& game){
    
    int k;
    
    outStream << "\t\t\tX DOMAIN\n\n\t";
    /*to write the letter of column*/
    for(k='a';k<game.getBoardSize()+'a';k++)   outStream <<static_cast<char>(k)<<"\t";
    outStream <<"\n";

    for(int i=0;i<game.getBoardSize();i++){
        outStream << i+1<<"\t";           /*to print row number*/
        for(k=0;k<game.getBoardSize();k++)
            outStream << game.hexCells[i][k].getName() << "\t";

        if((i+1) == game.boardSize/2)
            outStream << "O DOMAIN";
        outStream <<"\n\n";
    }
    return outStream;
}

istream& operator >>(istream& inStream, Hex& game){

    int flag;
    string str;
    cellStates cell1 = EMPTY, cell2 = USER, cell3 = COMPUTER;

    /*reading file to hexcells vector*/
    for(int k=0;!inStream.eof();){
        flag = 0;
        getline(inStream,str);
        
        for(long unsigned int i=0,j=0;i<str.length();i++)
            if(str[i] == cell1 || str[i] == cell2 || str[i] == cell3){    /*taking only '.', 'o', 'x'*/
                game.hexCells[k][j] = Hex :: Cell(k,j,str[i]);
                flag = 1;
                j++;
            }
        
        if(flag)
            k++;
    }
    return inStream;
}

void Hex :: upperCaseLetterWhoWin(int solve[][30]){

    for(int i=0;i<boardSize;i++)
        for(int k=0;k<boardSize;k++)
            if(solve[i][k] == 1)
                hexCells[i][k].setName(hexCells[i][k].getName()-32);
}

// Hex :: ~Hex(){

//     for(int i=0;i<getBoardSize();i++)
//         if(hexCells[i] != nullptr)
//             delete [] hexCells[i];
    
//     if(hexCells != nullptr)
//         delete [] hexCells;
// }