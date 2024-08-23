#include <iostream>
#include <set>
#include <vector>
#include <queue>

using namespace std;

class KthLargest {
    priority_queue<int, vector<int>, greater<>> pq;
    int k;
public:
    KthLargest(int k, vector<int>& nums) : k(k) {
        for (int& num : nums) {
            pq.push(num);
        }
        while (pq.size() > k) {
            pq.pop();
        }
    }

    int add(int val) {
        if (pq.size() < k) {
            pq.push(val);
        } else if (pq.top() < val) {
            pq.push(val);
            pq.pop();
        }
        return pq.top();
    }
};

int main() {
    vector<int> vec = {0};
    KthLargest k(2, vec);
    cout << k.add(-1);
    cout << k.add(1);
    cout << k.add(-2);
    cout << k.add(-4);
    cout << k.add(3);
}