#include <iostream>
#include "hexGame.h"

using namespace std;

/* Author : Merve Horuz */

int Hex :: markedCellAll = 0;

int main(){

    char multiSingle;
    int gameNum,selectGame,temp=0,flag=1;
    Hex object;
    vector<Hex> games,finishGame;

    do{
        cout << ",,,,,,,,,,,,,,,HEX GAME,,,,,,,,,,,,,,,,\n\n" << "enter 'm'  for multi game, enter 's' single game\n";
        cin >> multiSingle;

        if(multiSingle != 'm' && multiSingle != 's')
            cerr << "ERROR please enter 'm' or 's' !!\n";

    }while(multiSingle != 'm' && multiSingle != 's');

    if(multiSingle == 's'){
        object.setCounter(0);
        object.configurations();
        object.playGame(multiSingle);
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
            flag=1;
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
            games[selectGame-1].playGame(multiSingle);
            
            /*temp = number of ended games*/
            temp = 0;
            for(int j=0;j<gameNum;j++)
                if(games[j].getIsFinish())
                    temp++;
            
            if(games[0].compareHexGame(games[1]) == 1)
                cout << "\nfirst game has more marked cell for user\n";
            else if(games[0].compareHexGame(games[1]) == 0)
                cout << "\nsecond game has more marked cell for user\n";
            else
                cout << "\nsecond game and first game has same marked cell for user\n";

            cout << "\nnumber of marked cells in all game is " << games[selectGame-1].getMarkedCellAllGame();
        }
        
        if(temp == gameNum)
            cout << "\ngames is done !! bye.\n\n";
    }   
    return 0;
}