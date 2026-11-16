#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k, m;
    cin >> n >> k >> m;
    string s1, s2;
    cin >> s1 >> s2;

    int c1 = 0, c2 = 0, max1 = 0, max2 = 0;
    for (int i = 0; i < n; i++) {
        if (s1[i] == '1') { c1++; max1 = i + 1; }
        if (s2[i] == '1') { c2++; max2 = i + 1; }
    }

    int best_time = 1e9, best_o = 1, best_r = 1;

    // Try every room i from 1 to n in both orphanages
    for (int i = 1; i <= n; i++) {
        int t1 = max(max1 - i, k + i + max2); // Packages in Orphanage 1, Room i
        if (t1 < best_time) {
            best_time = t1;
            best_o = 1;
            best_r = i;
        }

        int t2 = max(max2 - i, k + i + max1); // Packages in Orphanage 2, Room i
        if (t2 < best_time) {
            best_time = t2;
            best_o = 2;
            best_r = i;
        }
    }

    int a = (best_o == 1 ? c1 : c2);
    int b = (best_o == 1 ? c2 : c1);

    // Try all possible values of x and pick the largest valid y
    int min_leftover = m;
    for (int x = 1; a * x <= m; x++) {
        int y = (m - a * x) / b;
        if (y > x) {
            min_leftover = min(min_leftover, m - (a * x + b * y));
        }
    }

    cout << best_time << "\n";
    cout << best_o << " " << best_r << "\n";
    cout << -1 << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}