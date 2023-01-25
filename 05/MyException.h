//
// Created by Mali Abramovitch
// Created by Alon Negrin
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
