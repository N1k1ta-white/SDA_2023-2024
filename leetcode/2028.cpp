//
// Created by Nikita on 05.09.2024.
//
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    int getSumOfRollsFromList(const vector<int>& rolls) {
        int sum = 0;
        for (const int& roll : rolls) {
            sum += roll;
        }
        return sum;
    }

    vector<int> getListOfRollsRelyOnSum(int sum, int count) {
        int average = sum / count;
        if (average <= 0 || average > 6) {
            return {};
        }
        vector<int> res = vector<int>(count, average);
        int remain = sum % count;
        for (int i = 0; remain > 0; remain--, i++) {
            i %= count;
            res[i]++;
            if (res[i] > 6) {
                return {};
            }
        }
        return res;
    }

public:
    vector<int> missingRolls(vector<int>& rolls, int mean, int n) {
        int m = rolls.size();
        int sumM = getSumOfRollsFromList(rolls);
        int countOfRolls = m + n;
        int sum = countOfRolls * mean;
        int sumN = sum - sumM;
        return getListOfRollsRelyOnSum(sumN, n);
    }
};

int main() {
    vector<int> rolls = {6,3,4,3,5,3};
    int mean = 1;
    int n = 6;

    Solution solution;

    for (int num : solution.missingRolls(rolls, mean, n)) {
        cout << num << " ";
    }
}