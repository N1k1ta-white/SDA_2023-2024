#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int getCommon(vector<int>& nums1, vector<int>& nums2) {
        for (int num : nums1) {
            int pos = lower_bound(nums2.begin(), nums2.end(), num) - nums2.begin();
            if (pos > 0 && num == nums2[pos]) {
                return num;
            }
        }
        return -1;
    }
};

int main() {
    Solution sol;
    vector<int> num1 = {3, 5};
    vector<int> num2 = {2};
    cout << sol.getCommon(num1, num2);
}