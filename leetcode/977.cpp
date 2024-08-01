#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        vector<int> res(nums.size());
        int s = 0, e = nums.size() - 1;
        for (int i = nums.size() - 1; i >= 0; --i) {
            if (abs(nums[s]) > abs(nums[e])) {
                res[i] = nums[s] * nums[s];
                s++;
            } else {
                res[i] = nums[e] * nums[e];
                e--;
            }
        }
        return res;
    }
};

int main() {
    vector<int> vec = {-4, -1, 0, 3, 10};
    Solution sol;
    vec = sol.sortedSquares(vec);
}