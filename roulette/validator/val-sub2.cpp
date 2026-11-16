#include "testlib.h"
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "n");
    inf.readSpace();
    int m = inf.readInt(1, 500, "m");
    inf.readSpace();
    inf.readInt(0, n * m, "k");
    inf.readSpace();
    inf.readInt(1, 1, "s");
    inf.readEoln();

    vector<vector<int>> a(n, vector<int>(m));
    bool has_two = false;

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            a[r][c] = inf.readInt(1, 2, "a");
            if (a[r][c] == 2) has_two = true;
            if (c + 1 < m) inf.readSpace();
        }
        inf.readEoln();
    }

    inf.readEof();

    if (has_two) {
        vector<vector<int>> dist_bfs(n, vector<int>(m, INF));
        deque<pair<int, int>> dq;
        dist_bfs[0][0] = (a[0][0] == 1 ? 1 : 0);
        dq.push_back({0, 0});

        while (!dq.empty()) {
            auto [r, c] = dq.front();
            dq.pop_front();
            for (int d = 0; d < 4; ++d) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                    int w = (a[nr][nc] == 1 ? 1 : 0);
                    if (dist_bfs[r][c] + w < dist_bfs[nr][nc]) {
                        dist_bfs[nr][nc] = dist_bfs[r][c] + w;
                        if (w == 0) dq.push_front({nr, nc});
                        else dq.push_back({nr, nc});
                    }
                }
            }
        }

        vector<vector<int>> dist_dp(n, vector<int>(m, INF));
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                int w = (a[r][c] == 1 ? 1 : 0);
                if (r == 0 && c == 0) {
                    dist_dp[r][c] = w;
                } else {
                    if (r > 0) dist_dp[r][c] = min(dist_dp[r][c], dist_dp[r - 1][c] + w);
                    if (c > 0) dist_dp[r][c] = min(dist_dp[r][c], dist_dp[r][c - 1] + w);
                }
            }
        }

        int best_bfs = INF;
        int best_dp = INF;
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                if (a[r][c] == 2) {
                    best_bfs = min(best_bfs, dist_bfs[r][c]);
                    best_dp = min(best_dp, dist_dp[r][c]);
                }
            }
        }

        ensuref(best_bfs == best_dp, "Down-Right path is not optimal");
    }

    return 0;
}