#include <iostream>
#include <queue>

#define ll long long

using namespace std;

vector<ll> disjoint;
vector<ll> rankSet;

void checkSet(ll x) {
    if (disjoint[x] == -1) {
        disjoint[x] = x;
        rankSet[x] = 1;
    }
}

ll find(ll x) {
    checkSet(x);

    if (disjoint[x] != x) {
        disjoint[x] = find(disjoint[x]);
    }

    return disjoint[x];
}

void Union(ll x, ll y) {
    checkSet(x);
    checkSet(y);

    ll root_y = find(y), root_x = find(x);

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
    Path(ll i, ll i1, ll i2, ll i3, ll i4) : from(i), to(i1), effort(i2), cost(i3), ind(i4) {}

    Path() {}

    ll from;
    ll to;
    ll effort;
    ll cost;
    ll ind;
};

struct Comparator {
    bool operator()(const Path& pt1, const Path& pt2) {
        if (pt1.effort == pt2.effort) {
            if (pt1.cost == pt2.cost) {
                if (pt1.from == pt2.from) {
                    return pt1.to < pt2.to;
                }
                return pt1.from > pt2.from;
            }
            return pt1.cost < pt2.cost;
        }
        return pt1.effort > pt2.effort;
    }
};

int main() {
    ll N, M, a, b, c1, c2;

    cin >> N >> M;

    priority_queue<Path, vector<Path>, Comparator> pq;
    disjoint.resize(N + 1, -1);
    rankSet.resize(N + 1, -1);

    for (ll i = 0; i < M; ++i) {
        cin >> a >> b >> c1 >> c2;
        pq.emplace(a, b, c1, c2, i + 1);
    }

    Path curr;
    ll counter = 0;

    while (!pq.empty()) {
        curr = pq.top();
        pq.pop();

        if (find(curr.to) != find(curr.from)) {
            Union(curr.to, curr.from);
            cout << curr.ind << endl;
            counter++;
            if (counter + 1 == N) {
                break;
            }
        }
    }
}