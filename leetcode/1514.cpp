#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
        // first current probability    second nextEdge
        priority_queue<pair<double, int>> pq;
        vector<bool> visited(n, false);
        unordered_map<int, vector<pair<double,int>>> edgesList;

        for (int i = 0; i < edges.size(); i++) {
            edgesList[edges[i][0]].emplace_back(succProb[i], edges[i][1]);
            edgesList[edges[i][1]].emplace_back(succProb[i], edges[i][0]);
        }

        pq.emplace(1, start_node);
        while (!pq.empty()) {
            pair<double, int> curr = pq.top();
            pq.pop();
            if (!visited[curr.second]) {
                if (curr.second == end_node) {
                    return curr.first;
                }
                for (pair<double, int> &neighbours: edgesList[curr.second]) {
                    pq.emplace(curr.first * neighbours.first, neighbours.second);
                }
                visited[curr.second] = true;
            }
        }
        return 0;
    }
};

int main() {
    Solution solution;
    int n = 3;
    vector<vector<int>> edges = {
            {0, 1},
            {1, 2},
            {0, 2}
    };
    vector<double> succProb = {0.5, 0.5, 0.3};
    int endPoint = 2;
    int startPoint = 0;

    cout << solution.maxProbability(n, edges, succProb, startPoint, endPoint);
}