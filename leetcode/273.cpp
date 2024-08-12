#include <iostream>

using namespace std;

class Solution {
    static const string digitString[];
    static const string teenString[];
    static const string tenString[];
    static const string hundred;
    static const string thousand;
    static const string million;
    static const string billion;

public:
    string numberToWords(int num) {
        if (num < 10) {
            return digitString[num];
        } else if (num < 20) {
            return teenString[num - 10];
        } else if (num < 100) {
            return tenString[num / 10] + (num % 10 != 0 ? " " + numberToWords(num % 10) : "");
        } else if (num < 1000) {
            return numberToWords(num / 100) + hundred + (num % 100 != 0 ? " "
                                                                                + numberToWords(num % 100) : "");
        } else if (num < 1000000) {
            return numberToWords(num / 1000) + thousand + (num % 1000 != 0 ? " "
                                                                                + numberToWords(num % 1000) : "");
        } else if (num < 1000000000) {
            return numberToWords(num / 1000000) + million + (num % 1000000 != 0 ? " "
                                                                             + numberToWords(num % 1000000) : "");
        }
        else if (num > 1000000000) {
            return numberToWords(num / 1000000000) + billion + (num % 1000000000 != 0 ? " "
                                                                          + numberToWords(num % 1000000000) : "");
        }
    }
};

const string Solution::digitString[] = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
const string Solution::teenString[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
const string Solution::tenString[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
const string Solution::hundred = " Hundred";
const string Solution::thousand = " Thousand";
const string Solution::million = " Million";
const string Solution::billion = " Billion";

int main() {
    Solution solution;
    cout << solution.numberToWords(INT_MAX);
}