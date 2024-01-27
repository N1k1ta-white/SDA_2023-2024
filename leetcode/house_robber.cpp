#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {

    vector<int> min;

    int recursiveRob(int pos, vector<int>& nums) {
        if (min[pos] == -1) {
            int findMax = nums[pos], curr;
            for (int i = pos + 2; i < nums.size(); i++) {
                curr = recursiveRob(i, nums) + nums[pos];
                if (findMax < curr) {
                    findMax = curr;
                }
            }
            min[pos] = findMax;
        }
        return min[pos];
    }

public:
    int rob(vector<int>& nums) {
        if (nums.size() == 0) {
            return recursiveRob(0, nums);
        }
        min.resize(nums.size(), -1);
        int first = recursiveRob(0, nums),
            second = recursiveRob(1, nums);
        return std::max(first, second);
    }
};

int main() {
    Solution sol;
    vector<int> vec = {0};
    cout << sol.rob(vec);
}