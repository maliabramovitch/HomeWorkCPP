//
// Created by Mali Abramovitch on 26/10/2022.
//
#include <stdlib.h>
#include "Passenger.h"
#include <string.h>


struct Passenger {
    char given_name[16];
    char surname[16];
    char passport_id[16];
    char country[16];
};

Passenger create(const char *line) {
    Passenger p = malloc(sizeof(struct Passenger));
    char *word = (char *) calloc(16, sizeof(char));
    int charIndex = 0;
    int Field = 0;
    for (int i = 0; i < strlen(line); i++) {
        while (line[i] == ' ' || line[i] == '\n') {
            word[charIndex] = '\0';
            if (Field == 0) {strcpy(p->given_name, word);}
            if (Field == 1) {strcpy(p->surname, word);}
            if (Field == 2) {strcpy(p->passport_id, word);}
            if (Field == 3) {strcpy(p->country, word);}
            Field++;
            charIndex = 0;
            word = (char *) calloc(sizeof(char), 16);
            i++;
            break;
        }
        word[charIndex] = line[i];
        charIndex++;
    }
    return p;
}

char *lable(Passenger p) {
    unsigned int sizeN = (strlen(p->given_name) + strlen(p->surname) + strlen(p->passport_id) + 3);
    char *new = calloc(sizeN, sizeof(char *));
    strcat(new, strdup(p->given_name));
    strcat(new, " ");
    strcat(new, strdup(p->surname));
    strcat(new, " ");
    strcat(new, strdup(p->passport_id));
    new[sizeN] = '\0';
    return new;
}


Passenger passcpy(Passenger p) {
    Passenger pn = malloc(sizeof(struct Passenger));
    strcpy(pn->given_name, p->given_name);
    strcpy(pn->surname, p->surname);
    strcpy(pn->passport_id, p->passport_id);
    strcpy(pn->country, p->country);
    return pn;
}

