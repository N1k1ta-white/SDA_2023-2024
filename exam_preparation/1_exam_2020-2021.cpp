#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int N, M, x;
    cin >> N >> M;
    vector<int> numbers(N);
    for (int i = 0; i < N; i++) {
        cin >> numbers[i];
    }
    sort(numbers.begin(), numbers.end());
    for (int i = 0; i < M; i++) {
        cin >> x;
        auto iter = lower_bound(numbers.begin(), numbers.end(), x);
        cout << iter - numbers.begin() << " ";
    }
}
