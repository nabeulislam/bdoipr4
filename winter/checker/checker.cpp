#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

// Set to true if getting Line 1 right is strictly required to earn points on Line 2 & 3.
// Set to false if Line 1 (30%), Line 2 (30%), and Line 3 (40%) are scored independently.
const bool REQUIRE_LINE1_FOR_PARTIAL = true;

int compute_min_leftover(int a, int b, int m) {
    int mn = m;
    for (int x = 1; a * x + b * (x + 1) <= m; ++x) {
        int y = (m - a * x) / b;
        mn = min(mn, m - a * x - b * y);
    }
    return mn;
}

int main(int argc, char* argv[]) {
    // Use registerChecker("<task_short_name>", argc, argv) for TPS/CMS testlib.h.
    // (If testing locally with standard Polygon testlib.h, replace with registerTestlibCmd(argc, argv);)
    registerChecker("winter", argc, argv);

    int T = inf.readInt();
    long long total_pct = 0; // Sum of percentage points (0..100) across all T test cases

    for (int tc = 1; tc <= T; ++tc) {
        // setTestCase(tc);

        int n = inf.readInt();
        int k = inf.readInt();
        int m = inf.readInt();
        string s1 = inf.readToken();
        string s2 = inf.readToken();

        int l1 = n + 1, r1 = 0, c1 = 0;
        int l2 = n + 1, r2 = 0, c2 = 0;

        for (int i = 0; i < n; ++i) {
            if (s1[i] == '1') {
                l1 = min(l1, i + 1);
                r1 = max(r1, i + 1);
                c1++;
            }
            if (s2[i] == '1') {
                l2 = min(l2, i + 1);
                r2 = max(r2, i + 1);
                c2++;
            }
        }

        // Compute optimal max travel time for Orphanage 1 and Orphanage 2
        int mn1 = 2e9, mn2 = 2e9;
        for (int i = 1; i <= n; ++i) {
            int t1 = max({i - l1, r1 - i, k + i + r2});
            mn1 = min(mn1, t1);

            int t2 = max({i - l2, r2 - i, k + i + r1});
            mn2 = min(mn2, t2);
        }
        int opt_time = min(mn1, mn2);

        // Read contestant's 3 lines for this test case
        long long p_time = ouf.readLong();
        long long p_o    = ouf.readLong();
        long long p_r    = ouf.readLong();
        long long p_left = ouf.readLong();

        int tc_pct = 0;
        bool ok1 = (p_time == opt_time);

        // Part 1: 30% for minimum possible maximum travel time on Line 1
        if (ok1) {
            tc_pct += 30;
        }

        if (!REQUIRE_LINE1_FOR_PARTIAL || ok1) {
            // Part 2: 30% for a valid room on Line 2 achieving opt_time
            if (p_o == -1 && p_r == -1) {
                // Skipped Line 2; 0 points for Part 2
            } else if ((p_o == 1 || p_o == 2) && (p_r >= 1 && p_r <= n)) {
                int i = (int)p_r;
                int actual_time = (p_o == 1)
                    ? max({i - l1, r1 - i, k + i + r2})
                    : max({i - l2, r2 - i, k + i + r1});
                if (actual_time == opt_time) {
                    tc_pct += 30;
                }
            }

            // Part 3: 40% for minimum leftover boxes on Line 3
            // Accepted if it matches the optimal orphanage(s) achieving opt_time
            if (p_left != -1) {
                bool ok3 = false;
                if (mn1 == opt_time && p_left == compute_min_leftover(c1, c2, m)) {
                    ok3 = true;
                }
                if (mn2 == opt_time && p_left == compute_min_leftover(c2, c1, m)) {
                    ok3 = true;
                }
                if (ok3) {
                    tc_pct += 40;
                }
            }
        }

        total_pct += tc_pct;
    }

    if (!ouf.seekEof()) {
        quitf(_wa, "Extra output found after reading %d test cases", T);
    }

    // Score of the file is the average over its test cases
    if (total_pct == 100LL * T) {
        quitf(_ok, "Correct (100%% across all %d test cases)", T);
    } else if (total_pct == 0) {
        quitf(_wa, "Wrong Answer (0%% across all %d test cases)", T);
    } else {
        double score_ratio = (double)total_pct / (100.0 * T);
        quitp(score_ratio, "Partial score: %.2f%% average across %d test cases", score_ratio * 100.0, T);
    }
}