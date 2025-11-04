#include <bits/stdc++.h>
using namespace std;

// input
int n;
int a[1000];

//
int dp[1000][1000];
int b1[1000][1000],s1[1000][1000],b2[1000][1000],s2[1000][1000], type[1000][1000], lowest[1000][1000], highest[1000][1000];

int getDP(int i, int j) {
  if (dp[i][j] != -1) return dp[i][j];
  // 1
  if (i == j) {
    type[i][j] = 0;
    lowest[i][j] = a[i];
    highest[i][j] = a[i];
    dp[i][j] = 0;
    return 0;
  }
  // 2
  if (j - i == 1) {
    if (a[i] >= a[j]) {
      type[i][j] = 1;
      lowest[i][j] = a[j];
      highest[i][j] = a[i];
      dp[i][j] = 0;

    } else {
      type[i][j] = 2;
      b1[i][j] = a[i];
      s1[i][j] = a[j];
      lowest[i][j] = a[i];
      highest[i][j] = a[j];
      dp[i][j] = s1 - b1;
    }
  }
  // >= 3
  int type_opt, val_opt, b1_opt, s1_opt, b2_opt, s2_opt, lowest_opt, highest_opt;
  for (int k = i; k < j; ++k) {
    // join (i,k) and (k,j)
    dp[i][k] = getDP(i,k);
    dp[k][j] = getDP(k,j);
    
    int type_can, val_can, b1_can, s1_can, b2_can, s2_can, lowest_can, highest_can;
    
    if (type[i][k] == 0 && type[k+1][j] == 1) {
      if (a[i] >= a[k+1]) {
        type_can = 1;
        b1_can = -1;
        s1_can = -1;
        b2_can = -1;
        s2_can = -1;
        lowest_can = lowest[k+1][j];
        highest_can = a[i];
        val_can = 0;
      } else {
        type_can = 2;
        b1_can = a[i];
        s1_can = a[k+1];
        b2_can = -1;
        s2_can = -1;
        lowest_can = min(a[i], lowest[k+1][j]);
        highest_can = highest[k+1][j];
        val_can = s1_can - b1_can;
      }
    } else if (type[i][k] == 1 && type[k+1][j] == 0) {
      if (a[j] <= a[k]) {
        type_can = 1;
        b1_can = -1;
        s1_can = -1;
        b2_can = -1;
        s2_can = -1;
        lowest_can = a[j];
        highest_can = a[i];
        val_can = 0;
      } else {
        type_can = 2;
        b1_can = a[k];
        s1_can = a[j];
        b2_can = -1;
        s2_can = -1;
        lowest_can = a[k];
        highest_can = max(a[i], a[j]);
        val_can = s1_can - b1_can;
      }
    }
    if (type[i][k] == 0 && type[k+1][j] == 2) {
      type_can = 2;
      b1_can = min(a[i], b1[k+1][j]);
      s1_can = s1[k+1][j];
      b2_can = -1;
      s2_can = -1;
      lowest_can = min(a[i], lowest[k+1][j]);
      highest_can = max(a[i], highest[k+1][j]);
      val_can = s1_can - b1_can;
    } else if (type[i][k] == 2 && type[k+1][j] == 0) {
      type_can = 2;
      b1_can = b1[i][k];
      s1_can = max(s1[i][k], a[j]);
      b2_can = -1;
      s2_can = -1;
      lowest_can = min(lowest[i][k], a[j]); 
      highest_can = max(highest[i][k], a[j]);
      val_can = s1_can - b1_can;
    } else if (type[i][k] == 0 && type[k+1][j] == 3) {
      type_can = 3;
      b1_can = min(a[i], b1[k+1][j]);
      s1_can = s1[k+1][j];
      b2_can = b2[k+1][j];
      s2_can = s2[k+1][k+1];
      lowest_can = min(a[i], lowest[k+1][j]);
      highest_can = max(a[i], highest[k+1][j]);
      val_can = s1_can - b1_can + s2_can - b2_can;
    } else if (type[i][k] == 3 && type[k+1][j] == 0) {
      type_can = 3;
      b1_can = b1[i][k];
      s1_can = s1[i][k];
      b2_can = b2[i][k];
      s2_can = max(s2[i][k], a[j]);
      lowest_can = min(lowest[i][k], a[j]); 
      highest_can = max(highest[i][k], a[j]);
      val_can = s1_can - b1_can + s2_can - b2_can;
    } else if (type[i][k] == 1 && type[k+1][j] == 2) {
      type_can = 2;
      b1_can = min(a[k], b1[k+1][j]);
      s1_can = s1[k+1][j];
      b2_can = -1;
      s2_can = -1;
      lowest_can = min(a[k], lowest[k+1][j]);
      highest_can = max(a[i], highest[k+1][j]);
      val_can = s1_can - b1_can;
    } else if (type[i][k] == 2 && type[k+1][j] == 1) {
      type_can = 2;
      b1_can = b1[i][k];
      s1_can = max(s1[i][k], a[j]);
      b2_can = -1;
      s2_can = -1;
      lowest_can = min(lowest[i][k], a[j]);
      highest_can = max(highest[i][k], a[k+1]);
      val_can = s1_can - b1_can;
    } else if (type[i][k] == 1 && type[k+1][j] == 3) {
      type_can = 3;
      b1_can = min(a[k], b1[k+1][j]);
      s1_can = s1[k+1][j];
      b2_can = b2[k+1][j];
      s2_can = s2[k+1][j];
      lowest_can = min(a[k], lowest[k+1][j]);
      highest_can = max(a[i], highest[k+1][j]);
      val_can = s1_can - b1_can + s2_can - b2_can;
    } else if (type[i][k] == 3 && type[k+1][j] == 1) {
      type_can = 3;
      b1_can = b1[i][k];
      s1_can = s1[i][k];
      b2_can = b2[k+1][j];
      s2_can = max(s2[i][k], a[j]);
      lowest_can = min(lowest[i][k], a[j]);
      highest_can = max(highest[i][k], a[k+1]);
      val_can = s1_can - b1_can + s2_can - b2_can;
    } else if (type[i][k] == 2 && type[k+1][j] == 3) {
      type_can = 3;
      highest_can = max(highest[i][k], highest[k+1][j]);
      lowest_can = min(lowest[i][k], lowest[k+1][j]);
      if (b1[k+i][j] >= s1[i][k]) {
        // joining
        b1_can = s1[i][k];
        s1_can = s1[k+1][j];
        b2_can = b2[k+1][j];
        s2_can = s2[k+1][j];
      } else {
        // choose 2 in 3
        pair<int,int> a,b,c;
        a = {b1[i][k], s1[k+1][j]};
        b = {b1[k+1][j], s1[k+1][j]};
      }
    } else if (type[i][k] == 3 && type[k+1][j] == 2) {
    } else if (type[i][k] == 0 && type[k+1][j] == 0) {
    } else if (type[i][k] == 1 && type[k+1][j] == 1) {
    } else if (type[i][k] == 2 && type[k+1][j] == 2) {

    } else if (type[i][k] == 3 && type[k+1][j] == 3) {
    }
  }
}

int main () {
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      dp[i][j] = -1;

      type[i][j] = -1;
      b1[i][j] = -1;
      s1[i][j] = -1;
      b2[i][j] = -1;
      s2[i][j] = -1;
    }
  }

  cout << getDP(1,n);
  return 0;
}