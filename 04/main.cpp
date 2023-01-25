#include <iostream>
#include <valarray>
#include "World.h"


using namespace std;

void checkCnf(int n) {
    if (n < 3 || n > 1000000) {
        cerr << "Usage: run the program with <init file name> <location file name>" << '\n';
        exit(0);
    }
}

int main(int argc, char **argv) {
    checkCnf(argc);
    string s;
    cin >> s;
    int n = stoi(s);
    if (n < 1) {
        cerr << "oopsi poopsi... invalid generation size\n";
        exit(3);
    }
    World *w; w = new World(argv[1], argv[2], n);
    w->RunTheWorld();
    delete w;

}
