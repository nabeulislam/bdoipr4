#include "testlib.h"
#include <bits/stdc++.h>


using namespace std;

const int INF = 1e9;
const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};

void enforce_down_right_optimal(int n, int m, vector<vector<int>>& a) {
    bool has_two = false;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (a[r][c] == 2) has_two = true;
        }
    }
    if (!has_two) return;

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

    if (best_bfs < best_dp) {
        int tr = rnd.next(0, n - 1);
        int tc = rnd.next(0, m - 1);
        a[tr][tc] = 2;

        vector<pair<int, int>> path;
        int cr = 0;
        int cc = 0;
        path.push_back({0, 0});
        while (cr < tr || cc < tc) {
            int coin = rnd.next(0, 1);
            if (cr < tr && (cc == tc || coin == 0)) cr++;
            else cc++;
            path.push_back({cr, cc});
        }

        shuffle(path.begin(), path.end());
        int ones_allowed = best_bfs;
        for (auto [pr, pc] : path) {
            if (pr == tr && pc == tc) continue;
            if (ones_allowed > 0) {
                a[pr][pc] = 1;
                ones_allowed--;
            } else {
                a[pr][pc] = 2;
            }
        }
    }
}

void make_subtask2(int n, int m, int k, const string& type, int extra, vector<vector<int>>& a) {
    if (type == "all_ones") {
        for (int r = 0; r < n; ++r)
            for (int c = 0; c < m; ++c)
                a[r][c] = 1;
    } else if (type == "all_twos") {
        for (int r = 0; r < n; ++r)
            for (int c = 0; c < m; ++c)
                a[r][c] = 2;
    } else if (type == "dr_corridor") {
        for (int r = 0; r < n; ++r)
            for (int c = 0; c < m; ++c)
                a[r][c] = 1;

        int tr = n - 1;
        int tc = m - 1;
        a[tr][tc] = 2;

        vector<pair<int, int>> path;
        int cr = 0;
        int cc = 0;
        path.push_back({0, 0});
        while (cr < tr || cc < tc) {
            int coin = rnd.next(0, 1);
            if (cr < tr && (cc == tc || coin == 0)) cr++;
            else cc++;
            path.push_back({cr, cc});
        }

        shuffle(path.begin(), path.end());
        int ones_budget = min((int)path.size() - 1, max(0, k + (extra % 3) - 1));
        for (auto [pr, pc] : path) {
            if (pr == tr && pc == tc) continue;
            if (ones_budget > 0) {
                a[pr][pc] = 1;
                ones_budget--;
            } else {
                a[pr][pc] = 2;
            }
        }
    } else if (type == "layers") {
        int target_dist = max(1, min(n + m - 2, k + (extra % 3) - 1));
        for (int r = 0; r < n; ++r)
            for (int c = 0; c < m; ++c)
                a[r][c] = (r + c >= target_dist) ? 2 : 1;
    } else {
        int prob_two = max(0, min(100, extra));
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                int roll = rnd.next(1, 100);
                a[r][c] = (roll <= prob_two) ? 2 : 1;
            }
        }
    }
    enforce_down_right_optimal(n, m, a);
}

void make_random(int n, int m, int min_a, int max_a, vector<vector<int>>& a) {
    for (int r = 0; r < n; ++r)
        for (int c = 0; c < m; ++c)
            a[r][c] = rnd.next(min_a, max_a);
}

void make_all_equal(int n, int m, int min_a, int max_a, int extra, vector<vector<int>>& a) {
    int val = min_a;
    if (extra == 2) val = max_a;
    else if (extra != 1) val = rnd.next(min_a, max_a);

    for (int r = 0; r < n; ++r)
        for (int c = 0; c < m; ++c)
            a[r][c] = val;
}

