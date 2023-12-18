#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <queue>

using namespace std;

unordered_map<int, int> wait;

// first to
// second value
// pair<int, int>

struct Comparator {
    bool operator()(const pair<int, int>& p1, const pair<int, int>& p2) {
        if (p1.second == p2.second) {
            return p1.first > p2.first;
        }
        return p1.second > p2.second;
    }
};

int search(int from, int to, const vector<set<pair<int, int>>>& edges) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, Comparator> pq;
    vector<bool> visited(edges.size(), false);
    vector<int> path(edges.size(), INT_MAX);
    pq.push({ from, 0 });
    pair<int, int> curr;
    int currPath;
    while (!pq.empty()) {
        curr = pq.top();
        pq.pop();
        if (visited[curr.first])
            continue;
        visited[curr.first] = true;
        if (curr.first == to)
            return path[to];
        for (pair<int, int> el : edges[curr.first]) {
            currPath = el.second + curr.second;
            if (path[el.first] > currPath)
                path[el.first] = currPath;
            pq.emplace(el.first, currPath + (wait[el.first] - (currPath % wait[el.first] == 0 ? wait[el.first] : currPath % wait[el.first])));
        }
    }
    return -1;
}

int main() {
    int V, E, start, end, val, to, from;
    vector<set<pair<int, int>>> edges;
    cin >> V >> E >> from >> to;
    for (int i = 0; i < V; ++i) {
        set<pair<int, int>> set;
        edges.push_back(set);
    }
    for (int i = 0; i < V; ++i) {
        cin >> wait[i];
    }
    for (int i = 0; i < E; ++i) {
        cin >> start >> end >> val;
        edges[start].insert({end, val});
        edges[end].insert({start, val});
    }
    cout << search(from, to, edges);
};