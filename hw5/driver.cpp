#include <iostream>
#include "hexGame.h"
#include "hexAdapter.h"
#include "hexVector.h"
#include "hexArray1D.h"

using namespace std;
using namespace mervesHex ;

bool checkIsfinish(const hexVector& vectorObject, const hexArray1D& array1DObject, const hexAdapter<deque>& adapterObject, int gameNum);
bool detectBoardError(vector <AbstractHex *> boards);

int main(){

    int game;
    hexVector vectorObject, tempVector;
    hexArray1D array1DObject, tempArray;
    hexAdapter<deque> adapterObject;
    vector <AbstractHex *> boards;

    for(int temp = 0;temp<3;temp++){

        do{
            
            cout << "\nwhich game do you want to play ?\n\nif you want to hexVector press 0,\nelse if you want to hexArray1D press 1,\nelse if you want to hexAdapter press 2\n";
            cin >> game;

            if(checkIsfinish(vectorObject,array1DObject,adapterObject,game))
                cout << "This game is over! select new one...\n";

        }while((game != 0 && game != 1 && game != 2) || checkIsfinish(vectorObject, array1DObject, adapterObject,game) );
        
        if(game == 0){

            vectorObject.getBoardSizeInput();
            vectorObject.creatBoard();
            vectorObject.getModeInput();
            vectorObject.setOrder(1);
            vectorObject.playGame();
        }

        else if(game == 1){

            array1DObject.getBoardSizeInput();
            array1DObject.creatBoard();
            array1DObject.getModeInput();
            array1DObject.setOrder(1);
            array1DObject.playGame();
        }

        else{
            adapterObject.getBoardSizeInput();
            adapterObject.creatBoard();
            adapterObject.getModeInput();
            adapterObject.setOrder(1);
            adapterObject.playGame();
        }
    }

    return 0;
}

/* it checks that whether choosed game is done or not */
bool checkIsfinish(const hexVector& vectorObject, const hexArray1D& array1DObject, const hexAdapter<deque>& adapterObject, int gameNum){

    if(gameNum == 0)
        return vectorObject.getIsFinish();
    
    else if(gameNum == 1)
        return array1DObject.getIsFinish();
    
    else
        return adapterObject.getIsFinish();
}

bool detectBoardError(vector <AbstractHex *> boards){

    cellStates cell1 = EMPTY, cell2 = USER, cell3 = COMPUTER;

    for(long unsigned int i=0;i<boards.size();i++){
        if(boards[i]->getSize() < 5)
            return false;
        
        for(int k=0;k<boards[i]->getSize();k++)
            for(int j=0;j<boards[i]->getSize();j++)
                if((*(boards[i]))(k,j) != cell1 && (*(boards[i]))(k,j) != cell2 && (*(boards[i]))(k,j) != cell3)
                    return false;
    }
    return true;
}