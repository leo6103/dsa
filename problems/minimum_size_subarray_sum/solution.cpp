#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int mySolOpt(int target, vector<int> &nums) {
      int l = 0;
      int r = 0;
      int min_len = INT_MAX;
      int sum = 0;
      int len = 0;
      for (r = 0; r < nums.size(); ++r) {
        sum += nums[r];
        len ++;

        while (l < r) {
          
        }
      }
      return min_len == INT_MAX ? 0 : min_len;
    }

    int mySol(int target, vector<int> &nums) {
      int l = 0;
      int r;
      int sum = 0;
      int min_len = INT_MAX;
      int min_len_set = false;
      int len = 0;

      for (r = 0; r < nums.size(); ++r) {
        sum += nums[r];
        len ++;

        if (sum >= target) {
          if (len < min_len) {
            min_len = len;
            min_len_set = true;
          }
          while (l < r) {
            sum -= nums[l];
            len --;
            l++;

            if (sum >= target) {
              if (len < min_len) {
                min_len = len;
                min_len_set = true;
              }
            }
            else break;
          }
        }
      }

      return min_len_set ? min_len : 0;
    }

    // GPT's sliding window solution
    int gptSol(int target, const vector<int> &nums) {
      int n = nums.size();
      int left = 0;
      int sum = 0;
      int ans = INT_MAX;

      for (int right = 0; right < n; ++right) {
        sum += nums[right];
        while (sum >= target) {
          ans = min(ans, right - left + 1);
          sum -= nums[left++];
        }
      }

      return ans == INT_MAX ? 0 : ans;
    }

    int minSubArrayLen(int target, vector<int> &nums) {
      return gptSol(target, nums);
    }
      
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int target;
    if (!(cin >> target)) return 0;

    string line;
    if (!getline(cin >> ws, line)) return 0;

    if (!line.empty() && line.front() == '[' && line.back() == ']') {
        line = line.substr(1, line.size() - 2);
    }

    vector<int> nums;
    string token;
    stringstream ss(line);
    while (getline(ss, token, ',')) {
        if (token.empty()) continue;
        nums.push_back(stoi(token));
    }

    Solution sol;
    cout << sol.minSubArrayLen(target, nums) << "\n";

    return 0;
}
