#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {

    class SlideWindow {
        vector<int> *nums;
        int count;
        int left;
        int right;

        void fill() {
            for (int i = 0; i < right + 1; ++i) {
                if (nums->at(i) == 1) {
                    count++;
                }
            }
        }

    public:
        SlideWindow(int size, vector<int>* vec) : count(0), nums(vec), right(size - 1), left(0) {
            fill();
        }

        int getCount() const {
            return count;
        }

        int next() {
            right++;
            if (nums->at(right) == 1) {
                count++;
            }
            if (nums->at(left) == 1) {
                count--;
            }
            left++;
            return count;
        }
    };

public:
    int minSwaps(vector<int>& nums) {
        int count = 0;
        for (int& num : nums) {
            if (num == 1) {
                count++;
            }
        }
        SlideWindow slideWindow(count, &nums);
        int ans = count - slideWindow.getCount();
        for (int i = 0; i < count - 1; ++i) {
            nums.push_back(nums[i]);
        }
        for (int i = count; i < nums.size(); ++i) {
            ans = min(ans, count - slideWindow.next());
        }
        return ans;
    }
};

int main() {
    vector<int> nums = {1,1,0,0};
    Solution solution;
    cout << solution.minSwaps(nums);
}