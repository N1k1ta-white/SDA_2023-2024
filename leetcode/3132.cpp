#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int minimumAddedInteger(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        int diff = INT_MAX, temp, it;
        for (int i = 0; i < nums1.size() && nums1.size() - i >= nums2.size(); ++i) {
            temp = nums2[0] - nums1[i];
            it = 0;
            if (temp < diff) {
                for (int j = 0; j < nums1.size() && it < nums2.size(); ++j) {
                    if (nums2[it] - nums1[j] == temp) {
                        it++;
                    }
                }
                if (it >= nums2.size()) {
                    diff = min(diff, temp);
                }
            }
        }
        return diff;
    }
};

int main() {
    Solution solution;
    vector<int> num1 = {3,3,5,5};
    vector<int> num2 = {7,7};
    cout << solution.minimumAddedInteger(num1, num2);
}