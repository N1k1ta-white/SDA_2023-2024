#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int numSpecial(vector<vector<int>>& mat) {
        int res = 0;
        int m = mat.size(), n = mat[0].size();
        vector<int> arrCol(n, 0);
        vector<int> arrRow(m, 0);
        for (int i = 0; i < m; i++) {
            int hasOne = 0;
            for (int j = 0; j < n; j++) {
                if (mat[i][j]) {
                    if (hasOne == 1) {
                        hasOne = -1;
                    }
                    if (arrCol[j] == 0 && hasOne == 0) {
                        arrCol[j] = 1;
                        hasOne = 1;
                    } else if (arrCol[j] == 1) {
                        arrCol[j] = -1;
                    }
                }
                if (hasOne != -1) {
                    arrRow[i] = 1;
                }
            }
        }
        return res;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> mat(5);
    mat[0] = {0,0,0,0,0,1,0,0};
    mat[1] = {0,0,0,0,1,0,0,1};
    mat[2] = {0,0,0,0,1,0,0,0};
    mat[3] = {1,0,0,0,1,0,0,0};
    mat[4] = {0,0,1,1,0,0,0,0};
    cout << sol.numSpecial(mat);
}