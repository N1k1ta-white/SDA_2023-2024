#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> nums(m);
    unordered_map<int, bool> num;
    for (int i = 0; i < m; ++i) {
        cin >> nums[i];
        num[nums[i]] = true;
    }
    int low_bound = 1;

    for (int it = 0; it < m; ++it) {
        for (int i = low_bound; i < nums[it]; ++i) {
            if (!num.count(i))
                cout << i << " ";
        }
        cout << nums[it] << " ";
        if (low_bound <= nums[it])
            low_bound = nums[it] + 1;
    }
    for (int i = low_bound; i <= n; ++i)
        cout << i << " ";
}