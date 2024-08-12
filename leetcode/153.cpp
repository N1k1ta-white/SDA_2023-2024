#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    int binarySearch(int start, int end, const vector<int>& nums, int min) {
        if (start < end) {
            int mid = start + (end - start) / 2;
            if (nums[end] > nums[mid]) {
                return binarySearch(start, mid, nums, nums[mid]);
            } else {
                return binarySearch(mid + 1, end, nums, min);
            }
        }
        return nums[start];
    }
public:
    int findMin(vector<int>& nums) {
        return binarySearch(0, nums.size() - 1, nums, INT_MAX);
    }
};

int main() {
    Solution solution;
    vector<int> nums = {3, 1, 2};
    cout << solution.findMin(nums);
}