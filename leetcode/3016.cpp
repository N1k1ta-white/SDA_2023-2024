#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumPushes(string word) {
        vector<int> letters(26, 0);
        for (char& i : word) {
            letters[i - 'a']++;
        }
        int res = 0;
        sort(letters.begin(), letters.end(),
             [](auto a, auto b) {
                 return a > b;
        });
        for (int i = 0; i < letters.size() && letters[i]; ++i) {
            res += letters[i] + (letters[i] * (i / 8));
        }
        return res;
    }
};

int main() {
    Solution solution;
    string word = "aabbccddeeffgghhiiiiii";
    cout << solution.minimumPushes(word);
}