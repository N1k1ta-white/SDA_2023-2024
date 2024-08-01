#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

using namespace std;

class Graph {
    unordered_map<int, vector<int>> edges;
    unordered_map<int, int> val;
    unordered_map<int, int> dist;
    int size;

    static int hash(int i, int j) {
        return i * 201 + j;
    }

    int hash(int i, int j, int val) {
        int hs = hash(i, j);
        if (!this->val.count(val)) {
            this->val[hs] = val;
        }
        return hs;
    }

    void addEdge(int h1, int h2) {
        edges[h1].push_back(h2);
    }

    void dfs(int from, stack<int>& stack, unordered_map<int, bool>& visited) {
        visited[from] = true;
        for (int vert : edges[from]) {
            if (!visited.count(vert)) {
                dfs(vert, stack, visited);
            }
        }
        stack.push(from);
    }

    void relax(int from, int to) {
        int currDist = dist[from] + val[to];
        if (!dist.count(to) || dist[to] > currDist) {
            dist[to] = currDist;
        }
    }

public:
    Graph(const vector<vector<int>>& triangle) {
        size = triangle.size();
        dist[0] = triangle[0][0];
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < i + 1; ++j) {
                int root = hash(i, j);
                int left = hash(i + 1, j, triangle[i + 1][j]);
                int right = hash(i + 1, j + 1, triangle[i + 1][j + 1]);
                addEdge(root, right);
                addEdge(root, left);
            }
        }
    }

    stack<int> getTopoSort() {
        stack<int> topo;
        unordered_map<int, bool> visited;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < i + 1; ++j) {
                if (!visited.count(hash(i, j))) {
                    dfs(hash(0, 0), topo, visited);
                }
            }
        }
        return topo;
    }

    void DAG() {
        stack<int> topo = getTopoSort();
        while (!topo.empty()) {
            int curr = topo.top();
            topo.pop();
            for (int vert : edges[curr]) {
                relax(curr, vert);
            }
        }
    }

    int getMinPathToBottomOfTriangle() {
        int res = INT_MAX;
        for (int i = 0; i < size; ++i) {
            res = min(dist[hash(size - 1, i)], res);
        }
        return res;
    }
};

int main() {
    vector<vector<int>> triangle = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
    Graph gr(triangle);
    gr.DAG();
    cout << gr.getMinPathToBottomOfTriangle();
}