void make_bait_islands(int n, int m, int s, int min_a, int max_a, vector<vector<int>>& a) {
    int low_val = rnd.next(min_a, max(min_a, max_a / 3));
    int mid_val = rnd.next(low_val + 1, max(low_val + 1, (2 * max_a) / 3));
    int high_val = rnd.next(mid_val + 1, max_a);

    for (int r = 0; r < n; ++r)
        for (int c = 0; c < m; ++c)
            a[r][c] = rnd.next(min_a, low_val);

    int needed = s;
    for (int r = n - 1; r >= 0 && needed > 0; --r) {
        for (int c = m - 1; c >= 0 && needed > 0; --c) {
            a[r][c] = rnd.next(mid_val, high_val);
            needed--;
        }
    }

    int bait = min(s - 1, (n * m) / 3);
    for (int r = 0; r < n && bait > 0; ++r) {
        for (int c = 0; c < m && bait > 0; ++c) {
            a[r][c] = high_val;
            bait--;
        }
    }
}

void make_snake(int n, int m, int k, int s, int min_a, int max_a, vector<vector<int>>& a) {
    int wall_val = rnd.next(min_a, max(min_a, max_a / 4));
    int path_val = rnd.next(wall_val + 1, max_a);

    for (int r = 0; r < n; ++r)
        for (int c = 0; c < m; ++c)
            a[r][c] = rnd.next(min_a, wall_val);

    vector<pair<int, int>> snake;
    for (int r = 0; r < n; r += 2) {
        if ((r / 2) % 2 == 0) {
            for (int c = 0; c < m; ++c) snake.push_back({r, c});
            if (r + 1 < n) snake.push_back({r + 1, m - 1});
        } else {
            for (int c = m - 1; c >= 0; --c) snake.push_back({r, c});
            if (r + 1 < n) snake.push_back({r + 1, 0});
        }
    }

    for (auto [r, c] : snake)
        a[r][c] = rnd.next(path_val, max_a);

    int safe_tail = min((int)snake.size(), s);
    int road_space = (int)snake.size() - safe_tail;
    int unsafe_budget = max(0, k - 1);

    if (road_space > 0) {
        int limit = min(unsafe_budget, road_space);
        for (int i = 0; i < limit; ++i) {
            int idx = rnd.next(0, road_space - 1);
            auto [r, c] = snake[idx];
            a[r][c] = rnd.next(min_a, wall_val);
        }
    }
}

void make_spiral(int n, int m, int k, int s, int min_a, int max_a, vector<vector<int>>& a) {
    int wall_val = rnd.next(min_a, max(min_a, max_a / 4));
    int path_val = rnd.next(wall_val + 1, max_a);

    for (int r = 0; r < n; ++r)
        for (int c = 0; c < m; ++c)
            a[r][c] = rnd.next(min_a, wall_val);

    vector<pair<int, int>> spiral;
    int top = 0;
    int bottom = n - 1;
    int left = 0;
    int right = m - 1;

    while (top <= bottom && left <= right) {
        for (int c = left; c <= right; ++c) spiral.push_back({top, c});
        top += 2;
        if (top - 1 > bottom) break;

        for (int r = top - 1; r <= bottom; ++r) spiral.push_back({r, right});
        right -= 2;
        if (left > right + 1) break;

        if (top - 1 <= bottom) {
            for (int c = right + 1; c >= left; --c) spiral.push_back({bottom, c});
            bottom -= 2;
        }
        if (top - 1 > bottom) break;

        if (left <= right + 1) {
            for (int r = bottom + 1; r >= top; --r) spiral.push_back({r, left});
            left += 2;
        }
    }

    for (auto [pr, pc] : spiral)
        a[pr][pc] = rnd.next(path_val, max_a);

    int safe_tail = min((int)spiral.size(), s);
    int road_space = (int)spiral.size() - safe_tail;
    if (road_space > 0) {
        int limit = min(k, road_space);
        for (int i = 0; i < limit; ++i) {
            int idx = rnd.next(0, road_space - 1);
            auto [pr, pc] = spiral[idx];
            a[pr][pc] = rnd.next(min_a, wall_val);
        }
    }
}

void make_checkerboard(int n, int m, int min_a, int max_a, vector<vector<int>>& a) {
    int low_val = rnd.next(min_a, max(min_a, max_a / 2));
    int high_val = rnd.next(low_val + 1, max_a);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if ((r + c) % 2 == 0) a[r][c] = rnd.next(high_val, max_a);
            else a[r][c] = rnd.next(min_a, low_val);
        }
    }
}

