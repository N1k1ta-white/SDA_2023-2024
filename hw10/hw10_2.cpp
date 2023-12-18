#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <set>
using namespace std;

class Graph{
    int V;
    unordered_map<int, vector<int>> edges;
    unordered_map<int, set<int>> groups;
    vector<bool> visited;
    vector<int> dist;
public:

    Graph(int V){
        this->V = V;
        dist = vector<int>(V + 1, 0);
        visited = vector<bool>(V + 1, false);
    }

    int BFS(int group){
        int v = *(groups[group].begin());
        queue<int> q;
        q.push(v);
        dist[v] = 0;
        visited[v] = true;
        while(!q.empty()){
            int temp = q.front();
            q.pop();
            for(int el : edges[temp]) {
                if(!visited[el]){
                    visited[el] = true;
                    dist[el] = dist[temp] + 1;
                    q.push(el);
                    if(groups[group].count(el))
                        return dist[el];
                }
            }
        }
        return -1;
    }
    void addEdge(int start, int end){
        edges[start].push_back(end);
        edges[end].push_back(start);
    }
    void assignGroup(int group, int vertices){
        groups[group].insert(vertices);
    }
};

int main() {
    int N, M, v, u, group;
    cin >> N >> M;
    Graph g(N);
    for(int i = 0; i < M; i++){
        cin >> v >> u;
        g.addEdge(v, u);
    }
    for(int i = 1; i <= N; i++){
        cin >> group;
        g.assignGroup(group, i);
    }
    cin >> group;
    cout << g.BFS(group);
}