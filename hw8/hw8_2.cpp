#include <iostream>
#include <set>
#include <queue>
#include <unordered_map>

using namespace std;

struct Moment {
    int time;
    int ind;
    bool exit;
};

class Comparator {
public:
    bool operator()(const Moment& m1, const Moment& m2) {
        if (m1.time == m2.time) {
            return m1.exit > m2.exit;
        }
        return m1.time > m2.time;
    }
};

class ComparatorInt {
public:
    bool operator()(int a, int b) {
        return a > b;
    }
};

int main() {
    int N, a, l, table = 0, T;
    cin >> N;
    priority_queue<int, vector<int>, ComparatorInt> emptyTables;
    priority_queue<Moment, vector<Moment>, Comparator> pq;
    for (int i = 0; i < N; ++i) {
        cin >> a >> l;
        pq.push({a, i, false});
        pq.push({l, i, true});
    }
    cin >> T;
    unordered_map<int, int> person;
    while (!pq.empty()) {
        if (!pq.top().exit) {
            if (emptyTables.empty()) {
                person[pq.top().ind] = table++;
            } else {
                person[pq.top().ind] = emptyTables.top();
                emptyTables.pop();
            }
            pq.pop();
        } else {
            emptyTables.push(person[pq.top().ind]);
            pq.pop();
        }
    }
    cout << person[T];
}