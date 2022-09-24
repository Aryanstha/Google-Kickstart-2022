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
  int n, q;
  cin >> n >> q;
  VVI to(n);
  rep(_, n - 1) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    to[u].emplace_back(v);
    to[v].emplace_back(u);
  }
  VI d(n);
  auto dfs = [&](auto self, int u, int p, int du) -> void {
    d[du]++;
    for(int v: to[u]) if (v != p) {
      self(self, v, u, du + 1);
    }
  };
  dfs(dfs, 0, -1, 0);
  int tmp;
  rep(_, q) cin >> tmp;
  int ans = 0;
  for(int i = 0; i < n; i++) {
    if (d[i] <= q) {
      ans += d[i];
      q -= d[i];
    } else {
      break;
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