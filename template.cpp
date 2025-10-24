#include <bits/stdc++.h>
using namespace std;

#define fast_io ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(v) (v).begin(), (v).end()
#define rep(i,a,b) for(int i=(a); i<(b); ++i)
using ll = long long;
using vi = vector<int>;

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  rep(i,0,n) cin >> a[i];

  sort(all(a));
  for (int x : a) cout << x << " ";
  cout << "\n";
}

int main() {
    fast_io;
    int t = 1;
    // cin >> t; // uncomment if multiple test cases
    while (t--) solve();
}
