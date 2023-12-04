#include <iostream>
#include <string>
#include <list>

using namespace std;

class Searcher {
    string word;
    list<int> currentWord;
    int res;
public:
    Searcher(const string& word, string curr) {
        this->word = word;
        for (char el : curr) {
            currentWord.push_back(el);
        }
        res = (word == curr ? 1 : 0);
    }

    void addChar(char ch) {
        currentWord.push_back(ch);
        currentWord.pop_front();
        int i = 0;
        for (auto it = currentWord.begin(); it != currentWord.end(); ++it, ++i) {
            if (word[i] != *it) {
                return;
            }
        }
        res++;
    }

    int getRes() const  {
        return res;
    }
};

int main() {
    string word, text;
    cin >> word >> text;
    Searcher searcher(word, text.substr(0, word.length()));
    for (int i = word.length(); i < text.length(); ++i) {
        searcher.addChar(text[i]);
    }
    cout << searcher.getRes();
}