#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <queue>
using namespace std;

int main() {
    int N, num, start = 0, maxSize = 0;
    cin >> N;
    unordered_map<int, int> position;
    for (int i = 0; i < N; ++i) {
        cin >> num;
        if (!position.count(num) || position[num] < start) {
            position[num] = i;
        } else {
            int size = i - start;
            if (maxSize < size) {
                maxSize = size;
            }
            start = position[num] + 1;
            position[num] = i;
        }
    }

    cout << max(maxSize, N - start);
}