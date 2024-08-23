#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {

    static constexpr int PRICE = 5;
    static constexpr int PRICE_INDEX = 0;
    static constexpr int BANKNOTE10 = 10;
    static constexpr int BANKNOTE10_INDEX = 1;
    static constexpr int BANKNOTE20 = 20;
public:
    bool lemonadeChange(vector<int>& bills) {
        vector<int> cashbox(2, 0);
        for (int banknote : bills) {
            switch (banknote) {
                case PRICE:
                    cashbox[PRICE_INDEX]++;
                    break;
                case BANKNOTE10:
                    if (!cashbox[PRICE_INDEX]) {
                        return false;
                    }
                    cashbox[PRICE_INDEX]--;
                    cashbox[BANKNOTE10_INDEX]++;
                    break;
                case BANKNOTE20:
                    if (cashbox[PRICE_INDEX] && cashbox[BANKNOTE10_INDEX]) {
                        cashbox[PRICE_INDEX]--;
                        cashbox[BANKNOTE10_INDEX]--;
                    } else if (cashbox[PRICE_INDEX] >= (BANKNOTE20 / PRICE - 1)) {
                        cashbox[PRICE_INDEX] -= (BANKNOTE20 / PRICE - 1);
                    } else {
                        return false;
                    }
                    break;
                default:
                    return false;
            }
        }
        return true;
    }
};

int main() {

}