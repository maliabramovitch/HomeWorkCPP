#include "MyException.h"
#include "Neverland.h"

using namespace std;


int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(-2);
    }
    // checks if the user gave a name to the out file
    string out = argv[argc - 1];
    if (out.substr(0, 4) != "[-o]") {
        out = "output.dat";
    } else {
        out = out.substr(4, out.size());
        --argc;
    }
    Neverland *nl; nl = new Neverland();
    for (int i = 1; i < argc; ++i) {
        try {
            nl->initTransportLine(argv[i]);
        }
        catch (MyException& e) {
            e.printMessage();
            continue;
        }
    }
    nl->getLinesInfo(out);
    delete nl;
    return 0;
}