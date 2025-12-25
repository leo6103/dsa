// Rotting Oranges — scaffold only (no implementation)
#include <bits/stdc++.h>
using namespace std;

struct Point {
    int row;
    int col;
    int t;
};

class Solution {
public:

    int orangesRotting(vector<vector<int>> &grid) {
        int m = grid.size();
        int n = grid[0].size();

        int totalFresh = 0;
        int totalRotting = 0;
        int totalEmpty = 0;

        vector<Point> rottingSources;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0) {
                    totalEmpty ++;
                } else if (grid[i][j] == 1) {
                    totalFresh ++;
                } else if (grid[i][j] == 2) {
                    totalRotting ++;
                    Point rottingPoint = {i,j,0};
                    rottingSources.push_back(rottingPoint);
                }
            }
        }

        // BFS
        queue<Point> q;

        for (int p = 0; p < totalRotting; ++p) {
            // bfs
            q.push(rottingSources[p]);  
        }

        if (totalFresh == 0) return 0;

        int minT = 0;
        while (!q.empty()) {
            auto p = q.front();
            q.pop();
            // Check for neighbors

            // Up (row - 1)
            if (p.row > 0) {
                if (grid[p.row - 1][p.col] == 1) {
                    grid[p.row - 1][p.col] = 2;
                    totalFresh --;
                    totalRotting ++;
                    q.push(Point{p.row - 1, p.col, p.t + 1});
                    if (totalFresh == 0) return p.t + 1;
                }
            }

            // Down (row + 1)
            if (p.row < m - 1) {
                if (grid[p.row + 1][p.col] == 1) {
                    grid[p.row + 1][p.col] = 2;
                    totalFresh --;
                    totalRotting ++;
                    q.push(Point{p.row + 1, p.col, p.t + 1});
                    if (totalFresh == 0) return p.t + 1;
                }
            }

            // Left (col - 1)
            if (p.col > 0) {
                if (grid[p.row][p.col - 1] == 1) {
                    grid[p.row][p.col - 1] = 2;
                    totalFresh --;
                    totalRotting ++;
                    q.push(Point{p.row, p.col - 1, p.t + 1});
                    if (totalFresh == 0) return p.t + 1;
                }
            }

            // Right (col + 1)
            if (p.col < n - 1) {
                if (grid[p.row][p.col + 1] == 1) {
                    grid[p.row][p.col + 1] = 2;
                    totalFresh --;
                    totalRotting ++;
                    q.push(Point{p.row, p.col + 1, p.t + 1});
                    if (totalFresh == 0) return p.t + 1;
                }
            }


        }
        if (totalFresh != 0) return -1;

        return 0;
    }
};

// Helper to parse a grid in the form [[2,1,1],[1,1,0],[0,1,1]]
static vector<vector<int>> parseGrid(const string &line) {
    vector<vector<int>> grid;
    vector<int> row;
    string cur;
    bool inNumber = false;

    auto flushNumber = [&](void) {
        if (!cur.empty()) {
            row.push_back(stoi(cur));
            cur.clear();
            inNumber = false;
        }
    };

    for (char c : line) {
        if ((c >= '0' && c <= '9') || c == '-') {
            cur.push_back(c);
            inNumber = true;
        } else {
            if (inNumber) {
                flushNumber();
            }
            if (c == ']') {
                if (!row.empty()) {
                    grid.push_back(row);
                    row.clear();
                }
            }
        }
    }
    // In case the last number wasn't followed by a non-digit
    if (inNumber) {
        flushNumber();
        if (!row.empty()) {
            grid.push_back(row);
            row.clear();
        }
    }
    return grid;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    if (!getline(cin >> ws, line)) return 0;

    vector<vector<int>> grid = parseGrid(line);

    Solution sol;
    int ans = sol.orangesRotting(grid);
    cout << ans << "\n";

    return 0;
}
