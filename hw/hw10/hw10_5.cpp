#include <iostream>
#include <set>
#include <stack>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

struct Node {
    int start;
    int end;
    int cost;
};

class Graph {
    int N;
    unordered_map<int, vector<int>> edges;

    vector<int> getNodesByStartPoint(int start) {
        return edges[start];
    }

    int search(int start, int end) {
        std::queue<pair<int, int>> traversalOrder;
        traversalOrder.emplace(start, 1);
        bool* visited = new bool[N]{false};
        pair<int, int> curr;
        visited[start] = true;
        while (!traversalOrder.empty()) {
            curr = traversalOrder.front();
            traversalOrder.pop();
            for (int el : getNodesByStartPoint(curr.first)) {
                if (el == end) {
                    delete[] visited;
                    return curr.second;
                }
                if (visited[el])
                    continue;
                visited[el] = true;
                traversalOrder.emplace(el, curr.second + 1);
            }
        }
        delete[] visited;
        return -1;
    }
public:

    Graph(int N) {
        this->N = N;
    }

    void addNode(int start, int end, int cost) {
        if (cost == 2) {
            edges[start].push_back(++N);
            edges[N].push_back(end);
            edges[N].push_back(start);
            edges[end].push_back(N);
        } else if (cost == 1) {
            edges[start].push_back(end);
            edges[end].push_back(start);
        }
    }

    int findPath(int start, int end) {
        return search(start, end);
    }
};

int main() {
    int N, M, start, end, cost;
    cin >> N >> M;
    Graph gr(N);
    for (int i = 0; i < M; ++i) {
        cin >> start >> end >> cost;
        gr.addNode(start, end, cost);
    }
    cin >> start >> end;
    cout << gr.findPath(start, end);
}