//
// Created by Mali Abramovitch on 02/12/2022.
//

#ifndef INC_02_GAMESQUARE_H
#define INC_02_GAMESQUARE_H


class GameSquare {

public:
    /**
    * There is no need for the big 5 because the fields are builtin types
    */
    explicit GameSquare(int xVal = 0, int yVal = 0);

    __attribute__((unused)) int getX() const { return x; };

    __attribute__((unused)) void setX(int newX) { x = newX; };

    __attribute__((unused)) int getY() const { return y; };

    __attribute__((unused)) void setY(int newY) { y = newY; };

    char getType() const { return type; };

    void setType(char newType) { type = newType; };

    void setXY(int newX, int newY) {
        this->x = newX;
        this->y = newY;
    }

private:
    int x;
    int y;
    char type = 'O';
};


#endif //INC_02_GAMESQUARE_H
