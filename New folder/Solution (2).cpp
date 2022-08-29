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

// Computes the radius of the longest palindrome centered at each element in O(n) total.
// Actual palindrome length is `2 * radius[i] + 1`.
template<typename T_string>
vector<int> odd_manacher(const T_string &pattern) {
    int n = int(pattern.size());
    vector<int> radius(n, 0);
    int loc = 0;

    for (int i = 1; i < n; i++) {
        if (i <= loc + radius[loc])
            radius[i] = min(radius[loc - (i - loc)], loc + radius[loc] - i);

        while (i - radius[i] > 0 && i + radius[i] < n - 1 && pattern[i - radius[i] - 1] == pattern[i + radius[i] + 1])
            radius[i]++;

        // Find the location with the furthest-reaching umbrella.
        if (i + radius[i] > loc + radius[loc])
            loc = i;
    }

    return radius;
}

// Returns a vector `lengths` of size `2 * n + 1` where `lengths[i]` indicates a palindrome starting at
// `(i - lengths[i]) / 2` and ending at `(i + lengths[i]) / 2` (exact division).
template<typename T_string>
vector<int> combined_manacher(const T_string &pattern) {
    int n = int(pattern.size());
    T_string extended(2 * n + 1, 0);

    for (int i = 0; i < n; i++)
        extended[2 * i + 1] = pattern[i];

    return odd_manacher(extended);
}

// Returns whether the substring represented by `[start, end)` is a palindrome using the output of `combined_manacher`.
bool is_palindrome(const vector<int> &lengths, int start, int end) {
    return lengths[start + end] >= end - start;
}


void run_case(int test_case) {
    int N;
    string P;
    cin >> N >> P;
    vector<int> lengths = combined_manacher(P);
    cout << "Case #" << test_case << ": ";

    for (int add = 1; add <= N; add++)
        if (is_palindrome(lengths, 0, add) && is_palindrome(lengths, add, N)) {
            cout << P.substr(0, add) << '\n';
            return;
        }
}

int main() {
    int tests;
    cin >> tests;

    for (int tc = 1; tc <= tests; tc++) {
        run_case(tc);
        cout << flush;
    }
}
