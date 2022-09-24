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
  struct S {
    string c;
    int d;
    int u;
  };
  int n;
  cin >> n;
  vector<S> a1(n);
  for(auto& [c, d, u]: a1) {
    cin >> c >> d >> u;
  }
  auto a2 = a1;
  sort(all(a1), [&](const S& x, const S& y) {
    return x.c < y.c || (x.c == y.c && x.u < y.u);
  });
  sort(all(a2), [&](const S& x, const S& y) {
    return x.d < y.d || (x.d == y.d && x.u < y.u);
  });
  int ans = 0;
  rep(i, n) ans += a1[i].u == a2[i].u;
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