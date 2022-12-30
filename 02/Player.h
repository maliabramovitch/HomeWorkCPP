//
// Created by Mali Abramovitch on 02/12/2022.
//

#ifndef INC_02_PLAYER_H
#define INC_02_PLAYER_H


class Player {
public:
    /**
    * There is no need for the big 5 because the fields are builtin types
    */
    explicit Player(char colorr, int scoree = 0);
    char getColor() const {return color;}
    int getScore() const {return score;}
    __attribute__((unused)) void setScore(int scoree) {score = scoree;}

    /**
     * ++score
     */
    void operator++();
    /**
     * --score
     */
    void operator--();


private:
    char const color;
    int score;
};


#endif //INC_02_PLAYER_H
