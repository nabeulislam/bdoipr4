#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Constraints {
    int max_n;
    int max_q;
    int max_v;
    bool allow_type2;
};

Constraints get_constraints(const string& sub) {
    if (sub == "samples") return {200000, 200000, 100000000, true};
    if (sub == "sub1")    return {1000,   1000,   10000,     true};
    if (sub == "sub2")    return {5000,   5000,   1000000,   true};
    if (sub == "sub3")    return {200000, 200000, 10000000,  false}; // Type 1 only
    if (sub == "sub4")    return {200000, 200000, 10000000,  true};
    if (sub == "sub5")    return {200000, 200000, 100000000, true};
    quitf(_fail, "Unknown subtask: %s", sub.c_str());
    return {0, 0, 0, false};
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string subtask = (argc > 1) ? argv[1] : "sub5";
    Constraints c = get_constraints(subtask);

    int n = inf.readInt(1, c.max_n, "n");
    inf.readEoln();

    for (int i = 1; i <= n; i++) {
        inf.readInt(0, c.max_v, "a_i");
        if (i < n) inf.readSpace();
    }
    inf.readEoln();

    int q = inf.readInt(1, c.max_q, "q");
    inf.readEoln();

    for (int i = 1; i <= q; i++) {
        int t = inf.readInt(1, c.allow_type2 ? 2 : 1, "t");
        inf.readSpace();

        if (t == 1) {
            int l = inf.readInt(1, n, "l");
            inf.readSpace();
            int r = inf.readInt(l, n, "r");
            inf.readEoln();
        } else {
            int u = inf.readInt(1, n, "u");
            inf.readSpace();
            int v = inf.readInt(0, c.max_v, "v");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}