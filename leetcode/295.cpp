#include <queue>
#include <iostream>

using namespace std;

class MedianFinder {
    priority_queue<int, vector<int>, less<>> pqGreat;
    priority_queue<int, vector<int>, greater<>> pqLess;
    int size;
public:
    MedianFinder() : size(0) {
    }

    void addNum(int num) {
        if (pqGreat.empty()) {
            pqGreat.push(num);
        }
        else {
            if (num > pqGreat.top()) {
                pqLess.push(num);
            } else {
                pqGreat.push(num);
            }

            if (pqLess.size() - pqGreat.size() == 2) {
                pqGreat.push(pqLess.top());
                pqLess.pop();
            } else if (pqGreat.size() - pqLess.size() == 1 || pqGreat.size() - pqLess.size() == 2) {
                pqLess.push(pqGreat.top());
                pqGreat.pop();
            }
        }
        size++;
    }

    double findMedian() {
        return !(size % 2) ? (pqGreat.top() + pqLess.top()) / 2.0 : (pqLess.empty() ? pqGreat.top() : pqLess.top());
    }
};

int main() {
    MedianFinder med;
    med.addNum(1);
    med.addNum(2);
    med.addNum(3);
    med.addNum(4);
    med.addNum(5);
    med.addNum(6);
    med.addNum(7);
    med.addNum(8);
    med.addNum(9);
    med.addNum(10);
//    med.addNum(1);
    cout << med.findMedian() << endl;
//    med.addNum(2);
//    med.addNum(3);
//    cout << med.findMedian() << endl;
}