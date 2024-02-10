#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <queue>
using namespace std;

int main() {
    int K, T, B, N, num;
    cin >> K >> T >> B >> N;
    priority_queue<int, vector<int>, greater<>> pq;
    for (int i = 0; i < N; ++i) {
        cin >> num;
        pq.push(num);
        if (!((i + 1) % T)) {
            if (B) {
                B--;
                for (int j = 0; j < K; ++j) {
                    cout << pq.top() << " ";
                    pq.pop();
                }
            }
        }
    }
    while (B) {
        B--;
        for (int j = 0; j < K; ++j) {
            cout << pq.top() << " ";
            pq.pop();
        }
    }
}