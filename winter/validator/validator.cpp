#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;


int getOpt(int argc, char* argv[], const string& name, int def) {
    for (int i = 1; i < argc; i++) {
        string a = argv[i];
        while (!a.empty() && a[0] == '-') a.erase(a.begin());
        string prefix = name + "=";
        if (a.compare(0, prefix.size(), prefix) == 0)
            return atoi(a.c_str() + prefix.size());
        if (a == name && i + 1 < argc)
            return atoi(argv[i + 1]);
    }
    return def;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int maxT = getOpt(argc, argv, "maxT", 10000);
    int maxN = getOpt(argc, argv, "maxN", 100000);

    int T = inf.readInt(1, maxT, "T");
    inf.readEoln();

    long long sumN = 0;
    for (int t = 1; t <= T; t++) {
        int n = inf.readInt(1, maxN, "n");
        inf.readSpace();
        inf.readInt(1, 1000, "k");
        inf.readSpace();
        int m = inf.readInt(3, 1000, "m");
        inf.readEoln();

        string s1 = inf.readToken("[01]{" + to_string(n) + "}", "s1");
        inf.readEoln();
        string s2 = inf.readToken("[01]{" + to_string(n) + "}", "s2");
        inf.readEoln();

        int c1 = count(s1.begin(), s1.end(), '1');
        int c2 = count(s2.begin(), s2.end(), '1');

        ensuref(c1 >= 2 && c2 >= 2, "case %d: each string needs at least two 1s", t);
        ensuref(c1 + 2 * c2 <= m, "case %d: c1 + 2*c2 <= m violated", t);
        ensuref(c2 + 2 * c1 <= m, "case %d: c2 + 2*c1 <= m violated", t);

        sumN += n;
    }
    ensuref(sumN <= 100000, "sum of n = %lld exceeds 1e5", sumN);

    inf.readEof();
    return 0;
}