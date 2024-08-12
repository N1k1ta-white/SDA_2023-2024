#include <unordered_map>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    unordered_map<int, int> prefix;
public:
    int minOperations(vector<int>& nums, int x) {
        int sum = 0;
        int it = 0;
        for (int num : nums) {
            sum += num;
            prefix[sum] = ++it;
        }
        int res = (prefix.find(x) != prefix.end() ? prefix[x] : -1);
        if (sum > x) {
            int size = nums.size();
            for (int i = size - 1; i >= 0; i--) {
                x -= nums[i];
                if (x == 0) {
                    int temp = size - i;
                    res = res != -1 ? min(res, temp) : temp;
                    break;
                }
                if (prefix.find(x) != prefix.end()) {
                    int temp = size - i + prefix[x];
                    res = res != -1 ? min(res, temp) : temp;
                }
            }
        }
        return res;
    }
};

int main() {
    Solution solution;
    vector<int> arr = {1,1};
    cout << solution.minOperations(arr, 3);
}