#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int clamp_value(int value, int low, int high) {
    return max(low, min(value, high));
}

int pick_bit_edge(int max_v) {
    if (rnd.next(0, 4) == 0) {
        // Checkpoint 100 boundaries
        int max_b = max_v / 100;
        int b = rnd.next(0, max_b);
        return clamp_value(b * 100 + rnd.next(-2, 2), 0, max_v);
    }
    // 64-bit word boundaries (bitpos = 0, 62, 63)
    int max_k = max_v >> 6;
    int k = rnd.next(0, max_k);
    return clamp_value((k << 6) + rnd.next(-2, 2), 0, max_v);
}

int pick_hand_small(int max_v) {
    vector<int> pool = {0, 1, 2, 3, 4, 5, 62, 63, 64, 65, 99, 100, 101, 127, 128, max_v - 1, max_v};
    vector<int> valid;
    for (int x : pool) {
        if (x >= 0 && x <= max_v) valid.push_back(x);
    }
    return valid[rnd.next(0, (int)valid.size() - 1)];
}

int gen_val(const string& mode, int max_v) {
    if (mode == "hand_small")   return pick_hand_small(max_v);
    if (mode == "bit_edge")     return pick_bit_edge(max_v);
    if (mode == "max_overflow") return rnd.next(max(0, max_v - 500), max_v);
    return rnd.next(0, max_v);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string mode  = argv[1];
    int n        = atoi(argv[2]);
    int q        = atoi(argv[3]);
    int max_v    = atoi(argv[4]);
    int upd_prob = atoi(argv[5]); // 0 to 100 (% chance of Type 2 update)

    cout << n << "\n";
    for (int i = 0; i < n; i++) {
        int val = gen_val(mode, max_v);
        cout << val << (i + 1 == n ? "" : " ");
    }
    cout << "\n";

    cout << q << "\n";
    for (int i = 0; i < q; i++) {
        int t = (rnd.next(1, 100) <= upd_prob) ? 2 : 1;

        if (t == 1) {
            int l = 1, r = n;
            if (mode == "index_edge") {
                int kind = rnd.next(0, 3);
                if (kind == 0)      { l = 1; r = 1; }
                else if (kind == 1) { l = n; r = n; }
                else if (kind == 2) { l = 1; r = n; }
                else                { l = rnd.next(1, n); r = rnd.next(l, n); }
            } else if (mode == "max_overflow") {
                if (rnd.next(1, 100) <= 75) {
                    l = rnd.next(1, max(1, n / 20));
                    r = rnd.next(max(l, n - n / 20), n);
                } else {
                    l = rnd.next(1, n);
                    r = rnd.next(l, n);
                }
            } else {
                l = rnd.next(1, n);
                r = rnd.next(l, n);
            }
            cout << 1 << " " << l << " " << r << "\n";
        } else {
            int u;
            if (mode == "index_edge") {
                int kind = rnd.next(0, 2);
                if (kind == 0)      u = 1;
                else if (kind == 1) u = n;
                else                u = rnd.next(1, n);
            } else {
                u = rnd.next(1, n);
            }
            int v = gen_val(mode, max_v);
            cout << 2 << " " << u << " " << v << "\n";
        }
    }

    return 0;
}
