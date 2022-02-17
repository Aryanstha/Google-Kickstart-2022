#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll t, n, i, j, ans, si;
    cin >> t;
    for (j = 1; j <= t; j++)
    {
        cin >> n;
        ll a[n];
        ans = 0;
        si = 0;
        priority_queue<ll, vector<ll>, greater<ll>> q;
        for (i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        cout << "Case #" << j << ": ";
        for (i = 0; i < n; i++)
        {
            while (q.empty() == false && q.top() <= ans)
            {
                q.pop();
                si--;
            }
            if (a[i] > ans)
            {
                q.push(a[i]);
                si++;
            }
            if (si == ans + 1)
            {
                ans++;
            }
            cout << ans << " ";
        }
        cout << "\n";
    }
    return 0;
}