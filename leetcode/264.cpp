#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
    class Comparator {
    public:
        bool operator()(const pair<int, int>& p1, const pair<int, int>& p2) const {
            return (long)p1.first * p1.second > (long)p2.first * p2.second;
        }
    };

    vector<int> dp;
    priority_queue<pair<int, int>, vector<pair<int, int>>, Comparator> pq;
    static const vector<int> primes;

    int recursiveSearch(int n) {
        if (dp.size() <= n)  {
            recursiveSearch(n - 1);
            for (int& prime : primes) {
                pq.emplace(dp[n-1], prime);
            }
            pair<int, int> num = pq.top();
            while ((long)num.first * num.second == dp[n - 1]) {
                pq.pop();
                num = pq.top();
            }
            dp.push_back((long)num.second * num.first);
            pq.pop();
        }
        return dp[n];
    }

public:
    int nthUglyNumber(int n) {
        dp = {1};
        return recursiveSearch(n - 1);
    }
};

const vector<int> Solution::primes = {2, 3, 5};

int main() {
    Solution sol;
    cout << sol.nthUglyNumber(10);
    cout << sol.nthUglyNumber(1);
    cout << sol.nthUglyNumber(11);
}