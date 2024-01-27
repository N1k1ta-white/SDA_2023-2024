#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

    class Solution {

        void insertionSort(vector<int>& arr) {
            for (int i = 1; i < arr.size(); i++) {
                int key = arr[i];
                int j = i - 1;
                while (j >= 0 && key < arr[j]) {
                    arr[j + 1] = arr[j];
                    j--;
                }
                arr[j + 1] = key;
            }
        }

    public:
        vector<int> sortArrayByParityII(vector<int>& arr) {
            vector<int> res;
            insertionSort(arr);
            int posEven = 0;
            int posOdd = 0;
            for (int i = 0; i < arr.size() / 2; i++) {
                for (;posEven < arr.size(); ++posEven) {
                    if (!(arr[posEven] % 2)) {
                        break;
                    }
                }
                for (;posOdd < arr.size(); ++posOdd) {
                    if (arr[posOdd] % 2) {
                        break;
                    }
                }
                res.push_back(arr[posEven++]);
                res.push_back(arr[posOdd++]);
            }
            return res;
        }
    };

int main() {
    Solution sol;
    vector<int> vec = {4,1,2,1};
    vector<int> res = sol.sortArrayByParityII(vec);
}