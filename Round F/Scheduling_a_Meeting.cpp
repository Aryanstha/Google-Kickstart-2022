#include<bits/stdc++.h>
namespace {
using namespace std;
#define rep(i,n) for(int i = 0; i < (int)(n); i++)
#define rrep(i,n) for(int i = (int)(n) - 1; i >= 0; i--)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
template<class T> bool chmax(T& a, const T& b) { if (a < b) { a = b; return true; } else return false; }
template<class T> bool chmin(T& a, const T& b) { if (b < a) { a = b; return true; } else return false; }
using ll = long long;
using P = pair<int,int>;
using VI = vector<int>;
using VVI = vector<VI>;
using VL = vector<ll>;
using VVL = vector<VL>;

void solve() {
  int n, k, x, d;
  cin >> n >> k >> x >> d;
  VI cost(n);
  int m;
  cin >> m;
  VVI rems(d + 1), adds(d + 1);
  rep(_, m) {
    int p, l, r;
    cin >> p >> l >> r;
    p--;
    if (l < x) {
      cost[p]++;
    } else {
      adds[l-x].emplace_back(p);
    }
    rems[r].emplace_back(p);
  }
  multiset<int, greater<int>> st0(all(cost));
  multiset<int> st1;
  int sm0 = accumulate(all(cost), 0), sm1 = 0;
  auto balance = [&] {
    while(!st0.empty() && !st1.empty()) {
      auto it0 = st0.begin();
      auto it1 = st1.begin();
      if (*it0 <= *it1) break;
      int v0 = *it0, v1 = *it1;
      st0.erase(it0);
      st1.erase(it1);
      st0.emplace(v1);
      st1.emplace(v0);
      sm0 += v1 - v0;
      sm1 += v0 - v1;
    }
    int sz0 = st0.size();
    if (sz0 > k) {
      rrep(_, sz0 - k) {
        auto it = st0.begin();
        int v = *it;
        st0.erase(it);
        sm0 -= v;
        st1.emplace(v);
        sm1 += v;
      }
    } else if (sz0 < k) {
      rrep(_, k - sz0) {
        auto it = st1.begin();
        int v = *it;
        st1.erase(it);
        sm1 -= v;
        st0.emplace(v);
        sm0 += v;
      }
    }
  };
  balance();
  int ans = m;
  for(int i = 0; i <= d - x; i++) {
    for(int p: rems[i]) {
      if (auto it = st0.find(cost[p]); it != st0.end()) {
        st0.erase(it);
        st0.emplace(--cost[p]);
        sm0--;
      } else {
        auto it2 = st1.find(cost[p]);
        st1.erase(it2);
        st1.emplace(--cost[p]);
        sm1--;
      }
    }
    balance();
    chmin(ans, sm0);
    for(int p: adds[i]) {
      if (auto it = st0.find(cost[p]); it != st0.end()) {
        st0.erase(it);
        st0.emplace(++cost[p]);
        sm0++;
      } else {
        auto it2 = st1.find(cost[p]);
        st1.erase(it2);
        st1.emplace(++cost[p]);
        sm1++;
      }
    }
  }
  cout << ans << '\n';
}

} int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int tt;
	cin >> tt;
	rep(i, tt) {
		cout << "Case #" << i + 1 << ": ";
		solve();
	}
}