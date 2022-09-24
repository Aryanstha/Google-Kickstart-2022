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
  ll d, x;
  int n;
  cin >> d >> n >> x;
  using T = tuple<ll, int, int>;
  priority_queue<T> evs;
  rep(_, n) {
    int q, v;
    ll l;
    cin >> q >> l >> v;
    if (l < d) {
      evs.emplace(d - 1 - l, q, v);
    }
  }
  evs.emplace(-1, 0, 0);
  priority_queue<P> stock;
  ll time = 0;
  ll ans = 0;
  while(!evs.empty()) {
    ll ntime = get<0>(evs.top());
    ll rest = (time - ntime) * x;
    while(!stock.empty() && rest > 0) {
      auto [v, q] = stock.top(); stock.pop();
      int cnt = min<ll>(q, rest);
      ans += (ll)cnt * v;
      q -= cnt;
      rest -= cnt;
      if (q) stock.emplace(v, q);
    }
    while(!evs.empty() && get<0>(evs.top()) == ntime) {
      auto [_, q, v] = evs.top(); evs.pop();
      stock.emplace(v, q);
    }
    time = ntime;
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