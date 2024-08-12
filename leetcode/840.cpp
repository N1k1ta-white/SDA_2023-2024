#include <iostream>
#include <vector>

using namespace std;

class Solution {
    class SlidingWindow {
        static const int magic = 15;
        vector<vector<int>>* grid;
        vector<int> dist;
        int left;
        int right;
        bool dir;
        int downPos;
        int rowSum[3];
        int colSum[3];

        int move(int n1, int n2) {
            int sum = 0;
            for (int i = downPos - 3; i < downPos; ++i) {
                rowSum[i - downPos + 3] -= grid->at(i).at(n1);
                dist[grid->at(i).at(n1)]--;
                sum += grid->at(i).at(n2);
                rowSum[i - downPos + 3] += grid->at(i).at(n2);
                dist[grid->at(i).at(n2)]++;
            }
            return sum;
        }

        int getRowSum(int rowPos) {
            int sum = 0;
            for (int i = left; i <= right; ++i) {
                sum += grid->at(rowPos).at(i);
                dist[grid->at(rowPos).at(i)]++;
            }
            return sum;
        }

        int getColSum(int colPos, int rowPos) {
            int sum = 0;
            for (int i = rowPos; i < rowPos + 3; ++i) {
                sum += grid->at(i).at(colPos);
            }
            return sum;
        }

    public:
        SlidingWindow(vector<vector<int>>* grid) : grid(grid), left(0), right(2), downPos(0), dir(true) {
            dist = vector<int>(16, 0);
            for (int i = 0; i < 3; ++i, downPos++) {
                rowSum[i] = getRowSum(downPos);
                colSum[i] =
            }
        }

        bool isMagic() const {
            for (const int& sum : rowSum) {
                if (sum != magic) {
                    return false;
                }
            }
            for (const int& amount : dist) {
                if (amount > 1) {
                    return false;
                }
            }
            int diag = grid->at(downPos - 3).at(left) + grid->at(downPos - 2).at(left + 1) + grid->at(downPos - 1).at(right);
            int diag2 = grid->at(downPos - 3).at(right) + grid->at(downPos - 2).at(right - 1) + grid->at(downPos - 1).at(left);
            return !(diag != magic || diag2 != magic);
        }

        void move() {
            int sum = 0;
            if (dir) {
                right++;
                sum = move(left, right);
                left++;
                colSum[0] = colSum[1];
                colSum[1] = colSum[2];
                colSum[2] = sum;
            } else {
                left--;
                sum = move(right, left);
                right--;
                colSum[2] = colSum[1];
                colSum[1] = colSum[0];
                colSum[0] = sum;
            }
        }

        void down() {
            if (dir) {
                for (int i = 0; i < 3; ++i) {
                    colSum[i] -= grid->at(downPos - 3 + i + 1).at(left + i);
                }
            }

            dir = !dir;
            rowSum[0] = rowSum[1];
            rowSum[1] = rowSum[2];
            rowSum[2] = getRowSum(downPos);

            downPos++;
        }
    };

public:
    int numMagicSquaresInside(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        if (rows < 3 || cols < 3) {
            return 0;
        }
        SlidingWindow slidingWindow(&grid);
        int res = slidingWindow.isMagic();
        for (int i = 3; i <= rows; ++i) {
            for (int j = 3; j < cols; ++j) {
                slidingWindow.move();
                res += slidingWindow.isMagic();
            }
            if (i != rows) {
                slidingWindow.down();
                res += slidingWindow.isMagic();
            }
        }
        return res;
    }
};

int main() {
    vector<vector<int>> grid = {{2,7,6},{1,5,9},{4,3,8}};
    Solution solution;
    cout << solution.numMagicSquaresInside(grid);
}