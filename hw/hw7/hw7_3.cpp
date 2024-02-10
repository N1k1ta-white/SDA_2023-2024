#include <iostream>
#include <climits>
#include <set>
#include <vector>

using namespace std;



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int q, temp, min = INT_MAX;
    vector<int> nums, res;
    set<int> arr;

    cin >> q;
    arr.insert(0);
    for (int i = 0; i < q; ++i) {
        cin >> temp;
        arr.insert(temp);

        auto iter = arr.find(temp);
        auto iter2 = iter;
        if (++iter != arr.end()) {
            iter--;
            temp = *(iter++) ^ *iter;
            if (temp < min && temp != 0)
                min = temp;
        }

        if (iter2 != arr.begin()) {
            temp = *(iter2--) ^ *iter2;
            if (temp < min && temp != 0)
                min = temp;
        }

        res.push_back(min);
    }

    for (int i : res)
        cout << i << endl;
}