#include <queue>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

const int P = 4 * 10e9 + 7;
const int BASE = 10;

unsigned long long hashing(vector<int>& numbers) {
    int power = 1;
    int resHash = 0;
    for (int number : numbers) {
        resHash += number * power;
        resHash %= P;
        if (resHash < 0) {
            resHash += P;
            resHash %= P;
        }
        power *= BASE;
        power %= P;
        if (power < 0) {
            power += P;
            power %= P;
        }
    }
    return resHash;
}

int main() {
    int N, M;
    cin >> N >> M;
    unordered_map<unsigned long long, int> exist;
    int countUnique = 0;
    vector<int> row(M);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> row[j];
        }
        int hash = hashing(row);
        exist[hashing(row)]++;
    }
    for (auto el : exist) {
        if (el.second == 1) {
            countUnique++;
        }
    }
    cout << countUnique;
}