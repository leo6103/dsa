#include <bits/stdc++.h>
using namespace std;

#define fast_io ios::sync_with_stdio(false); cin.tie(nullptr);
const int MAX_N = 10e5;

int n,k;
int a[10000];

int main() {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  cin >> k;
  for (int i = 0; i < k; ++i) {
    int l1,l2; cin >> l1 >> l2;
    int num = a[l1];
    for (int j = l1; j <= l2; ++j) {
      if (a[j] < a[l1]) num = a[j];
    }
    cout << num << endl;
  }

  return 0;
}