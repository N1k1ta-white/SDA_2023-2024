#include <iostream>
#include <vector>
#include <unordered_map>
#include <valarray>

using namespace std;

class Solution {

    class Hash {
    public:
        static int hash(bool alice, int pos, int M) {
            return alice * 101 * 101 + pos * 101 + M;
        }
    };

    unordered_map<int, int> dp;

    int recursiveSearch(int pos, int M, const vector<int>& piles, bool alice) {
        int hash = Hash::hash(alice, pos, M);
        if (pos == piles.size()) {
            return 0;
        }
        if (dp.find(hash) == dp.end()) {
            int res = alice ? -1 : INT_MAX;
            int sum = 0;
            for (int i = 1; i <= 2 * M && pos + i <= piles.size(); ++i) {
                sum += piles[i - 1 + pos];
                if (alice) {
                    res = max(recursiveSearch(pos + i, max(i, M), piles, !alice) + sum, res);
                } else {
                    res = min(recursiveSearch(pos + i, max(i, M), piles, !alice), res);
                }
            }
            dp[hash] = res;
        }
        return dp[hash];
    }

public:
    int stoneGameII(vector<int>& piles) {
        return recursiveSearch(0, 1, piles, true);
    }
};

int main() {
//    vector<int> vec = {1,2,3,4,5,100};
    vector<int> vec = {2,7,9,4,4};
    Solution solution;
    cout << solution.stoneGameII(vec);
}