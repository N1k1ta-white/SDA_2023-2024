#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string kthDistinct(vector<string>& arr, int k) {
        // first - count    second - first pos
        unordered_map<string, int> um;
        for (string& str : arr) {
            um[str]++;
        }
        for (string& str : arr) {
            if (um[str] == 1) {
                k--;
                if (k == 0) {
                    return str;
                }
            }
        }
        return "";
    }
};

int main() {
    Solution solution;
    vector<string> vec = {"d","b","c","b","c","a"};
    cout << solution.kthDistinct(vec, 2);
}