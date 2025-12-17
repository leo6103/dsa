#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n;
    const int INF = 1e5;
    const int MAX_TX = 2;

    struct Point {
        int idx;
        int val;
    };

    struct Transaction {
        Point buy, sell;
        int getVal() const { return sell.val - buy.val; }
    };

    struct Range {
        Point left, right;
        deque<Transaction> transactions;
    };

    struct DP {
        Point lowest, highest;
        int val;
    };

    static bool calculated[105][105];
    static Range ranges[105][105];
    static DP dp[105][105];

    // Merge logic — passed by reference
    Range merge(Range &r, Point p) {
        int y = r.right.val;
        int z = p.val;

        if (r.transactions.empty()) {
            if (y < z) r.transactions.push_back({r.right, p});
        } else {
            int x = r.transactions.back().sell.val;
            if (x == y && y < z) {
                r.transactions.back().sell = p; // h * u
            } else if (x > y && y < z) {
                r.transactions.push_back({r.right, p}); // d * u
            }
        }

        r.right = p;

        // limit size
        while (r.transactions.size() > MAX_TX) r.transactions.pop_front();
        return r;
    }

    int maxProfit(vector<int> &prices) {
        n = prices.size();
        auto a = prices;

        // ✅ only one initialization loop
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                if (j == i) {
                    ranges[i][i] = {{i, a[i]}, {i, a[i]}, {}};
                } else {
                    Point p = {j, a[j]};
                    ranges[i][j] = merge(ranges[i][j - 1], p);
                }
            }
        }

        auto tx = ranges[0][n - 1].transactions;
        int txNum = tx.size();
        if (txNum == 0) return 0;
        if (txNum == 1) return tx[0].getVal();

        // dp init
        for (int i = 0; i < txNum; ++i) {
            dp[i][i] = {tx[i].buy, tx[i].sell, tx[i].getVal()};
        }

        // dp transitions
        for (int i = 0; i < txNum; ++i) {
            for (int j = i; j < txNum; ++j) {
                if (i == j) continue;
                int candidateVal = dp[j][j].highest.val - dp[i][j - 1].lowest.val;
                DP bigger = dp[i][j - 1].val >= dp[j][j].val ? dp[i][j - 1] : dp[j][j];
                if (candidateVal >= 0) {
                    DP candidate = {dp[i][j - 1].lowest, dp[j][j].highest, candidateVal};
                    dp[i][j] = bigger.val >= candidateVal ? bigger : candidate;
                } else {
                    dp[i][j] = bigger;
                }
            }
        }

        // combine two transactions
        int sol = -INF;
        for (int k = 0; k < txNum - 1; ++k) {
            int candidate = dp[0][k].val + dp[k + 1][txNum - 1].val;
            sol = max(sol, candidate);
        }

        return sol;
    }
};

// static members
bool Solution::calculated[105][105];
Solution::Range Solution::ranges[105][105];
Solution::DP Solution::dp[105][105];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<int> prices(n);
    for (int i = 0; i < n; ++i) cin >> prices[i];

    Solution sol;
    cout << sol.maxProfit(prices) << "\n";
    return 0;
}
