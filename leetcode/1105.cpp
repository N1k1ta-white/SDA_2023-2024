#include <vector>
#include <iostream>

using namespace std;

class Solution {
    vector<int> dp;
    const int width = 0;
    const int height = 1;

    int recursiveFilling(int pos, vector<vector<int>>& books, int shelfWidth) {
        if (pos == books.size()) {
            return 0;
        } else if (dp[pos] == -1) {
            int remainsWidth = shelfWidth;
            int maxHeight = 0;
            dp[pos] = INT_MAX;
            for (int i = pos; i < books.size(); i++) {
                if (books[i][width] > remainsWidth) {
                    break;
                }
                maxHeight = max(maxHeight, books[i][height]);
                remainsWidth -= books[i][width];
                dp[pos] = min(dp[pos], maxHeight + recursiveFilling(i + 1, books, shelfWidth));
            }
        }
        return dp[pos];
    }

public:
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        dp = vector<int>(books.size(), -1);
        return recursiveFilling(0, books, shelfWidth);
    }
};

int main() {
    vector<vector<int>> books = {{1,1},{2,3},{2,3}};
    int shelf = 4;
    Solution solution;
    cout << solution.minHeightShelves(books, shelf);
}