#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Solution {
    const int mod = 1000000007;
public:
    int rangeSum(vector<int>& nums, int n, int left, int right) {
        multiset<int> sums;
        vector<int> sum(n, 0);
        sum[0] = nums[0];
        sums.insert(sum[0]);
        for (int i = 1; i < n; ++i) {
            sum[i] = sum[i - 1] + nums[i];
            sums.insert(sum[i]);
        }
        for (int i = 0; i < n; ++i) {
            int rem = nums[i];
            for (int j = i + 1; j < n; ++j) {
                sum[j] -= rem;
                sums.insert(sum[j]);
            }
        }

        int res = 0;
        multiset<int>::iterator it = next(sums.begin(), left - 1);
        for (int i = left; i <= right; ++i) {
            res = (res + *it++) % mod;
        }
        return res;
    }
};

int main() {
    Solution solution;
    vector<int> ex = {1,2,3,4};
    cout << solution.rangeSum(ex, ex.size(), 1, 5);
}