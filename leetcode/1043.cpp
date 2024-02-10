#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {

    unordered_map<int, int> storageOfRes;
    unordered_map<int, int> sumOfInter;

    int hash(int start, int end) {
        return start * 501 + end;
    }

    int getSumOfInter(vector<int>& vec, int start, int end) {
        int hashCode = hash(start, end);
        if (!sumOfInter.count(hashCode)) {
            int max = -1;
            for (int i = start; i <= end; i++) {
                if (vec[i] > max) {
                    max = vec[i];
                }
            }
            sumOfInter[hashCode] = max * (end - start);
        }
        return sumOfInter[hashCode];
    }

    int recursiveSearch(int pos, int k, vector<int>& arr) {
        if (!storageOfRes.count(pos)) {
            int max = 0, curr, sum;
            for (int i = pos + 1; i < pos + k + 1 && i < arr.size(); i++) {
                sum = getSumOfInter(arr, pos, i);
                curr = recursiveSearch(i, k, arr) + sum;
                if (curr > max) {
                    max = curr;
                }
            }
            storageOfRes[pos] = max;
        }
        return storageOfRes[pos];
    }

public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        return recursiveSearch(0, k, arr);
    }
};

int main() {
    Solution sol;
    vector<int> arr = {1,15,7,9,2,5,10};
    cout << sol.maxSumAfterPartitioning(arr, 3);
}