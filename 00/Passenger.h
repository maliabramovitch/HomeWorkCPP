//
// Created by Mali Abramovitch on 26/10/2022.
//

#ifndef INC_01_PASSENGER_H
#define INC_01_PASSENGER_H


typedef struct Passenger* Passenger;
/*creating instance of Passenger*/
Passenger create(const char* line);

/*prints in format*/
char* lable(Passenger p);


/*creating a copy of Passenger*/
Passenger passcpy(Passenger p);

#endif //INC_01_PASSENGER_H
