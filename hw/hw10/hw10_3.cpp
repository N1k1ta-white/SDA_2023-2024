#include <bits/stdc++.h>

using namespace std;

unordered_map<char, set<char>> graph;
bool visited[CHAR_MAX + 1];

stack<char> letters;

void dfs(char value) {
    visited[value] = true;
    if(graph.count(value)) {
        for (char element : graph[value]) {
            if (!visited[element]) {
                dfs(element);
            }
        }
    }
    letters.push(value);
}

void topologicalSort() {
    for (pair<char, set<char>> element : graph) {
        if (!visited[element.first]) {
            dfs(element.first);
        }
    }
}

int main() {
    size_t N;
    cin >> N;

    string firstWord, secondWord;
    cin >> firstWord;
    for (int i = 1; i < N; ++i) {
        cin >> secondWord;
        for (int j = 0; j < firstWord.size() && j < secondWord.size(); ++j) {
            if (firstWord[j] != secondWord[j]) {
                graph[firstWord[j]].insert(secondWord[j]);
                break;
            }
        }
        firstWord = secondWord;
    }

    topologicalSort();
    while (!letters.empty()) {
        cout << letters.top() << " ";
        letters.pop();
    }
}