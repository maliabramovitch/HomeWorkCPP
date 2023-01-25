//
// Created by Mali Abramovitch on 25/01/2023.
//

#ifndef INC_51_MYEXCEPTION_H
#define INC_51_MYEXCEPTION_H

#include <string>
#include <utility>
#include <iostream>

class MyException {
private:
    std::string message;
public:
    explicit MyException(std::string msg) : message(std::move(msg)){};
    void printMessage() {std::cerr << message;}
};


#endif //INC_51_MYEXCEPTION_H
