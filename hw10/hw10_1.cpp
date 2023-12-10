#include <iostream>
#include <queue>

using namespace std;

struct Coordinate {
    int x;
    int y;
};

struct Square {
    Coordinate max;
    Coordinate min;

    long long calculateArea() {
        return (long long)(abs(max.x - min.x) + 1)  * (abs(max.y - min.y) + 1);
    }
};

void checkNeighbors(int** arr, int N, const Coordinate& curr, Square& square) {
    if (curr.x >= 0 && curr.x < N && curr.y >= 0 && curr.y < N && arr[curr.x][curr.y]) {
        if (square.min.x > curr.x)
            square.min.x = curr.x;
        if (square.min.y > curr.y)
            square.min.y = curr.y;
        if (square.max.x < curr.x)
            square.max.x = curr.x;
        if (square.max.y < curr.y)
            square.max.y = curr.y;
        arr[curr.x][curr.y] = 0;
        Coordinate newCord = curr;
        newCord.x -= 1;
        checkNeighbors(arr, N, newCord, square);
        newCord.x += 2;
        checkNeighbors(arr, N, newCord, square);
        newCord.x -= 1;
        newCord.y += 1;
        checkNeighbors(arr, N, newCord, square);
        newCord.y -= 2;
        checkNeighbors(arr, N, newCord, square);
    }
}

int main() {
    int N;
    cin >> N;
    int **arr = new int*[N];
    for (int i = 0; i < N; ++i) {
        arr[i] = new int[N];
        for (int j = 0; j < N; ++j) {
            cin >> arr[i][j];
        }
    }

    Coordinate curr;
    Square square;
    auto comparator = [](long long n1, long long n2)->bool{
            return n1 < n2;
    };
    priority_queue<long long, vector<long long>, decltype(comparator)> res(comparator);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (arr[j][i]) {
                curr = square.min = square.max = {j, i};
                checkNeighbors(arr, N, curr, square);
                res.push(square.calculateArea());
            }
        }
    }

    while (!res.empty()) {
        cout << res.top() << " ";
        res.pop();
    }

    for (int i = 0; i < N; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}