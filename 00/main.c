#include <stdio.h>
#include <stdlib.h>
#include "ADTStack.h"
#include <string.h>
#include "Passenger.h"



int main() {
    FILE *read = fopen("international_passengers.dat", "r");
    if (!read) {
        printf("oopsi poopsi file *for reading* opening went wrong");
        exit(0);
    }
    Stack stk = init(60, (void *(*)(void *)) passcpy, (void (*)(void *)) free, (char *(*)(void *)) lable);
    char *buff = NULL;
    size_t buffSize = 0;
    while ((getline(&buff, &buffSize, read)) != EOF) {
        Passenger p = create(buff);
        push(stk, p);
    }
    print(stk);
    destroy(stk);
    fclose(read);
    free(buff);
}