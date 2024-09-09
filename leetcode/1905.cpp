#include <iostream>
#include <vector>

using namespace std;

class Solution {

    static int n;
    static int m;

    struct Point {
        int x;
        int y;

        static int coordinates(int x, int y) {
            return m * x + y;
        }

        int getCoordinates() const {
            return coordinates(x, y);
        }
    };

    class CellChecker {
        vector<vector<int>> *grid;
    public:

        explicit CellChecker(vector<vector<int>>& grid) : grid(&grid) {}

        bool isMarked(const Point& point) const {
            return grid->at(point.x).at(point.y);
        }
    };

    class Disjoint {
        vector<int> disjoint;
        vector<int> rank;
        int groupCount;
        int removedGroup;
    public:
        Disjoint() : groupCount(0) {
            removedGroup = n * m;
            disjoint = vector<int>(n * m + 1,  -1);
            rank = vector<int>(n * m + 1, 1);
            disjoint[removedGroup] = removedGroup;
        }

        int find(int x) {
            if (disjoint[x] == -1) {
                groupCount++;
                disjoint[x] = x;
            } else if (disjoint[x] != x) {
                disjoint[x] = find(disjoint[x]);
            }
            return disjoint[x];
        }

        void Union(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX == rootY) {
                return;
            }
            groupCount--;
            if (rank[rootX] < rank[rootY]) {
                swap(rootX, rootY);
            }
            disjoint[rootY] = rootX;
            rank[rootX] += rank[rootY];
        }

        void removeGroup(int x) {
            int root_x = find(x);
            if (root_x != removedGroup) {
                groupCount--;
                disjoint[root_x] = removedGroup;
            }
        }

        int getGroupCount() const {
            return groupCount;
        }
    };

    class SubIslandCounter {
        Disjoint disjoint;
        CellChecker cellChecker;
        vector<vector<int>> *grid;
        vector<bool> visited;

        const vector<Point> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        bool isInGrid(Point& point) const {
            return point.x >= 0 && point.x < grid->size() && point.y >= 0 && point.y < grid->at(0).size();
        }

        bool isGround(Point& point) {
            return isInGrid(point) && grid->at(point.x).at(point.y);
        }

        bool isVisited(Point& point) {
            return visited[point.getCoordinates()];
        }

        bool isSubIsland(Point& point) {
            return !cellChecker.isMarked(point);
        }

        void addNeighbours(Point& point) {
            for (auto& direction : directions) {
                Point next = { point.x + direction.x, point.y + direction.y };
                recursiveAdd(point, next);
            }
        }

        void recursiveAdd(Point& from, Point& to) {
            if (isGround(to) && !isVisited(to)) {
                disjoint.Union(from.getCoordinates(), to.getCoordinates());
                visited[to.getCoordinates()] = true;

                if (isSubIsland(to)) {
                    disjoint.removeGroup(to.getCoordinates());
                }
                addNeighbours(to);
            }
        }

        void fill() {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    Point point = {i, j};

                    if (!isVisited(point) && isGround(point)) {
                        visited[point.getCoordinates()] = true;
                        disjoint.find(point.getCoordinates());
                        if (isSubIsland(point)) {
                            disjoint.removeGroup(point.getCoordinates());
                        }
                        addNeighbours(point);
                    }
                }
            }
        }

    public:
        SubIslandCounter(vector<vector<int>>& grid1, vector<vector<int>>& grid2) : cellChecker(grid1),
                                                                                   grid(&grid2) {
            visited = vector<bool>(n * m, false);
            fill();
        }

        int getCountOfSubIslands() const {
            return disjoint.getGroupCount();
        }
    };


public:
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        n = grid1.size();
        m = grid1[0].size();
        SubIslandCounter subIslandCounter(grid1, grid2);
        return subIslandCounter.getCountOfSubIslands();
    }
};

int Solution::n = 0;
int Solution::m = 0;

int main() {
    vector<vector<int>> grid1 = {{1,1,1,0,0},{0,1,1,1,1},{0,0,0,0,0},{1,0,0,0,0},{1,1,0,1,1}};
    vector<vector<int>> grid2 = {{1,1,1,0,0},{0,0,1,1,1},{0,1,0,0,0},{1,0,1,1,0},{0,1,0,1,0}};
    Solution solution;
    cout << solution.countSubIslands(grid1, grid2);
}