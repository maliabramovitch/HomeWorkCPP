#include <iostream>
#include "GameManager.h"

void notGood();

int main(int argc, char** argv) {
    if (argc < 2) notGood();
    int size = std::stoi(argv[1]);
    if (size < 2) notGood();
    auto* gm = new GameManager;
    gm->playAlchemize(size);
    delete gm;
}

void notGood(){
    std::cerr << "Invalid run arguments; run the game with board size.\n";
    exit(0);
}