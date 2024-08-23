#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {

    vector<vector<int>> res;

    void recursion(vector<int>& curr, int sum, int pos, const vector<int>& candidates, int target) {
        if (pos != -1) {
            curr.push_back(candidates[pos]);
            sum += candidates[pos];
        }
        if (sum < target) {
            for (int i = pos + 1; i < candidates.size(); ++i) {
                if (i == pos + 1 || candidates[i] != candidates[i - 1]) {
                    recursion(curr, sum, i, candidates, target);
                }
            }
        } else if (sum == target) {
            res.push_back(curr);
        }
        curr.pop_back();
    }

public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        res = vector<vector<int>>();
        vector<int> curr = {};
        recursion(curr, 0, -1, candidates, target);
        return res;
    }
};

int main() {
//    vector<int> vec = {10,1,2,7,6,1,5};
//    int target = 8;
    vector<int> vec = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,33,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,44,4,4,4,5,5,5,5,5,5,5,5,5,5,5,49,5,5,5,5,6,6,6,6};
    int target = 29;
    Solution solution;
    solution.combinationSum2(vec, target);
}