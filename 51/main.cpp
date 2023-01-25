#include "MyException.h"
#include "Neverland.h"
using namespace std;


int main(int argc, char* argv[]) {
    if (argc < 2) {
        exit(-2);
    }
    string out = argv[argc-1];
    if (out.substr(0, 4) != "[-0]") {
        out = "output.dat";
    }
    Neverland* nl = new Neverland();
    for (int i = 1; i < argc; ++i) {
        try {
            nl->initTransportLine(argv[i]);
        }
        catch (MyException e) {
            e.printMessage();
            continue;
        }
    }
    nl->getLinesInfo(out);
    delete nl;
return 0;
}
