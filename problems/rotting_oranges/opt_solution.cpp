// Rotting Oranges - Optimized Solution
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // Constants for grid values (better than magic numbers)
    static const int EMPTY = 0;
    static const int FRESH = 1;
    static const int ROTTEN = 2;
    
    // Direction vectors: Up, Down, Left, Right
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        queue<pair<int, int>> q;  // {row, col}
        int freshCount = 0;
        
        // OPTIMIZATION 1: Single pass - count fresh and enqueue rotten
        // No need for intermediate rottingSources vector
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == ROTTEN) {
                    q.push({i, j});
                } else if (grid[i][j] == FRESH) {
                    freshCount++;
                }
            }
        }
        
        // Edge case: no fresh oranges
        if (freshCount == 0) return 0;
        
        int minutes = 0;
        
        // BFS - level by level
        while (!q.empty()) {
            int levelSize = q.size();
            bool rottedThisMinute = false;
            
            // Process all oranges that rot at the current minute
            for (int i = 0; i < levelSize; i++) {
                auto [row, col] = q.front();
                q.pop();
                
                // OPTIMIZATION 2: Direction array eliminates 4 duplicate blocks
                for (int dir = 0; dir < 4; dir++) {
                    int newRow = row + dr[dir];
                    int newCol = col + dc[dir];
                    
                    // Check bounds and if orange is fresh
                    if (newRow >= 0 && newRow < m && 
                        newCol >= 0 && newCol < n && 
                        grid[newRow][newCol] == FRESH) {
                        
                        grid[newRow][newCol] = ROTTEN;
                        freshCount--;
                        q.push({newRow, newCol});
                        rottedThisMinute = true;
                    }
                }
            }
            
            // Only increment time if we actually rotted oranges this minute
            if (rottedThisMinute) {
                minutes++;
            }
        }
        
        // If there are still fresh oranges, they're unreachable
        return freshCount == 0 ? minutes : -1;
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