void make_distinct(int n, int m, int min_a, int max_a, vector<vector<int>>& a) {
    vector<int> vals(n * m);
    for (int i = 0; i < n * m; ++i)
        vals[i] = max(min_a, max_a - i);

    shuffle(vals.begin(), vals.end());
    for (int r = 0; r < n; ++r)
        for (int c = 0; c < m; ++c)
            a[r][c] = vals[r * m + c];
}

void make_start_trap(int n, int m, int k, int min_a, int max_a, int extra, vector<vector<int>>& a) {
    int low_val = rnd.next(min_a, max(min_a, max_a / 3));
    int high_val = rnd.next(low_val + 1, max_a);

    for (int r = 0; r < n; ++r)
        for (int c = 0; c < m; ++c)
            a[r][c] = rnd.next(high_val, max_a);

    int trap_radius = max(1, min(n + m - 2, k + (extra % 3) - 1));
    for (int r = 0; r < n; ++r)
        for (int c = 0; c < m; ++c)
            if (r + c < trap_radius)
                a[r][c] = rnd.next(min_a, low_val);
}

void make_layers(int n, int m, int min_a, int max_a, vector<vector<int>>& a) {
    int mid = max(min_a, max_a / 2);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if ((r + c) % 2 == 0) a[r][c] = rnd.next(mid, max_a);
            else a[r][c] = rnd.next(min_a, mid);
        }
    }
}

void make_comb(int n, int m, int s, int min_a, int max_a, vector<vector<int>>& a) {
    int low_val = rnd.next(min_a, max(min_a, max_a / 3));
    int high_val = rnd.next(low_val + 1, max_a);

    for (int r = 0; r < n; ++r)
        for (int c = 0; c < m; ++c)
            a[r][c] = rnd.next(min_a, low_val);

    int limit = min(n, max(1, s - 1));
    for (int c = 0; c < m; c += 2)
        for (int r = 0; r < limit; ++r)
            a[r][c] = rnd.next(high_val, max_a);

    int needed = s;
    for (int r = n - 1; r >= 0 && needed > 0; --r) {
        for (int c = m - 1; c >= 0 && needed > 0; --c) {
            a[r][c] = high_val;
            needed--;
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int subtask = atoi(argv[1]);
    string type = argv[2];
    int n = atoi(argv[3]);
    int m = atoi(argv[4]);
    int k = atoi(argv[5]);
    int s = atoi(argv[6]);
    int extra = (argc > 7) ? atoi(argv[7]) : 50;

    int min_a = 1;
    int max_a = 1000000000;

    if (subtask == 1) {
        n = min(n, 40);
        m = min(m, 40);
        max_a = 50;
    } else if (subtask == 2) {
        min_a = 1;
        max_a = 2;
        s = 1;
    } else if (subtask == 3) {
        k = n * m;
    }

    if (k < 0) k = rnd.next(0, n * m);
    if (s < 0) s = rnd.next(1, n * m);
    k = min(k, n * m);
    s = max(1, min(s, n * m));

    vector<vector<int>> a(n, vector<int>(m, min_a));

    if (subtask == 2) {
        make_subtask2(n, m, k, type, extra, a);
    } else if (type == "random") {
        make_random(n, m, min_a, max_a, a);
    } else if (type == "all_equal") {
        make_all_equal(n, m, min_a, max_a, extra, a);
    } else if (type == "bait_islands") {
        make_bait_islands(n, m, s, min_a, max_a, a);
    } else if (type == "snake") {
        make_snake(n, m, k, s, min_a, max_a, a);
    } else if (type == "spiral") {
        make_spiral(n, m, k, s, min_a, max_a, a);
    } else if (type == "checkerboard") {
        make_checkerboard(n, m, min_a, max_a, a);
    } else if (type == "distinct") {
        make_distinct(n, m, min_a, max_a, a);
    } else if (type == "start_trap") {
        make_start_trap(n, m, k, min_a, max_a, extra, a);
    } else if (type == "layers") {
        make_layers(n, m, min_a, max_a, a);
    } else if (type == "comb") {
        make_comb(n, m, s, min_a, max_a, a);
    }

    println(n, m, k, s);
    for (int r = 0; r < n; ++r) {
        println(a[r]);
    }

    return 0;
}