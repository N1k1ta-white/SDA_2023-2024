#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

vector<int> disjoint;
vector<int> rankSet;

void reset() {
    for (int &i : disjoint) {
        i = -1;
    }
}

void checkSet(int x) {
    if (disjoint[x] == -1) {
        disjoint[x] = x;
        rankSet[x] = 1;
    }
}

int find(int x) {
    checkSet(x);
    if (disjoint[x] != x) {
        disjoint[x] = find(disjoint[x]);
    }
    return disjoint[x];
}

void Union(int x, int y) {
    checkSet(x);
    checkSet(y);
    int root_y = find(y), root_x = find(x);
    if (root_y == root_x) {
        return;
    }
    if (rankSet[root_x] < rankSet[root_y]) {
        swap(root_y, root_x);
    }
    disjoint[root_y] = root_x;
    rankSet[root_x] += rankSet[root_y];
}

struct Path {
    int to;
    int from;
    int cost;

    Path(int i, int i1, int i2) : to(i), from(i1), cost(i2) {
    }

    Path() = default;

    bool operator<(const Path& pt) const {
        return cost < pt.cost;
    }
};

pair<int, int> check(const vector<Path>& paths, int min, int N) {
    int counter = 0, max = INT_MIN;
    reset();
    for (const Path& curr : paths) {
        if (curr.cost >= min) {
            if (find(curr.to) != find(curr.from)) {
                Union(curr.to, curr.from);
                counter++;
                if (curr.cost > max) {
                    max = curr.cost;
                }
                if (counter + 1 == N) {
                    break;
                }
            }
        }
    }
    return {counter + 1, max};
}

int main() {
    int N, M, f, t, s, maxS = -1, minS = INT_MAX;
    cin >> N >> M;
    disjoint.resize(N, -1);
    rankSet.resize(N, -1);
    vector<Path> paths(M);
    for (int i = 0; i < M; ++i) {
        cin >> f >> t >> s;
        paths[i] = {f - 1, t - 1, s};
        if (maxS < s) {
            maxS = s;
        }
        if (minS > s) {
            minS = s;
        }
    }
    int max = maxS, min = minS, curr_max;
    for (int i = minS; i < maxS; ++i) {
        curr_max = check(paths, i, N);
        if (curr_max != -1) {
            if (max - min > curr_max - i) {
                max = curr_max;
                min = i;
            }
        }
    }
    cout << min << " " << max;
}