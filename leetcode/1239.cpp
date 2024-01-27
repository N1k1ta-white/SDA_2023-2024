#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {

    unordered_map<int, int> results;

    class Mask {
        int length = 0;
        long mask = 0;


        bool add(char ch) {
            long copy = mask;
            int temp = 1;
            temp = temp << (ch - 'a');
            mask |= temp;
            return copy ^ mask;
        }

    public:
        Mask() = default;

        bool add(const string& str) {
            for (char ch : str) {
                if (!add(ch)) {
                    return false;
                }
            }
            length += str.size();
            return true;
        }

        int getMask() const {
            return mask;
        }

        int getLength() const {
            return length;
        }
    };

    int recursiveSearch(vector<string>& arr, int start, Mask mask) {
        if (!results.count(mask.getMask())) {
            bool ans = mask.add(arr[start]);
            int max = mask.getLength();
            if (ans) {
                int curr;
                for (int i = start + 1; i < arr.size(); ++i) {
                    curr = recursiveSearch(arr, i, mask);
                    if (curr > max) {
                        max = curr;
                    }
                }
                results[mask.getMask()] = max;
            } else {
                return 0;
            }
        }
        return results[mask.getMask()];
    }

public:

    int maxLength(vector<string>& arr) {
        int max = 0, curr;
        Mask mask;
        for (int i = 0; i < arr.size(); ++i) {
            curr = recursiveSearch(arr, i, mask);
            if (curr > max) {
                max = curr;
            }
        }
        return max;
    }

};

int main() {
    Solution sol;
    vector<string> vec = {"ab","ba","cd","dc","ef","fe","gh","hg","ij","ji","kl","lk","mn","nm","op","po"};
    cout << sol.maxLength(vec);
}