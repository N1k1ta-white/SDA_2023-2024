#include <queue>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

long long getPancakes(long long time, vector<long long>& vec) {
    long long res = 0;
    for (long long i = 0; i < vec.size(); ++i) {
        res += time / vec[i];
    }
    return res;
}

long long binary_search(long long start, long long end, long long num, vector<long long>& vec) {
    if (start > end) {
        return end + 1;
    }
    long long mid = start + (end - start) / 2;
    long long count = getPancakes(mid, vec);
    if (count < num) {
        return binary_search(mid + 1, end, num, vec);
    } else {
        return binary_search(start, mid - 1, num, vec);
    }
}

int main() {
    long long devider = 1, N, K;
    cin >> N >> K;
    vector<long long> t(K);
    for (long long i = 0; i < K; ++i) {
        cin >> t[i];
    }
    cout << binary_search(0, 1e13, N, t);
}