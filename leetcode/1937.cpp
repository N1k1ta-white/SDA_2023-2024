#include <iostream>
#include <vector>
#include <cmath>

#define ll long long

using namespace std;


class Solution {

    static ll max(ll a, ll b) {
        return a < b ? b : a;
    }

    static ll max(vector<ll> arr) {
        ll res = arr[0];
        for (int i = 1; i < arr.size(); ++i) {
            res = max(res, arr[i]);
        }
        return res;
    }

public:
    long long maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        int m = points[0].size();
        vector<vector<ll>> dp = vector<vector<ll>>(n, vector<ll >(m));
        vector<ll> left(m);
        vector<ll> right(m);
        for (int i = 0; i < m; ++i) {
            dp[0][i] = points[0][i];
        }
        for (int i = 1; i < n; ++i) {
            left[0] = dp[i - 1][0];
            right[m - 1] = dp[i - 1][m - 1];
            for (int j = 1; j < m; ++j) {
                left[j] = max(dp[i - 1][j], left[j - 1] - 1);
                right[m - 1 - j] = max(dp[i - 1][m - j - 1], right[m - j] - 1);
            }
            for (int j = 0; j < m; ++j) {
                dp[i][j] = max(left[j], right[j]) + points[i][j];
            }
        }
        return max(dp[n - 1]);
    }
};

int main() {
    vector<vector<int>> arr = {{1,2,3},{1,5,1},{3,1,1}};
    Solution sol;
    cout << sol.maxPoints(arr);
}