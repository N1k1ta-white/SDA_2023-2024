#include <iostream>
#include <queue>
#include <cmath>

#define PLL pair<long, long>

using namespace std;


class Distance {
    PLL pos;
    static PLL dest;
public:
    Distance(PLL p) {
        pos = p;
    }

    const PLL& getPos() const {
        return pos;
    }

    static void initDest(PLL destin) {
        dest = destin;
    }

    double getDist() const {
        return sqrt(pow(pos.first - dest.first, 2) + pow(pos.second - dest.second, 2));
    }

    void print() const {
        cout << pos.first << " " << pos.second << endl;
    }
};

PLL Distance::dest = {0, 0};


class Comparator {
public:
    bool operator()(Distance& pos1, Distance& pos2) {
        double d1 = pos1.getDist(), d2 = pos2.getDist();
        if (abs(d1 - d2) < 0.00001) {
            return (pos1.getPos().first == pos2.getPos().first ?
                    pos1.getPos().second > pos2.getPos().second : pos1.getPos().first > pos2.getPos().first);
        }
        return pos1.getDist() > pos2.getDist();
    }
};

int main() {
    int x, y, N, K;
    cin >> x >> y >> N >> K;
    Distance::initDest({x, y});
    priority_queue<Distance, vector<Distance>, Comparator> pq;
    for (int i = 0; i < N; ++i) {
        cin >> x >> y;
        Distance temp({x, y});
        pq.push(temp);
    }
    for (int i = 0; i < K; ++i) {
        pq.top().print();
        pq.pop();
    }
}