#include <bits/stdc++.h>
using namespace std;

int n;
int a[1000];
const int INF = 1e5;
const int MAX_TX = 2;

struct Point {
  int idx;
  int val;
};

struct Transaction {
  Point buy,sell;

  int getVal() {
    return sell.val - buy.val;
  }
};

struct Range {
  Point left,right;
  deque<Transaction> transactions;
};

bool calculated[1000][1000];
Range ranges[1000][1000];

deque<Transaction> getTwo(deque<Transaction> &tx) {
  sort(tx.begin(), tx.end(), [](const Transaction &a, const Transaction &b) {
    int diffA = a.sell.val - a.buy.val;
    int diffB = b.sell.val - b.buy.val;
    return diffA < diffB;
  });

  while (tx.size() > 2) {
    tx.pop_back();
  }

  return tx;
}
Range merge (Range r, Point p) {

  int y = r.right.val;
  int z = p.val;
  // (h,d)
  if (r.transactions.empty()) {
    if (y < z) {
      r.transactions.push_back({r.right, p});
    }
  } else {
    // (h,d) * (u,h,d)
    int x = r.transactions.back().sell.val;
    if (x == y && y < z) {
      // h * u
      // correct
      r.transactions.back().sell = p;

      // r.transactions.push_back({r.right,p});

    } else if (x > y && y < z) {
      // d * u
      r.transactions.push_back({r.right,p});
    }
    // h * h
    // h * d
    // d * h
    // d * d
    // => shift right
  }

  r.right = p;
  return r;
}

struct DP {
  Point lowest, highest;
  int val;
};

DP dp[1000][1000];

int main () {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    if (i == 0) {
      ranges[i][i] = {
        {i,a[i]},{i,a[i]},
        {}
      };
    } else {
      Point p = {i,a[i]};
      ranges[0][i] = merge(ranges[0][i-1], p);
    }
  }

  // Preprocess to get transaction of each range
  for (int i = 0; i < n; ++i) {
    for (int j = i; j < n; ++j) {
      if (j == i) {
        ranges[i][i] = {
          {i,a[i]},{i,a[i]},
          {}
        };
      } else {
        Point p = {j,a[j]};
        ranges[i][j] = merge(ranges[i][j-1], p);
      }
    }
  }

  auto tx = ranges[0][n-1].transactions;


  cout << "There are " << tx.size() << " transactions: " <<endl;
  
  for (int i = 0; i < tx.size(); ++i) {
    cout << "Buy at (" << tx[i].buy.idx << "," << tx[i].buy.val<< ")";
    cout << " Sell at (" << tx[i].sell.idx << "," << tx[i].sell.val << ")"<< endl;
  }

  int txNum = tx.size();
  if (txNum == 1) {
    cout << " 1" << endl;
    cout << tx[0].getVal() << endl;
    return 0;
  } else if (txNum == 0) {
    cout << 0;
    return 0;
  }
  for (int i = 0; i < txNum; ++i) {
    dp[i][i] = {
      tx[i].buy,tx[i].sell,
      tx[i].getVal()
    };
  }

  for (int i = 0; i < txNum; ++ i) {
    for (int j = i; j < txNum; ++j) {
      if (i == j) continue;
      int candidateVal = dp[j][j].highest.val - dp[i][j-1].lowest.val;
        DP bigger = dp[i][j-1].val >= dp[j][j].val ? dp[i][j-1] : dp[j][j];
      if (candidateVal >= 0) {
        DP candidate = {
          dp[i][j-1].lowest, dp[j][j].highest,
          candidateVal
        };
        dp[i][j] = bigger.val >= candidateVal ? bigger : candidate;
      } else {
        dp[i][j] = bigger;
      }
    }
  }

  int sol = -INF;
  for (int k = 0; k < txNum-1; ++k) {
    int candidate = dp[0][k].val + dp[k+1][txNum-1].val;
    if (candidate > sol) {
      sol = candidate;
    }
  }
  
  cout << sol;

  return 0;
}