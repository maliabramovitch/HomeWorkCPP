//
// Created by Mali Abramovitch on 02/12/2022.
//

#include "GameManager.h"
#include <iostream>
#include <string>
#include <sstream>


void GameManager::playAlchemize(int boardSize) {
    if (boardSize < 2) {
        std::cerr << "Invalid run arguments; run the game with board size.\n";
        exit(0);
    }
    b = new Board(boardSize);
    b->printBoard();
    while (b->getPlayedSquares() < (b->getBoardSize() * b->getBoardSize())) {
        if (std::cin.eof()) break;
        if (turn == 'r') {
            std::cout << "R:\n";
        } else {
            std::cout << "B:\n";
        }
std::getline(std::cin, location);
        int x, y;
        std::stringstream ss(location);
        ss >> x;
        ss >> y;
        if (checkInput(x, y)) {
            playTurn(x, y);
            b->printBoard();
        }
    }
    if (b->getRed()->getScore() == b->getBlue()->getScore()) {
        std::cout << "The game ended with a tie\n";
    }
    if (b->getRed()->getScore() > b->getBlue()->getScore()) {
        std::cout << "Red won\n";
    } if (b->getRed()->getScore() < b->getBlue()->getScore()){
        std::cout << "Blue won\n";
    }
    delete b;

}

bool GameManager::checkInput(int x, int y) {
    if (x < 1 || y < 1 || x > b->getBoardSize() || y > b->getBoardSize() || b->getGameSquare(x, y).getType() != 'O') {
        std::cerr << "Invalid row/col index or non free cell\n";
        return false;
    }
    return true;
}

void GameManager::playTurn(int x, int y) {
    char myBottle, otherBottle, jem;
    Player *p;
    if (turn == 'r') {
        p = b->getRed();
        myBottle = 'R';
        otherBottle = 'B';
        jem = 'r';
        turn = 'b';
    } else {
        p = b->getBlue();
        myBottle = 'B';
        otherBottle = 'R';
        jem = 'b';
        turn = 'r';
    }
    GameSquare gs1, gs2;
    b->setGameSquare(x, y, myBottle);
    ++(*b);
    if (b->getPlayedSquares() < 1) return;
    for (int row1 = (x - 1); row1 < (x + 2); ++row1) {
        if (row1 < 1 || row1 > b->getBoardSize()) continue;
        for (int col1 = y - 1; col1 < y + 2; ++col1) {
            if (col1 < 1 || col1 > b->getBoardSize()) continue;
            if (row1 == x && col1 == y) continue;
            gs1 = b->getGameSquare(row1, col1);
            if (gs1.getType() == 'r') {
                --(*b->getRed());
                b->setGameSquare(row1, col1, 'X');
                continue;
            }
            if (gs1.getType() == 'b') {
                --(*b->getBlue());
                b->setGameSquare(row1, col1, 'X');
                continue;
            }
            if (gs1.getType() == 'O') {
                for (int row2 = (row1 - 1); row2 < (row1 + 2); ++row2) {
                    if (row2 < 1 || row2 > b->getBoardSize()) continue;
                    for (int col2 = (col1 - 1); col2 < (col1 + 2); ++col2) {
                        if (col2 < 1 || col2 > b->getBoardSize()) continue;
                        if ((row2 == x && col2 == y) || (row2 == row1 && col2 == col1)) continue;
                        gs2 = b->getGameSquare(row2, col2);
                        if (gs2.getType() == otherBottle && gs1.getType() != 'X') {
                            b->setGameSquare(row1, col1, jem);
                            ++(*p);
                            ++(*b);
                        }
                        if (gs2.getType() == myBottle) {
                            if (gs1.getType() == 'O') ++(*b);
                            if (gs1.getType() == p->getColor())--(*p);
                            b->setGameSquare(row1, col1, 'X');

                        }
                    }
                }
            }
        }

    }
}



