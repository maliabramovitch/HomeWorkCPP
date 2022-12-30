//
// Created by Mali Abramovitch on 02/12/2022.
//

#include <iostream>
#include "Board.h"

using namespace std;

Board::Board(int size) : boardSize(size) {
    boardMatrix = new GameSquare *[size];
    for (int i = 0; i < size; i++) {
        boardMatrix[i] = new GameSquare[size];
        for (int j = 0; j < boardSize; j++) {
            boardMatrix[i][j].setXY(i + 1, j + 1);
        }
    }
    red = new Player('R');
    blue = new Player('B');
    playedSquares = 0;
}

Board::Board(const Board &other) : boardSize(other.boardSize) {
    boardMatrix = new GameSquare *[other.boardSize];
    for (int i = 0; i < other.boardSize; i++) {
        boardMatrix[i] = other.getBoardMatrix()[i];
    }
    red = new Player(*other.red);
    blue = new Player(*other.blue);
    playedSquares = other.playedSquares;
}

Board::Board(Board &&other) noexcept : boardSize(other.boardSize), boardMatrix(other.boardMatrix), red(other.red),
                                       blue(other.blue), playedSquares(other.playedSquares) {
    other.boardMatrix = nullptr;
    other.boardSize = 0;
    other.red = nullptr;
    other.blue = nullptr;
    other.boardSize = 0;
}

Board::~Board() {
    delete red;
    delete blue;
    for (int i = 0; i < boardSize; i++) {
        delete[] boardMatrix[i];
    }
    delete[] boardMatrix;

}

Board &Board::operator=(const Board &other) {
    if (this == &other) return *this;
    if (boardSize != other.boardSize) {
        for (int i = 0; i < this->boardSize; ++i) {
            delete[] boardMatrix[i];
        }
        delete boardMatrix;
        boardMatrix = new GameSquare *[other.boardSize];
    }

    for (int i = 0; i < other.boardSize; ++i) {
        boardMatrix[i] = other.getBoardMatrix()[i];
    }
    boardSize = other.boardSize;
    blue = other.blue;
    red = other.red;
    playedSquares = other.playedSquares;

    return *this;
}

Board &Board::operator=(Board &&other) noexcept {
    boardSize = other.boardSize;
    boardMatrix = other.boardMatrix;
    red = other.red;
    blue = other.blue;
    playedSquares = other.playedSquares;

    other.boardMatrix = nullptr;
    other.boardSize = 0;
    other.red = nullptr;
    other.blue = nullptr;
    other.boardSize = 0;

    return *this;
}

GameSquare Board::getGameSquare(int x, int y) {
    return boardMatrix[x - 1][y - 1];
}

void Board::setGameSquare(int x, int y, char c) {
    boardMatrix[x-1][y-1].setType(c);
}
void Board::printBoard() {
    cout << "Red count: " << red->getScore() << '\t' << "Blue count: " << blue->getScore() << '\n';
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            cout << boardMatrix[i][j].getType() << '\t';
        }
        cout << '\n';
    }
}

