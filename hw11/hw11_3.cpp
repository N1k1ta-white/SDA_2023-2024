#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <queue>
#include <climits>

#define ll long long

using namespace std;

struct Path {
    ll to;
    ll cost;
    ll maxKg;
};

struct ComparatorByTime {
    bool operator()(const Path& p1, const Path& p2) const {
        if (p1.cost == p2.cost) {
            if (p1.maxKg == p2.maxKg) {
                return p1.to > p2.to;
            }
            return p1.maxKg > p2.maxKg;
        }
        return p1.cost > p2.cost;
    }
};

bool searchByWeight(ll from, ll to, const vector<set<Path, ComparatorByTime>>& edges, ll maxTime, ll maxKg) {
    priority_queue<Path, vector<Path>, ComparatorByTime> pq;
    vector<bool> visited(edges.size(), false);
    pq.push({ from, 0 , 0});
    Path curr;
    while (!pq.empty()) {
        curr = pq.top();
        pq.pop();
        if (visited[curr.to]) {
            continue;
        }
        visited[curr.to] = true;
        if (curr.to == to && curr.cost <= maxTime) {
            return true;
        } else if (curr.cost > maxTime) {
            break;
        }
        for (Path el : edges[curr.to]) {
            if (!visited[el.to] && el.maxKg <= maxKg)
                pq.push({el.to, el.cost + curr.cost, (el.maxKg < curr.maxKg ? curr.maxKg : el.maxKg)});
        }
    }
    return false;
}

void binarySearchDijkstra(ll start, ll end, const vector<set<Path, ComparatorByTime>>& edges, ll maxTime, ll& best,
                         ll from, ll to) {
    if (start <= end) {
        ll mid = start + (end - start) / 2;
        if (!searchByWeight(from, to, edges, maxTime, mid)) {
            start = mid + 1;
        } else {
            if (best > mid) {
                best = mid;
            }
            end = mid - 1;
        }
        binarySearchDijkstra(start, end, edges, maxTime, best, from, to);
    }
}

int main() {
    ll N, M, start, end, val, time, kg, maxKg = -1;
    vector<set<Path, ComparatorByTime>> edges;
    cin >> N >> M >> time;
    for (int i = 0; i < N; ++i) {
        set<Path, ComparatorByTime> set;
        edges.push_back(set);
    }
    for (int i = 0; i < M; ++i) {
        cin >> start >> end >> kg >> val;
        if (maxKg < kg) {
            maxKg = kg;
        }
        edges[start - 1].insert({end - 1, val, kg});
    }
    ll res = LONG_LONG_MAX;
    binarySearchDijkstra(1, maxKg, edges, time, res, 0, N - 1);
    cout << (res == LONG_LONG_MAX ? -1 : res);
};