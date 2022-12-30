//
// Created by Mali Abramovitch on 02/12/2022.
//

#ifndef INC_02_BOARD_H
#define INC_02_BOARD_H


#include "GameSquare.h"
#include "Player.h"

class Board {
public:
    explicit Board(int size); // C'tor
    Board(Board const &other); // copy C'tor
    Board(Board&& other) noexcept ; // move C'tor
    ~Board(); // D'tor
    Board& operator=(Board const &other); // copy =
    Board& operator=(Board&& other) noexcept ; // move =

    int getBoardSize() const {return boardSize;};
    GameSquare** getBoardMatrix() const {return boardMatrix;}
    Player* getRed(){return red;};
    Player* getBlue(){return blue;};
    int getPlayedSquares() const {return playedSquares;}

    __attribute__((unused)) void setPlayedSquares(int ps) { playedSquares = ps;}
    GameSquare getGameSquare(int x, int y);
    void setGameSquare(int x, int y, char c);
    void printBoard();
    void operator++() {++playedSquares;}

private:
    int boardSize;
    GameSquare** boardMatrix;
    Player* red;
    Player* blue;
    int playedSquares;

};


#endif //INC_02_BOARD_H
