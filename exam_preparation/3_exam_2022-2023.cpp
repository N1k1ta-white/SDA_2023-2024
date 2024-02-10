#include <queue>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Graph {
    vector<vector<int>> edges;
    vector<int> *aVec;
    unordered_map<int, int> a;
    unordered_map<int, bool> p;
public:
    Graph(int v) {
        edges.resize(v, vector<int>());
    }

    void addEdge(int from, int to) {
        edges[from].push_back(to);
    }

    void addP(const vector<int>& p) {
        for (int num : p) {
            this->p[num] = true;
        }
    }

    void addA(vector<int>& a) {
        aVec = &a;
        int it = 0;
        for (int i : a) {
            this->a[i] = it++;
        }
    }

    int findShortestPath(int a1, int a2) {
        unordered_map<int, bool> visited;
        queue<pair<int, int>> queue;
        queue.push({a1, 0});
        pair<int, int> curr;
        while (!queue.empty()) {
            curr = queue.front();
            queue.pop();
            if (curr.first == a2) {
                return curr.second;
            }
            if (a.count(curr.first) && a[curr.first] > a[a1] || p.count(curr.first)) {
                continue;
            }
            if (!visited[curr.first]) {
                visited[curr.first] = true;
                for (int to: edges[curr.first]) {
                    queue.emplace(to, curr.second + 1);
                }
            }
        }
        return 0;
    }


    int findFullShortestPath() {
        int res = 0;
        for (int i = 0; i < aVec->size() - 1; ++i) {
            res += findShortestPath((*aVec)[i], (*aVec)[i + 1]);
        }
        return res;
    }
};

int main() {
    int N, M, from, to, P, K;
    cin >> N >> M;
    Graph graph(N);
    for (int i = 0; i < M; ++i) {
        cin >> from >> to;
        graph.addEdge(from, to);
        graph.addEdge(to, from);
    }
    cin >> P;
    vector<int> a(P);
    for (int i = 0; i < P; ++i) {
        cin >> a[i];
    }
    graph.addA(a);
    cin >> K;
    vector<int> p(K);
    for (int i = 0; i < K; ++i) {
        cin >> p[i];
    }
    graph.addP(p);
    cout << graph.findFullShortestPath();
}