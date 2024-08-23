#include <iostream>

using namespace std;

class Solution {

    class Fraction {
        int numerator;
        int denominator;

        static int findGreaterCommonDivisor(int a, int b) {
            if (a < 0) {
                a *= -1;
            }
            if (b < 0) {
                b *= -1;
            }
            if (a < b) {
                swap(a, b);
            }
            while (b != 0) {
                int temp = b;
                b = a % b;
                a = temp;
            }
            return a;
        }

        int findLeastCommonMultiple(const Fraction& fraction) const {
            return (denominator * fraction.denominator) /
                   findGreaterCommonDivisor(denominator, fraction.denominator);
        }

        void changeDenominator(int newDenominator) {
            numerator *= newDenominator / denominator;
            denominator = newDenominator;
        }

        static int getNumeratorAfterChangeDenominator(const Fraction& fraction, int newDenominator) {
            return fraction.numerator * (newDenominator / fraction.denominator);
        }

        void setOneDenominatorForBoth(Fraction& fraction) {
            int commonDenominator = findLeastCommonMultiple(fraction);
            this->changeDenominator(commonDenominator);
            fraction.changeDenominator(commonDenominator);
        }

        static int getPosOfSlash(const string& str) {
            int pos = 0;
            while (str[pos] != '/') {
                pos++;
            }
            return pos;
        }

        void init(int numerator, int denominator) {
            this->denominator = denominator;
            this->numerator = numerator;
        }

        void optimizeFraction() {
            int gcd = findGreaterCommonDivisor(numerator, denominator);
            numerator /= gcd;
            denominator /= gcd;
        }

    public:

        Fraction(int numerator, int denominator) {
            init(numerator, denominator);
        }

        Fraction(const string& str) {
            int pos = getPosOfSlash(str);
            string numeratorStr = str.substr(0, pos);
            string denominatorStr = str.substr(pos + 1, str.size() - pos - 1);
            init(stoi(numeratorStr), stoi(denominatorStr));
        }

        int getNumerator() const {
            return numerator;
        }

        int getDenominator() const {
            return denominator;
        }

        void adding(Fraction& fraction) {
            if (denominator != fraction.denominator) {
                setOneDenominatorForBoth(fraction);
            }
            numerator += fraction.numerator;
        }

        void subtraction(Fraction& fraction) {
            if (denominator != fraction.denominator) {
                setOneDenominatorForBoth(fraction);
            }
            numerator -= fraction.numerator;
        }

        string toString() {
            optimizeFraction();
            return to_string(numerator) + "/" + to_string(denominator);
        }
    };

    static Fraction parseFractionFromSubstring(const string& str, int start, int end) {
        string fracString = str.substr(start, end);
        return {fracString};
    }

public:
    string fractionAddition(string expression) {
        int prev = 0;
        Fraction res(0,1);
        for (int i = 1; i < expression.size(); ++i) {
            if (expression[i] == '+' || expression[i] == '-') {
                Fraction tempFraction = parseFractionFromSubstring(expression, prev, i);
                res.adding(tempFraction);
                prev = i;
            }
        }
        Fraction tempFraction = parseFractionFromSubstring(expression, prev, expression.size());
        res.adding(tempFraction);
        return res.toString();
    }
};

int main() {
    Solution solution;
    cout << solution.fractionAddition("-1/2+3/4-6/8");
//    cout << solution.fractionAddition("-1/2+1/2+1/3");
}