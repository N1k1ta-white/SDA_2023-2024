#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <queue>

using namespace std;

unordered_map<int, set<int>> primeFactor;

set<int> getPrimeFactor(int num) {
    int copy = num;
    bool end = false;
    if (!primeFactor.count(num)) {
        int prime = 2;
        while (num != 1) {
            while (num % prime == 0) {
                primeFactor[copy].insert(prime);
                num /= prime;
                getPrimeFactor(num);
                for (int primeRes : primeFactor[num]) {
                    primeFactor[copy].insert(primeRes);
                }
                end = true;
                break;
            }
            if (end) {
                break;
            }
            prime++;
        }
    }
    return primeFactor[copy];
}

class Relation {
    set<int> factorNumbs;
public:
    Relation(int num) {
        factorNumbs = getPrimeFactor(num);
    }

    bool add(int num) {
        set<int> primes = getPrimeFactor(num);
        bool contain = false;
        for (int prime : primes) {
            if (factorNumbs.count(prime)) {
                contain = true;
                break;
            }
        }
        if (contain) {
            for (int num : primes) {
                factorNumbs.insert(num);
            }
        }
        return contain;
    }
};

class Solution {
public:
    bool canTraverseAllPairs(vector<int>& nums) {
        if (nums.size() == 1 && nums[0] == 1) {
            return true;
        }
        queue<int> skippedNums;
        Relation rel(nums[0]);
        for (int num : nums) {
            if (num == 1) {
                return false;
            }
            if (!rel.add(num)) {
                skippedNums.push(num);
            }
        }
        bool added;
        do {
            added = false;
            queue<int> skipped2;
            while (!skippedNums.empty()) {
                int curr = skippedNums.front();
                skippedNums.pop();
                if (!rel.add(curr)) {
                    skipped2.push(curr);
                } else {
                    added = true;
                }
            }
            skippedNums = std::move(skipped2);
        } while (added && !skippedNums.empty());
        return skippedNums.empty();
    }
};

int main() {
    unordered_map<int, set<int>> *pointer = &primeFactor;
    getPrimeFactor(100);
    Solution sol;
    vector<int> arg = {1};
    cout << sol.canTraverseAllPairs(arg);
}