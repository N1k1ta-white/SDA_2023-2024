#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {

    const int variants[3][2] = {{1, -1}, {1, 0}, {1, 1}};
    unordered_map<int, int> shortest_paths;

    class Graph {
        unordered_map<int, vector<int>> edge;
        unordered_map<int, int> value;
    public:

        void addEdge(int x, int y) {
            edge[x].push_back(y);
        }

        vector<int> getNeighbours(int num) {
            return edge[num];
        }

        void setValue(int hash, int val) {
            value[hash] = val;
        }

        int getValue(int hash) {
            return value[hash];
        }
    };

    inline int hash(int x, int y) const {
        return x * 101 + y;
    }

    int findShortestPathByValue(Graph& graph, int curr) {
        if (!shortest_paths.count(curr)) {
            bool first = true;
            int min = graph.getValue(curr);
            for (int neighbours: graph.getNeighbours(curr)) {
                int res = findShortestPathByValue(graph, neighbours) + graph.getValue(curr);
                if (res < min || first) {
                    min = res;
                    first = false;
                }
            }
            shortest_paths[curr] = min;
            return min;
        } else {
            return shortest_paths[curr];
        }
    }

public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        Graph graph;
        int n = matrix.size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                graph.setValue(hash(i, j), matrix[i][j]);
                for (int k = 0; k < 3; ++k) {
                    if (i + variants[k][0] >= 0 && i + variants[k][0] < n
                        && j + variants[k][1] >= 0 && j + variants[k][1] < n) {
                        graph.addEdge(hash(i, j), hash(i + variants[k][0], j + variants[k][1]));
                    }
                }
            }
        }

        int min = findShortestPathByValue(graph, hash(0, 0)), curr;
        for (int i = 1; i < n; ++i) {
            curr = findShortestPathByValue(graph, hash(0, i));
            if (curr < min) {
                min = curr;
            }
        }
        return min;
    }
};

int main() {
    vector<vector<int>> matrix;
    matrix.push_back({2, 1, 3});
    matrix.push_back({6, 5, 4});
    matrix.push_back({7, 8, 9});
    Solution sol;
    cout << sol.minFallingPathSum(matrix);
}