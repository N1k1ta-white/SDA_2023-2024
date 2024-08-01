#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<string> commonChars(vector<string>& words) {
    int letters[26] {0};
    for (string &word : words) {
        for (char &ch : word) {
            letters[ch - 'a']++;
        }
    }
    vector<string> res;
    int size = words.size();
    for (int i = 0; i < 26; i++) {
            while((letters[i] - size) >= 0) {
                res.push_back(string(1, char('a' + i)));
                letters[i] -= words.size();
            }
    }
    return res;
}


bool isPossibleDivide(vector<int>& nums, int k) {
    int size = nums.size();
    if (size % k != 0) {
        return false;
    }

    map<int, int> map;
    for (int &n : nums) {
        map[n]++;
    }
    int iter = size / k;
    int prev, l;

    for (int i = 0; i < iter; i++) {
        l = 0;
        prev = -1;
        bool rm = false;
        for (auto it = map.begin(); l < k; l++, it++) {
            if (rm) {
                rm = false;
                it--;
            }
            if (prev == it->first || it == map.end() || prev != -1 && abs(prev - it->first) > 1) {
                return false;
            } else {
                it->second--;
                prev = it->first;
                if (it->second == 0) {
                    auto tmp = it;
                    tmp++;
                    map.erase(it);
                    it = tmp;
                    rm = true;
                }
            }
            if (it == map.end()) {
                break;
            }
        }
    }

    return true;
}


int main() {
//    vector<string> words = {"bella", "label", "roller"};
//    commonChars(words);

    vector<int> nums = {0, 0};
    int k = 2;
    cout << isPossibleDivide(nums, k);
}