#include <iostream>
#include <vector>
#define VI vector<int>
#define ll long long
using namespace std;

bool isPossible(VI& arr, ll time, ll target) {
    ll sum = 0;
    for (int i = 0; i < arr.size(); ++i) {
        sum += time / arr[i];
        if (sum >= target)
            return true;
    }
    return false;
}

int main() {
    int N, target;
    cin >> N >> target;
    VI arr(N);
    for (int i = 0; i < N; ++i)
        cin >> arr[i];
    ll l = 1, r = LLONG_MAX;
    while (l <= r) {
        ll mid = l + (r + l) / 2;
        if (isPossible(arr, mid, target))
            r = mid - 1;
        else
            l = mid + 1;
    }
    cout << l;
}
