#include <queue>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Graph {
    vector<vector<int>> edges;
    const int DIST = 6;
    int N;
public:
    Graph(int N) : N(N) {
        edges.resize(N, vector<int>());
    }

    void addEdge(int from, int to) {
        edges[from].push_back(to);
    }

    vector<int> getNeighbours(int v) const {
        return edges[v];
    }

    void printDistance(int v) const {
        vector<int> distance(N, -1);
        queue<pair<int, int>> queue;
        queue.push({v, 0});
        pair<int, int> curr;
        while (!queue.empty()) {
            curr = queue.front();
            queue.pop();
            if (distance[curr.first] == -1) {
                distance[curr.first] = curr.second * DIST;
                for (int neighbours : getNeighbours(curr.first)) {
                    queue.push({neighbours, curr.second + 1});
                }
            }
        }
        for (int i = 0; i < N; ++i) {
            if (i == v) {
                continue;
            }
            cout << distance[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    int Q, N, M, x, y;
    cin >> Q;
    for (int i = 0; i < Q; ++i) {
        cin >> N >> M;
        Graph graph(N);
        for (int j = 0; j < M; ++j) {
            cin >> x >> y;
            x--;
            y--;
            graph.addEdge(x, y);
            graph.addEdge(y, x);
        }
        cin >> x;
        graph.printDistance(x - 1);
    }
}