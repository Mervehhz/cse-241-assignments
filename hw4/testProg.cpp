
#include <iostream>
#include "hexGame.h"

using namespace std;

/* Author : Merve Horuz */

void selectGameErrorHandling(int& selectGame1, int& selectGame2, int gameNum);

int Hex :: markedCellAll = 0;

int main(){

    char multiSingle,comp;
    int gameNum,selectGame,temp=0,flag,selectGame1,selectGame2;
    Hex object;
    vector<Hex> games,finishGame;

    do{
        cout << ",,,,,,,,,,,,,,,HEX GAME,,,,,,,,,,,,,,,,\n\n" << "enter 'm'  for multi game, enter 's' single game\n";
        cin >> multiSingle;

        if(multiSingle != 'm' && multiSingle != 's')
            cerr << "ERROR please enter 'm' or 's' !!\n";

    }while(multiSingle != 'm' && multiSingle != 's');

    object.setMultiSingle(multiSingle);
    if(multiSingle == 's'){
        object.setCounter(0);
        object.configurations();
        object.playGame();
    }
    
    else{
        do{
            cout << "how many games want to play ? ->> ";
            cin >> gameNum;

            if(gameNum < 5)
                cerr << "\nERROR.. please enter valid number that is at least five number of game !! \n";
        }while(gameNum < 5);

        /*setting mode, counter and board size in all games*/
        for(int i=0;i<gameNum;i++){
            object.setCounter(0);
            object.configurations();
            object.setIsFinish(0);
            games.push_back(object);
        }
    
        for(int k=0;temp < gameNum;k++){

            flag = 1;

            do{
                cout << "\nwhich game do you want to play ?(for ex : 1,2,3...) --> ";
                cin >> selectGame;

                if(selectGame < 1 || selectGame > gameNum){
                    cerr << "\nERROR please enter between bound !! \n";
                    flag=0;
                }
                if(games[selectGame-1].getIsFinish() && flag)
                    cerr << "\nERROR this game is done !!\n";

        }while(selectGame < 1 || selectGame > gameNum || games[selectGame-1].getIsFinish());
            
            games[selectGame-1].playGame();
            
            /*temp = number of ended games*/
            temp = 0;
            for(int j=0;j<gameNum;j++)
                if(games[j].getIsFinish())
                    temp++;
        
            games[selectGame-1].output();

            cout << "do you want to comparing two games ? if you want, then press 'y' or 'Y'.\n";
            cin >> comp;

            if(comp == 'y' || comp == 'Y'){

                selectGameErrorHandling(selectGame1,selectGame2,gameNum);
                if(games[selectGame1-1] == games[selectGame2-1])
                    cout << selectGame1 << " and " << selectGame2 << " have same marked cell " << endl;
                
                else
                    cout << selectGame1 << " and " << selectGame2 << " do not have same marked cell " << endl;
            }

            cout << "\nnumber of marked cells in all game is " << games[selectGame-1].getMarkedCellAllGame();
        }
        
        if(temp == gameNum)
            cout << "\ngames is done !! bye.\n\n";
    }

    return 0;
}

void selectGameErrorHandling(int& selectGame1, int& selectGame2, int gameNum){

    do{
        cout << "\nwhich games do you want to compare ? first game --> ";
        cin >> selectGame1;
        cout << "\n";

        if(selectGame1 < 1 || selectGame1 > gameNum)
            cerr << "\nERROR please enter between bound !! \n";
        

    }while(selectGame1 < 1 || selectGame1 > gameNum);

    do{ 
        cout << "\nwhich games do you want to compare ? second game --> ";
        cin >> selectGame2;
        cout << "\n";

        if(selectGame2 < 1 || selectGame2 > gameNum)
            cerr << "\nERROR please enter between bound !! \n";
        
    }while(selectGame2 < 1 || selectGame2 > gameNum);
}