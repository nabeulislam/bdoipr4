#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "n");
    inf.readSpace();
    int m = inf.readInt(1, 500, "m");
    inf.readSpace();
    inf.readInt(0, n * m, "k");
    inf.readSpace();
    inf.readInt(1, n * m, "s");
    inf.readEoln();

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            inf.readInt(1, 1000000000, "a");
            if (c + 1 < m) inf.readSpace();
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}