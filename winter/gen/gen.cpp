#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;


vector<int> pickDistinct(int c, int n) {
    vector<int> all(n);
    for (int i = 0; i < n; i++) all[i] = i;
    for (int i = 0; i < c; i++) {
        int j = rnd.next(i, n - 1);
        swap(all[i], all[j]);
    }
    all.resize(c);
    return all;
}

string makeRow(int n, int c, int style) {
    string s(n, '0');
    if (style == 0) {
        for (int p : pickDistinct(c, n)) s[p] = '1';
    } else if (style == 1) {
        s[0] = '1';
        s[n - 1] = '1';
        int need = c - 2;
        if (need > 0)
            for (int p : pickDistinct(need, n - 2)) s[p + 1] = '1';
    } else if (style == 2) {
        int start = rnd.next(0, n - c);
        for (int i = 0; i < c; i++) s[start + i] = '1';
    } else if (style == 3) {
        for (int i = 0; i < c; i++) s[i] = '1';
    } else {
        for (int i = 0; i < c; i++) s[n - 1 - i] = '1';
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T     = atoi(argv[1]);
    int maxN  = atoi(argv[2]);
    int sumN  = atoi(argv[3]);
    int kMin  = atoi(argv[4]);
    int kMax  = atoi(argv[5]);
    int mode  = atoi(argv[6]);
    int style = atoi(argv[7]);
    int tight = atoi(argv[8]);
    int sym   = atoi(argv[9]);
    int cmax  = atoi(argv[10]);
    

    const int MAXM = 1000;
    if (sumN < 2 * T) {
        fprintf(stderr, "sumN must be at least 2*T\n");
        return 1;
    }

    int used = 0;
    printf("%d\n", T);
    for (int t = 0; t < T; t++) {
        int remaining = T - t - 1;
        int budget = (sumN - used) - 2 * remaining;
        int cap = min(maxN, budget);
        if (cap < 2) {
            fprintf(stderr, "not enough budget for test %d\n", t);
            return 1;
        }

        int n = (mode == 1) ? cap : rnd.next(2, cap);
        used += n;

        int c1, c2;
        if (sym) {
            c1 = c2 = rnd.next(2, max(2, min(min(n, cmax), 333)));
        } else {
            c1 = rnd.next(2, max(2, min(min(n, cmax), 498)));
            int hi2 = min(min(n, cmax), min((MAXM - c1) / 2, MAXM - 2 * c1));
            c2 = rnd.next(2, max(2, hi2));
        }

        int lowestM = max(max(3, c1 + 2 * c2), c2 + 2 * c1);
        int m;
        if (tight == 1) m = lowestM;
        else if (tight == 2) m = MAXM;
        else m = rnd.next(lowestM, MAXM);

        int k = rnd.next(kMin, kMax);

        int s1 = (style == -1) ? rnd.next(0, 4) : style;
        int s2 = (style == -1) ? rnd.next(0, 4) : style;

        string a = makeRow(n, c1, s1);
        string b;
        if (sym == 1) {
            b = a;
        } else if (sym == 2) {
            b = a;
            reverse(b.begin(), b.end());
        } else {
            b = makeRow(n, c2, s2);
        }

        printf("%d %d %d\n", n, k, m);
        printf("%s\n", a.c_str());
        printf("%s\n", b.c_str());
    }
    return 0;
}