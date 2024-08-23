#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>

using namespace std;

class Solution {

    class SlidingWindow {
        vector<int>* nums;
    public:
        SlidingWindow(vector<int>* nums) : nums(nums) {}

        int searchPairsWithMaxDist(int max) {
            int count = 0;
            int size = nums->size();
            int left = 0, right = 0;
            for (;right < size; right++) {
                while (nums->at(right) - nums->at(left) > max) {
                    left++;
                }
                count += right - left;
            }
            return count;
        }
    };

    int binarySearch(int start, int end, int k, SlidingWindow& slidingWindow)  {
        if (start < end) {
            int mid = start + (end - start) / 2;
            int count = slidingWindow.searchPairsWithMaxDist(mid);
            if (count < k) {
                return binarySearch(mid + 1, end, k, slidingWindow);
            } else {
                return binarySearch(start, mid, k, slidingWindow);
            }
        }
        return start;
    }


public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int max = nums[nums.size() - 1] - nums[0];
        int min = 0;
        SlidingWindow slidingWindow(&nums);
        return binarySearch(min, max, k, slidingWindow);
    }
};

int main() {
    vector<int> nums = {9,10,7,10,6,1,5,4,9,8};
    int k = 18;
    Solution solution;
    cout << solution.smallestDistancePair(nums, k);
}