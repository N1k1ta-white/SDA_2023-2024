#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {

    unordered_map<int, int> paths;

    int hash(int x, int y) {
        return x * 101 + y;
    }

    int recursiveStep(int x, int y, int height, int width) {
        if (!paths.count(hash(x, y))) {
            if (x > height || y > width || x < 0 || y < 0) {
                return 0;
            } else if (x == height - 1 || y == width - 1) {
                return 1;
            }
            paths[(hash(x, y))] = recursiveStep(x + 1, y, height, width)
                                  + recursiveStep(x, y + 1, height, width);
        }
        return paths[hash(x, y)];
    }

public:
    int uniquePaths(int m, int n) {
        return recursiveStep(0, 0, m, n);
    }
};

int main() {
    Solution sol;
    cout << sol.uniquePaths(3, 7);
}