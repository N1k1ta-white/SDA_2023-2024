#include <iostream>
#include <vector>

using namespace std;

class Solution {
    static const vector<vector<int>> dir;

public:
    vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart) {
        vector<vector<int>> res;
        int count = rows * cols;

        vector<int> pos = {rStart, cStart};
        res.push_back(pos);
        int dirPos = 0;
        for (int i = 0, t = 1; res.size() < count; ++i, ++t) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < t; ++k) {
                    pos[0] += dir[dirPos][0];
                    pos[1] += dir[dirPos][1];
                    if (pos[0] >= 0 && pos[0] < rows && pos[1] >= 0 && pos[1] < cols) {
                        res.push_back(pos);
                    }
                }
                dirPos = (dirPos + 1) % 4;
            }
        }
        return res;
    }
};

const vector<vector<int>> Solution::dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int main() {
    Solution solution;
    solution.spiralMatrixIII(6, 6, 1, 1);
}