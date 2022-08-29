#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>
using namespace std;

// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template<class Fun> class y_combinator_result {
    Fun fun_;
public:
    template<class T> explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
    template<class ...Args> decltype(auto) operator()(Args &&...args) { return fun_(std::ref(*this), std::forward<Args>(args)...); }
};
template<class Fun> decltype(auto) y_combinator(Fun &&fun) { return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun)); }


template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#ifdef NEAL_DEBUG
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

int64_t floor_div(int64_t a, int64_t b) {
    return a / b - ((a ^ b) < 0 && a % b != 0);
}


const int64_t INF64 = int64_t(2e18) + 5;

// North, East, West, South
const int DIRS = 4;
const int DR[] = {-1, 0, 0, +1};
const int DC[] = {0, +1, -1, 0};

void run_case(int test_case) {
    int N, P, M, AR, AC;
    cin >> N >> P >> M >> AR >> AC;
    AR--; AC--;

    array<char, DIRS> op;
    array<int, DIRS> K;

    for (int dir = 0; dir < DIRS; dir++)
        cin >> op[dir] >> K[dir];

    auto apply_op = [&](int64_t value, int dir) -> int64_t {
        if (op[dir] == '+')
            return value + K[dir];
        else if (op[dir] == '-')
            return value - K[dir];
        else if (op[dir] == '*')
            return value * K[dir];
        else if (op[dir] == '/')
            return floor_div(value, K[dir]);

        assert(false);
    };

    vector<int> X(P), Y(P), C(P);
    vector<vector<int>> square_mask(N, vector<int>(N, 0));
    vector<vector<int>> square_add(N, vector<int>(N, 0));

    for (int i = 0; i < P; i++) {
        cin >> X[i] >> Y[i] >> C[i];
        X[i]--; Y[i]--;
        square_mask[X[i]][Y[i]] |= 1 << i;
        square_add[X[i]][Y[i]] += C[i];
    }

    vector<vector<vector<int64_t>>> dp(N, vector<vector<int64_t>>(N, vector<int64_t>(1 << P, -INF64)));
    dp[AR][AC][0] = 0;

    for (int m = 0; m < M; m++) {
        vector<vector<vector<int64_t>>> ndp(N, vector<vector<int64_t>>(N, vector<int64_t>(1 << P, -INF64)));

        for (int r = 0; r < N; r++)
            for (int c = 0; c < N; c++)
                for (int mask = 0; mask < 1 << P; mask++) {
                    if (dp[r][c][mask] <= -INF64)
                        continue;

                    ndp[r][c][mask] = max(ndp[r][c][mask], dp[r][c][mask]);

                    for (int dir = 0; dir < DIRS; dir++) {
                        int nr = r + DR[dir];
                        int nc = c + DC[dir];

                        if (min(nr, nc) < 0 || max(nr, nc) >= N)
                            continue;

                        ndp[nr][nc][mask] = max(ndp[nr][nc][mask], apply_op(dp[r][c][mask], dir));

                        int nmask = mask | square_mask[nr][nc];
                        int nadd = (mask & square_mask[nr][nc]) == 0 ? square_add[nr][nc] : 0;
                        ndp[nr][nc][nmask] = max(ndp[nr][nc][nmask], apply_op(dp[r][c][mask], dir) + nadd);
                    }
                }

        dp.swap(ndp);
    }

    int64_t best = -INF64;

    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            best = max(best, dp[r][c][(1 << P) - 1]);

    cout << "Case #" << test_case << ": ";

    if (best <= -INF64)
        cout << "IMPOSSIBLE" << '\n';
    else
        cout << best << '\n';
}

int main() {
    int tests;
    cin >> tests;

    for (int tc = 1; tc <= tests; tc++) {
        run_case(tc);
        cout << flush;
    }
}
