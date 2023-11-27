#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <unordered_map>
#include <climits>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, med, medInd;
    unordered_map<int, int> polar;
    int low = INT_MAX, height = INT_MIN;
    cin >> n >> med;
    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
        if (numbers[i] == med)
            medInd = i;
    }

    int temp = 0;
    for (int i = medInd + 1; i < n; ++i) {
        if (numbers[i] > med)
            temp++;
        else
            temp--;
        polar[i] = temp;
    }

    temp = 0;
    for (int i = medInd - 1; i >= 0; --i) {
        if (numbers[i] > med)
            temp--;
        else
            temp++;
        polar[i] = temp;
    }

    int res = 0;
    unordered_map<int, pair<int, int>> counter;
    for (int i = 0; i < n; ++i) {
        if (low > polar[i])
            low = polar[i];
        if (height < polar[i])
            height = polar[i];
        if (i == medInd) {
            res++;
//            cout << "mid ";
            continue;
        }
        if (i < medInd) {
            counter[polar[i]].first++;
        }
        else
            counter[polar[i]].second++;
//        cout << polar[i] << " ";
    }

    for (int i = low; i <= height; ++i) {
        if (counter.count(i)) {
            if (i == 0) {
                res += counter[i].second + counter[i].first;
            }
            res += counter[i].second * counter[i].first;
        }
    }

    cout << res;
}