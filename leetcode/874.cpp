#include <iostream>
#include <vector>
#include <unordered_map>
#include <valarray>

using namespace std;

class Solution {

    class Hash {
        static const long num = 30011;
    public:
        static long hash(int x, int y) {
            return x * num + y;
        }
    };

    class Point {
        vector<int>* pointVec;
        bool isMinePoint;

        static const int x = 0;
        static const int y = 1;

        void free() {
            if (isMinePoint) {
                delete pointVec;
            }
        }

        void copyFrom(const Point& point) {
            isMinePoint = true;
            this->pointVec = new vector<int>(0, 2);
            pointVec->at(x) = point.getX();
            pointVec->at(y) = point.getY();
        }

    public:

        Point() : isMinePoint(true) {
            pointVec = new vector<int>(0, 2);
        }

        Point(const Point& point) : Point(point.getX(), point.getY()) {};

        Point& operator=(const Point& other) {
            if (this != &other) {
                free();
                copyFrom(other);
            }
            return *this;
        }

        Point(int x, int y) : isMinePoint(true) {
            pointVec = new vector<int>{x, y};
        }

        Point(vector<int>& point) : pointVec(&point), isMinePoint(false) {}

        int getY() const {
            return pointVec->at(y);
        }

        int getX() const {
            return pointVec->at(x);
        }

        void setX(int xValue) {
            pointVec->at(x) = xValue;
        }

        void setY(int yValue) {
            pointVec->at(y) = yValue;
        }

        long getCoordinates() const {
            return Hash::hash(getX(), getY());
        }

        ~Point() {
            free();
        }
    };

    class Plane {
        unordered_map<long, bool> obstacle;
    public:
        Plane(vector<vector<int>>& obstacle) {
            for (Point point : obstacle) {
                this->obstacle[point.getCoordinates()] = true;
            }
        }

        bool isObstacle(Point& point) {
            return obstacle.find(point.getCoordinates()) != obstacle.end();
        }

        bool isObstacle(Point* point) {
            return obstacle.find(point->getCoordinates()) != obstacle.end();
        }
    };

    class Rotator {
        int currentDirection = 0;
        static const int count = 4;
    public:

        void turnRight() {
            currentDirection = (currentDirection + 1) % 4;
        }

        void turnLeft() {
            currentDirection = (currentDirection + 3) % 4;
        }

        int getIdOfCurrentDirection() const {
            return currentDirection;
        }
    };

    class Action {
    protected:
        Rotator* rotator;
    public:
        Action(Rotator& rotator) : rotator(&rotator) {}

        virtual void makeAction() = 0;

        virtual ~Action() = default;
    };

    class MoveForward : public Action {
        int steps;
        Plane* plane;
        Point* point;

        static vector<vector<int>> movement;

        Point getDestination() {
            Point move = movement[rotator->getIdOfCurrentDirection()];
            Point dest;
            dest.setX(point->getX() + move.getX() * steps);
            dest.setY(point->getY() + move.getY() * steps);
            return dest;
        }

    public:
        MoveForward(Plane& plane, Rotator& rotator, Point& point, int steps)
            : Action(rotator), plane(&plane), steps(steps), point(&point) {}

        void makeAction() override {
            Point move = movement[rotator->getIdOfCurrentDirection()];

            for (int i = 0; i < steps; ++i) {
                point->setX(point->getX() + move.getX());
                point->setY(point->getY() + move.getY());
                if (plane->isObstacle(point)) {
                    point->setX(point->getX() - move.getX());
                    point->setY(point->getY() - move.getY());
                    break;
                }
            }
        }
    };

    class TurnRight : public Action {
    public:
        TurnRight(Rotator& rotator) : Action(rotator) {}

        void makeAction() override {
            rotator->turnRight();
        }
    };

    class TurnLeft : public Action {
    public:
        TurnLeft(Rotator& rotator) : Action(rotator) {}

        void makeAction() override {
            rotator->turnLeft();
        }
    };

    class Robot {
        Plane plane;
        Rotator rotator;
        Point curr;
        int longestDistance;

        Action* commandDecoder(int commandId) {
            switch (commandId) {
                case -1:
                    return new TurnRight(rotator);
                case -2:
                    return new TurnLeft(rotator);
                default:
                    return new MoveForward(plane, rotator, curr, commandId);
            }
        }

        int getEuclideanDistance() {
            return pow(curr.getX(), 2) + pow(curr.getY(), 2);
        }

        bool isLongestDistance() {
            return getEuclideanDistance() > longestDistance;
        }

    public:

        Robot(vector<vector<int>>& obstacles) : plane(obstacles), curr(0, 0), longestDistance(0) {}

        void executeCommand(int command) {
            Action* action = commandDecoder(command);
            action->makeAction();
            delete action;

            if (isLongestDistance()) {
                longestDistance = getEuclideanDistance();
            }
        }

        int getLongestDistance() const {
            return longestDistance;
        }

    };

public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        Robot robot(obstacles);
        for (int& command : commands) {
            robot.executeCommand(command);
        }
        return robot.getLongestDistance();
    }
};

vector<vector<int>> Solution::MoveForward::movement = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int main() {
    vector<int> commands = {6,-1,-1,6};
    vector<vector<int>> obstacles = {};
    Solution solution;
    cout << solution.robotSim(commands, obstacles);
}