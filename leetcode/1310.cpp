//
// Created by Nikita on 13.09.2024.
//
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    static const int left = 0;
    static const int right = 1;

    vector<int> prefixSum;

    void computePrefixSum(vector<int>& arr) {
        prefixSum = vector<int>(arr.size());
        prefixSum[0] = arr[0];

        for (int i = 1; i < arr.size(); ++i) {
            prefixSum[i] = prefixSum[i - 1] ^ arr[i];
        }
    }

    int computeXorQuery(int start, int end) {
        if (start == 0) {
            return prefixSum[end];
        }
        return prefixSum[start - 1] ^ prefixSum[end];
    }

public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        vector<int> answer(queries.size());

        computePrefixSum(arr);

        int i = 0;
        for (vector<int>& query : queries) {
            answer[i++] = computeXorQuery(query[left], query[right]);
        }

        return answer;
    }
};

int main() {
    vector<int> arr = {4, 8, 2, 10};
    vector<vector<int>> queries = {{2, 3}, {1, 3}, {0, 0}, {0, 3}};
    Solution solution;

    vector<int> res = solution.xorQueries(arr, queries);
}