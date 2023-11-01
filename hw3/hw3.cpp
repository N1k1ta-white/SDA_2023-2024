#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

#define vec std::vector<int>
#define ll long long

ll countGroups(vec& arr, ll count, ll target) {
    ll iter = -1, currentSum = 0, countGroups = 0;
    while (iter + 1 < count) {
        currentSum += arr[++iter];
        if (arr[iter] > target)
            return LONG_LONG_MAX;
        if (currentSum > target) {
            countGroups++;
            currentSum = 0;
            iter--;
        }
    }
    return ++countGroups;
}

ll findGruopMax(vec& arr, ll l, ll count, ll groupsCount, ll r) {
    ll mid, max = 0, groups;
    while (r >= l) {
        mid = (r - l) / 2 + l;
        groups = countGroups(arr, count, mid);
        if (groups <= groupsCount) {
            max = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    return max;
}

int main() {
    ll count, groupsCount, sumNumb = 0;
    std::cin >> count >> groupsCount;
    vec arr(count);
    for (int i = 0; i < count; ++i) {
        std::cin >> arr[i];
        sumNumb += arr[i];
    }
    if (groupsCount == count) {
        std::cout << arr[count - 1];
        return 0;
    }
    std::cout << findGruopMax(arr, 1, count, groupsCount, sumNumb);
}
