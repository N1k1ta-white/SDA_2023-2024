#include <iostream>
#include <vector>

using namespace std;

class Solution {

    static int getPos(int x, int y, int width) {
        return x * width + y;
    }

public:
    vector<vector<int>> construct2DArray(vector<int>& original, int m, int n) {
        if (original.size() != n * m) {
            return {};
        }
        vector<vector<int>> vec(m, vector<int>(n));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                vec[i][j] = original[getPos(i, j, n)];
            }
        }
        return vec;
    }
};
int main() {

}
