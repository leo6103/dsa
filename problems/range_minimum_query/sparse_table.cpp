#include <bits/stdc++.h>
using namespace std;

#define fast_io ios::sync_with_stdio(false) cin.tie(nullptr);
const int MAX_N = 10000;

int n,q;
int a[100001];
int query[MAX_N][MAX_N];

int main() {
  cin >> n;
  cin >> q;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  
  // preprocess
  int maxk = floor(log2(n));
  // store every range of 2^k value
  for (int k = 0; k <= maxk; ++k) {
    for (int i = 0; i <= n - 1; ++ i) {
      if (k == 0) {
        query[i][k] = a[i];
      } else if (i + (int)pow(2,k) - 1 <= n - 1){
        query[i][k] = min(query[i][k-1], query[i + (int)pow(2,k-1)][k-1]);
      }
      // cout << "query i, k: " << i << ", " << k << "=" << query[i][k] << endl; 
    }
  }

  // cout << "**" << endl;
  // query
  for (int i = 0; i < q; ++i) {
    int l1,l2; cin >> l1 >> l2;
    int qk = floor(log2(l2 - l1 + 1 - 1));
    cout << min(query[l1][qk], query[l2 - (int)pow(2,qk) + 1 - 1][qk]) << endl;
  }

  return 0;
}