#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> buildSuffixArray(const string& str) {
    int n = str.size();
    vector<int> p(n), c(n);

    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = {str[i], i};
    }
    sort(a.begin(), a.end());

    for (int i = 0; i < n; ++i) {
        p[i] = a[i].second;
    }

    c[p[0]] = 0;
    for (int i = 1; i < n; ++i) {
        c[p[i]] = c[p[i - 1]] + (a[i].first != a[i - 1].first);
    }

    int k = 0;
    while ((1 << k) < n) {
        vector<pair<pair<int, int>, int>> a(n);
        for (int i = 0; i < n; ++i) {
            a[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
        }
        sort(a.begin(), a.end());

        for (int i = 0; i < n; ++i) {
            p[i] = a[i].second;
        }

        c[p[0]] = 0;
        for (int i = 1; i < n; ++i) {
            c[p[i]] = c[p[i - 1]] + (a[i].first != a[i - 1].first);
        }

        ++k;
    }

    return p;
}

vector<int> buildLCP(const string& str, const vector<int>& p) {
    int n = str.size();
    vector<int> rank(n);
    for (int i = 0; i < n; ++i) {
        rank[p[i]] = i;
    }

    int k = 0;
    vector<int> lcp(n - 1, 0);

    for (int i = 0; i < n; ++i) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }

        int j = p[rank[i] + 1];
        while (i + k < n && j + k < n && str[i + k] == str[j + k]) {
            ++k;
        }

        lcp[rank[i]] = k;
        if (k > 0) {
            --k;
        }
    }

    return lcp;
}

int longestCommonSubstringLength(const string& str1, const string& str2) {
    string combined = str1 + "#" + str2;
    vector<int> suffixArray = buildSuffixArray(combined);
    vector<int> lcp = buildLCP(combined, suffixArray);

    int maxLen = 0;
    for (int i = 0; i < lcp.size(); ++i) {
        if ((suffixArray[i] < str1.size() && suffixArray[i + 1] > str1.size()) ||
            (suffixArray[i] > str1.size() && suffixArray[i + 1] < str1.size())) {
            maxLen = max(maxLen, lcp[i]);
        }
    }

    return maxLen;
}

int main() {
    string str1, str2;

    cin >> str1;
    cin >> str2;

    int length = longestCommonSubstringLength(str1, str2);

    cout << length << endl;

    return 0;
}
