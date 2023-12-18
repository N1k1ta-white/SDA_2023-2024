#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>

using namespace std;

class Graph {
    unordered_map<int, set<int>> group;
    vector<pair<int, int>> roads;
    unordered_map<int, int> groupDetector;
    int countCities;
    int countRoads;
    int usedRoads;
    int groupCount;
public:
    Graph(int cityCount) : countCities(cityCount), countRoads(0), usedRoads(0) {
        for (int i = 1; i < cityCount + 1; ++i) {
            group[i].insert(i);
            groupDetector[i] = i;
        }
        groupCount = cityCount;
    }

    void addRoad(int start, int end) {
        countRoads++;
        roads.emplace_back(start, end);
    }

    void minimizeGroups() {
        int iter = 0;
        while (iter != countRoads) {
            if (group[groupDetector[roads[iter].first]].find(roads[iter].second) == group[groupDetector[roads[iter].first]].end()) {
                for (int el : group[groupDetector[roads[iter].second]]) {
                    group[groupDetector[roads[iter].first]].insert(el);
                }
                group.erase(groupDetector[roads[iter].second]);
                groupDetector[roads[iter].second] = groupDetector[roads[iter].first];
                usedRoads++;
                iter++;
            } else {
                iter++;
            }
        }
    }

    int getRoads() const {
        return usedRoads;
    }

    int getCountGroups() const {
        return group.size();
    }
};


int main() {
    int N, cityCount, roadCount, costDisco, costRoad, st, en;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> cityCount >> roadCount >> costDisco >> costRoad;
        Graph gr(cityCount);
        for (int j = 0; j < roadCount; ++j) {
            cin >> st >> en;
            gr.addRoad(st, en);
        }
        gr.minimizeGroups();
        cout << costDisco * gr.getCountGroups() + costRoad * gr.getRoads() << endl;
    }
}