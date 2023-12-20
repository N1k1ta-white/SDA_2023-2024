//#include <iostream>
//#include <set>
//#include <vector>
//#include <unordered_map>
//
//using namespace std;
//
//struct Coordinate {
//    int x;
//    int y;
//
//    string getString() const {
//        return (to_string(x) + to_string(y));
//    }
//};
//
//struct Comparator {
//    bool operator()(const pair<Coordinate, int>& p1, const pair<Coordinate, int>& p2) {
//        if (p1.second == p2.second) {
//            if (p1.first.y == p2.first.y) {
//                return p1.first.x > p2.first.x;
//            }
//            return p1.first.y > p2.first.y;
//        }
//        return p1.second > p2.second;
//    }
//};
////
////int search(int from, int to, const vector<set<pair<int, int>>>& edges) {
////    priority_queue<pair<int, int>, vector<pair<int, int>>, Comparator> pq;
////    vector<bool> visited(edges.size(), false);
////    vector<int> path(edges.size(), INT_MAX);
////    pq.push({ from, 0 });
////    pair<int, int> curr;
////    int currPath;
////    while (!pq.empty()) {
////        curr = pq.top();
////        pq.pop();
////        if (visited[curr.first])
////            continue;
////        visited[curr.first] = true;
////        if (curr.first == to)
////            return path[to];
////        for (pair<int, int> el : edges[curr.first]) {
////            currPath = el.second + curr.second;
////            if (path[el.first] > currPath)
////                path[el.first] = currPath;
////            pq.emplace(el.first, currPath + (wait[el.first] - (currPath % wait[el.first] == 0 ? wait[el.first] : currPath % wait[el.first])));
////        }
////    }
////    return -1;
////}
//
//// first to
//// second val
//
//int main() {
//    int height, width;
//    Coordinate cd;
//    char cell;
//    cin >> height >> width;
//    int** matr = new int*[height];
//    for (int i = 0; i < height; ++i) {
//        matr[i] = new int[width];
//        for (int j = 0; j < width; ++j) {
//            cin.get(cell);
//            matr[i][j] = cell == '.' ? 0 : 1;
//        }
//    }
//
//    unordered_map<string, vector<pair<Coordinate, int>>> edges;
//    for (int i = 0; i < height; ++i) {
//        for (int j = 0; j < width; ++j) {
//            cd = {i, j};
//            Coordinate temp;
//            string cord = cd.getString();
//            if (!edges.count(cord)) {
//                vector<pair<Coordinate, int>> edg;
//                edges[cord] = edg;
//            }
//            if (i != 0) {
//                temp = {i - 1, j};
//                edges[cord].emplace_back(temp, matr[i - 1][j]);
//            }
//            if (j != 0) {
//                temp = {i, j - 1};
//                edges[cord].emplace_back(temp, matr[i][j - 1]);
//            }
//            if (i + 1 != height) {
//                temp = {i + 1, j};
//                edges[cord].emplace_back(temp, matr[i + 1][j]);
//            }
//            if (j + 1 != width) {
//                temp = {i, j + 1};
//                edges[cord].emplace_back(temp, matr[i][j + 1]);
//            }
//        }
//    }
//
//    for (int i = 0; i < height; ++i) {
//        delete[] matr[i];
//    }
//    delete[] matr;
//}
//


#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

long long Dijkstra(vector<vector<char>>& matr){
    priority_queue<pair<int,pair<int,int>>, vector<pair<int,pair<int,int>>>, greater<>> pq; //cost,<x,y>
    vector<vector<int>> distance(matr.size());
    pair<int,int> curr;
    int currDist;
    bool w;
    for (int i = 0; i < matr.size(); i++) {
        for (int j = 0; j < matr[0].size(); j++)
            distance[i].push_back(INT_MAX);
    }
    for (int i = 0; i < matr[0].size(); i++) {
        pq.push({(matr[0][i] == '#'), {0, i}});
        distance[0][i] = (matr[0][i] == '#');
        pq.push({(matr[matr.size() - 1][i] == '#'), {matr.size() - 1, i}});
        distance[matr.size() - 1][i] = (matr[matr.size() - 1][i] == '#');
    }
    for (int i = 0; i < matr.size() - 1; i++) {
        pq.push({(matr[i][0] == '#'), {i, 0}});
        distance[i][0] = (matr[i][0] == '#');
        pq.push({(matr[i][matr[0].size() - 1] == '#'), {i, matr[0].size() - 1}});
        distance[i][matr[0].size() - 1] = (matr[i][matr[0].size() - 1] == '#');
    }
    while (!pq.empty()) {
        curr = pq.top().second;
        currDist = pq.top().first;
        pq.pop();
        if (currDist > distance[curr.first][curr.second]) {
            continue;
        }
        pair<int,int> neigh[4]  = {{curr.first + 1, curr.second}, {curr.first - 1, curr.second},
                                   {curr.first, curr.second + 1}, {curr.first, curr.second - 1}};
        for (int i = 0; i < 4; i++) {
            if (neigh[i].first < 0 || neigh[i].first >= matr.size()
                || neigh[i].second < 0 || neigh[i].second >= matr[0].size()) {
                continue;
            }
            w = (matr[neigh[i].first][neigh[i].second] == '#');
            if (currDist + w < distance[neigh[i].first][neigh[i].second]) {
                distance[neigh[i].first][neigh[i].second] = currDist + w;
                pq.push({distance[neigh[i].first][neigh[i].second], {neigh[i].first, neigh[i].second}});
            }
        }
    }
    int max = INT_MIN;
    int counter = 0;
    for (int i = 0; i < matr.size(); i++) {
        for (int j = 0; j < matr[0].size(); j++) {
            if (distance[i][j] > max && matr[i][j] == '.'){
                max = distance[i][j];
                counter = 1;
                continue;
            }
            if (distance[i][j] == max && matr[i][j] == '.') {
                counter++;
            }
        }
    }
    return counter;
}


int main() {
    int N,M;
    char a;
    cin >> N >> M;
    vector<vector<char>> matrix(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++){
            cin >> a;
            matrix[i].push_back(a);
        }
    }
    cout<<Dijkstra(matrix);
}