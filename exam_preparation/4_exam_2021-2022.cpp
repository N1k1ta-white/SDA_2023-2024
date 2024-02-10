#include <queue>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Graph {
    unordered_map<int, vector<int>> edges;
public:
    void addEdge(int from, int to) {
        edges[from].push_back(to);
    }

    vector<int> getEdges(int v) {
        return edges[v];
    }

    int getWeight(int v) {
        unordered_map<int, bool> visited;
        queue<int> queue;
        queue.push(v);
        int res = -v, curr;
        while (!queue.empty()) {
            curr = queue.front();
            queue.pop();
            if (!visited[curr]) {
                res += curr;
                for (int vertices: getEdges(curr)) {
                    queue.push(vertices);
                }
                visited[curr] = true;
            }
        }
        return res;
    }
};

int main() {
    int m, t, x, y;
    cin >> m >> t;
    Graph graph;
    for (int i = 0; i < m; ++i) {
        cin >> x >> y;
        graph.addEdge(x, y);
    }
    for (int i = 0; i < t; ++i) {
        cin >> x;
        cout << graph.getWeight(x) << endl;
    }
}