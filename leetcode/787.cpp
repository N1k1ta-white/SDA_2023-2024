#include <iostream>
#include <queue>

using namespace std;

vector<int> disjoint;

int getRoot(int x) {
    if (disjoint[x] == -1) {
        disjoint[x] = x;
    }
    if (disjoint[x] != x) {
        disjoint[x] = getRoot(disjoint[x]);
    }
    return disjoint[x];
}

void Union(int x, int y) {
    int r_x = getRoot(x), r_y = getRoot(y);
    disjoint[r_y] = r_x;
}

struct Path {
    int to;
    int cost;
};

struct PathForSearch {
    Path p;
    int stops;
};

class Graph {
    vector<vector<Path>> edges;
public:
    Graph(int n) {
        edges.resize(n, vector<Path>());
    }

    void addEdge(int from, int to, int cost) {
        edges[from].push_back({to, cost});
        Union(from, to);
    }

    int findShortestPath(int from, int to, int k) {
        queue<PathForSearch> q;
        q.push({{from, 0}, -1});
        vector<int> dist(edges.size(), INT_MAX);
        while (!q.empty()) {
            PathForSearch curr = q.front();
            q.pop();
            if (curr.stops < k) {
                for (Path path: edges[curr.p.to]) {
                    int cost = curr.p.cost + path.cost;
                    if (dist[path.to] > cost) {
                        q.push({{path.to, cost}, curr.stops + 1});
                        dist[path.to] = cost;
                    }
                }
            }
        }
        return dist[to] == INT_MAX ? -1 : dist[to];
    }
};

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        Graph graph(n);
        disjoint.resize(n, -1);
        for (const vector<int>& flight : flights) {
            graph.addEdge(flight[0], flight[1], flight[2]);
        }
        if (getRoot(src) != getRoot(dst)) {
            return -1;
        }
        return graph.findShortestPath(src, dst, k);
    }
};

int main() {
    Solution sol;
    vector<vector<int>> flights = {{0, 1, 100}, {1, 2, 100}, {2, 0, 100}, {1, 3, 600}, {2, 3, 200}};
    cout << sol.findCheapestPrice(4, flights, 0, 3, 1);
}