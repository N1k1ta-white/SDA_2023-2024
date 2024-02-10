#include <queue>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> disjoint;
vector<int> rankSet;

int find(int x) {
    if (disjoint[x] == -1) {
        disjoint[x] = x;
    }
    if (disjoint[x] != x) {
        disjoint[x] = find(disjoint[x]);
    }
    return disjoint[x];
}

void Union(int x, int y) {
    int x_root = find(x),
            y_root = find(y);
    if (x_root != y_root) {
        disjoint[y_root] = disjoint[x_root];
        rankSet[x_root] += rankSet[y_root];
    }
}

int main() {
    int N, Q, divider, p1, p2, root, res = 0;
    cin >> N >> Q >> divider;
    disjoint.resize(N + 1, -1);
    rankSet.resize(N + 1, 1);
    for (int i = 0; i < Q; ++i) {
        cin >> p1 >> p2;
        Union(p1, p2);
    }

    for (int i = 0; i < N; ++i) {
        root = find(i);
        if (root != N) {
            if (rankSet[root] % divider == 0) {
                res++;
            }
            Union(N, root);
        }
    }
    cout << res;
}