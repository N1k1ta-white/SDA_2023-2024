#include <queue>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int binarySearch(int start, int end, int num, vector<pair<int, int>>& vec) {
    if (start <= end) {
        int mid = start + (end - start) / 2;
        if (vec[mid].first < num) {
            return binarySearch(mid + 1, end, num, vec);
        } else if (vec[mid].first > num) {
            return binarySearch(start, mid - 1, num, vec);
        } else {
            return mid;
        }
    } else {
        return end;
    }
}

int main() {
    int N, stock, t;
    cin >> N;
    vector<pair<int, int>> time(N);
    unordered_map<int, int> um;
    int max = -1;
    for (int i = 0; i < N; ++i) {
        cin >> stock >> t;
        um[stock]++;
        if (um[stock] >= um[max]) {
            max = stock;
        }
        time[i] = {t, max};
    }
    int Q, num;
    cin >> Q;
    for (int i = 0; i < Q; ++i) {
        cin >> num;
        if (num < time[0].first) {
            cout << -1 << endl;
        } else {
            int pos = binarySearch(0, N - 1, num, time);
            cout << time[pos].second << endl;
        }
    }
}