#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <queue>
using namespace std;

class Graph {
    struct Path {
        size_t from;
        size_t to;
        size_t cost;
    };

    class PathComparator {
    public:
        bool operator()(const Path& p1, const Path& p2) const {
            return p1.cost < p2.cost;
        }
    };
private:
    size_t countOfEdges;
    unordered_map<size_t, vector<Path>> edges;
public:
    void addEdge(size_t to, size_t from, size_t cost) {
        edges[to].push_back({to, from, cost});
        edges[from].push_back({from, to, cost});
    }

    vector<Path> getEdge(size_t v) {
        return edges[v];
    }

    size_t kruskal() {
        size_t v = edges.begin()->first;
        unordered_map<size_t, bool> visited;
        priority_queue<Path, vector<Path>, PathComparator> pq;
        visited[v] = true;
        size_t sum = 0;
        for (Path& p : edges.begin()->second) {
            pq.push(p);
        }
        while (!pq.empty()) {
            Path curr = pq.top();
            pq.pop();
            if (!visited[curr.to]) {
                sum += curr.cost;
                for (Path& p : edges[curr.to]) {
                    pq.push(p);
                }
                visited[curr.to] = true;
            }
        }
        return sum;
    }
};

int main() {
    size_t N, M, x, y, w;
    cin >> N >> M;
    size_t sum = 0;
    Graph graph;
    for (size_t i = 0; i < M; ++i) {
        cin >> x >> y >> w;
        sum += w;
        graph.addEdge(x, y, w);
    }
    cout << sum - graph.kruskal();
}