#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int maxFrequencyElements(vector<int>& nums) {
        unordered_map<int, int> map;
        unordered_map<int, int> freq;
        int max = 0;
        for (int i = 0; i < nums.size(); i++) {
            --freq[map[nums[i]]++];
            freq[map[nums[i]]]++;
            if (map[nums[i]] > map[max]) {
                max = nums[i];
            }
        }
        return freq[map[max]] * map[max];
    }
};

int main() {
    Solution sol;
    vector<int> vec = {10,12,11,9,6,19,11};
    cout << sol.maxFrequencyElements(vec);
}