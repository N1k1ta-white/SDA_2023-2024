#include <iostream>
#include <climits>
#include <unordered_map>

using namespace std;

int main() {
    int N, temp, min = INT_MAX;
    unordered_map<int, int> un;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> temp;
        if (!un.count(temp)) {
            un[temp] = i;
        } else {
            if (min > i - un[temp]) {
                min = i - un[temp];
            }
            un[temp] = i;
        }
    }
    cout << min;
}