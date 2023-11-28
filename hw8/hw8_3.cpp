#include <iostream>
#include <queue>

using namespace std;

struct Moment {
    int passengers;
    int time;
    bool isExit;

    int getPassengers() const {
        return (isExit ? passengers * -1 : passengers);
    }
};

class Comparator {
public:
    bool operator()(const Moment& m1, const Moment& m2) {
        return m1.time > m2.time;
    }
};

int main() {
    int Q, N, C, k, x, y, res;
    cin >> Q;
    for (int i = 0; i < Q; ++i) {
        cin >> N >> C;
        res = 0;
        priority_queue<Moment, deque<Moment>, Comparator> pq;
        for (int j = 0; j < N; ++j) {
            cin >> k >> x >> y;
            pq.push({k, x, false});
            pq.push({k, y, true});
        }
        while (!pq.empty()) {
            res += pq.top().getPassengers();
            pq.pop();
            if (res > C) {
                cout << "0" << endl;
                break;
            }
        }
        if (pq.empty()) {
            cout << "1" << endl;
        }
    }
};