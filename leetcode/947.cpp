#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {

    class Disjoint {
      vector<int> disjoint;
      vector<int> rank;
      int groupCount;
    public:
        explicit Disjoint(int n) : groupCount(n) {
            disjoint = vector<int>(n);
            for (int i = 0; i < n; ++i) {
                disjoint[i] = i;
            }
            rank = vector<int>(n, 1);
        }

        int find(int x) {
            if (disjoint[x] != x) {
                disjoint[x] = find(disjoint[x]);
            }
            return disjoint[x];
        }

        void Union(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX == rootY) {
                return;
            }
            groupCount--;
            if (rank[rootX] < rank[rootY]) {
                swap(rootX, rootY);
            }
            disjoint[rootY] = rootX;
            rank[rootX] += rank[rootY];
        }

        int getGroupCount() const {
            return groupCount;
        }
    };

    struct Hash {
    private:
        static const int prime = 10007;
    public:
        static int hash(int n, bool axis) {
            return prime * axis + n;
        }
    };

    const bool x = false;
    const bool y = true;

public:
    int removeStones(vector<vector<int>>& stones) {
        unordered_map<int, vector<int>> neighbours;
        int n = stones.size();
        Disjoint disjoint(n);

        for (int i = 0; i < n; ++i) {
            neighbours[Hash::hash(stones[i][x], x)].push_back(i);
            neighbours[Hash::hash(stones[i][y], y)].push_back(i);
        }

        for (auto& line : neighbours) {
            for (int i = 1; i < line.second.size(); ++i) {
                disjoint.Union(line.second[0], line.second[i]);
            }
        }

        return n - disjoint.getGroupCount();
    }
};

int main() {
    vector<vector<int>> stones = {{3,2},{3,1},{4,4},{1,1},{0,2},{4,0}};
    Solution solution;
    cout << solution.removeStones(stones);
}