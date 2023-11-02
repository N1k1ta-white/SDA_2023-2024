#include <iostream>
#include <stack>
#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

using vec = vector<int>;

class Gate {
    vec res;
    deque<int> pos;
public:
    void add(int numb) {
        if (numb > 0) {
            pos.push_back(numb);
        }
        else {
            numb *= -1;
            while (!pos.empty()) {
                if (numb < pos.back())
                    return;
                else if (numb == pos.back()) {
                    pos.pop_back();
                    return;
                }
                pos.pop_back();
            }
            res.push_back(numb * -1);
        }
    }
    void print() {
        while (!pos.empty()) {
            res.push_back(pos.front());
            pos.pop_front();
        }
        for (int re : res)
            cout << re << " ";
    }
};

int main() {
    int n, hero;
    std::cin >> n;
    Gate gate;
    for (int i = 0; i < n; ++i) {
        std::cin >> hero;
        gate.add(hero);
    }
    gate.print();
}