#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {

    struct Hash {
        static int hash(int i, int j) {
            return i * 31 + j;
        }

        // i j
        pair<int, int> unhash(int hash) {
            return {hash % 31, hash / 31};
        }
    };

    class Graph {
        unordered_map<int, vector<int>> edges;
        int time;

        bool dfsTarjan(int curr, unordered_map<int, int>& parent, unordered_map<int, int>& disc,
                       unordered_map<int, int>& low) {
            disc[curr] = low[curr] = time++;

            for (int& neighbour: edges[curr]) {
                if (disc.find(neighbour) == disc.end()) {
                    parent[neighbour] = curr;
                    bool res = dfsTarjan(neighbour, parent, disc, low);
                    low[curr] = min(low[curr], low[neighbour]);
                    if ((low[neighbour] >= disc[curr] && parent[curr] != -1) || res) {
                        return true;
                    }
                } else if (neighbour != parent[curr]) {
                    low[curr] = min(disc[neighbour], low[curr]);
                }
            }
            return false;
        }


    public:
        void addGraph(int from, int to) {
            edges[from].push_back(to);
        }

        bool findBridge() {
            unordered_map<int, int> disc;
            unordered_map<int, int> low;
            unordered_map<int, int> parent;
            time = 0;
            parent[edges.begin()->first] = -1;
            return dfsTarjan(edges.begin()->first, parent, disc, low);
        }

        int getCountOfEdges() const {
            return edges.size();
        }
    };

    const vector<pair<int, int>> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    void recursiveAdding(int i, int j, vector<vector<int>>& grid, Graph& graph, unordered_map<int, bool>& isExist) {
        int hash = Hash::hash(i, j);
        if (!isExist[hash]) {
            isExist[hash] = true;
            for (const auto &k: dir) {
                if (i + k.first < grid.size() && j + k.second < grid[i].size() && grid[i + k.first][j + k.second]) {
                    graph.addGraph(hash, Hash::hash(i + k.first, j + k.second));
                    recursiveAdding(i + k.first, j + k.second, grid, graph, isExist);
                }
            }
        }
    }

public:
    int minDays(vector<vector<int>>& grid) {
        Graph graph;
        int n = grid.size(), m = grid[0].size();
        unordered_map<int, bool> isExist;
        bool found = false;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] && !found) {
                    found = true;
                    recursiveAdding(i, j, grid, graph, isExist);
                } else if (grid[i][j] && found && !isExist[Hash::hash(i, j)]) {
                    return 0;
                }
            }
        }

        if (graph.getCountOfEdges() <= 2) {
            return graph.getCountOfEdges() == 0 ? found : graph.getCountOfEdges();
        }

        return graph.findBridge() ? 1 : 2;
    }
};

int main() {
    vector<vector<int>> grid = {{0,1,1},{1,1,1},{1,1,0}};
    Solution sol;
    cout << sol.minDays(grid);
}