//
// Created by Mali Abramovitch on 02/12/2022.
//

#ifndef INC_02_GAMEMANAGER_H
#define INC_02_GAMEMANAGER_H


#include <string>
#include "Board.h"

class GameManager {
    /**
     * class to run the game.
     * no C'tor so there is no need for the big 5.
     * the function playAlchemize() manage all the allocations.
     */
public:
    void playAlchemize(int boardSize);

private:
    Board* b;
    std::string location;
    char turn = 'r';
    bool checkInput(int x, int y);
    void playTurn(int x, int y);
};


#endif //INC_02_GAMEMANAGER_H
