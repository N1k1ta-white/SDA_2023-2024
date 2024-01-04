#include <iostream>
#include <vector>

using namespace std;

vector<int> disjoint;
vector<int> rankSet;

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

int main() {
    int N, M, p, q, Q, type;
    cin >> N >> M;
    disjoint.resize(N + 1, -1);
    rankSet.resize(N + 1, -1);
    for (int i = 0; i < M; ++i) {
        cin >> p >> q;
        Union(p, q);
    }
    cin >> Q;
    for (int i = 0; i < Q; ++i) {
        cin >> type >> p >> q;
        if (type == 1) {
            cout << (find(p) == find(q));
        } else {
            Union(p, q);
        }
    }
}