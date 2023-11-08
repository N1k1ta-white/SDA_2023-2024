#include <deque>
#include <iostream>

using namespace std;
class HungerGame {
    deque<int> *players;
public:
    HungerGame() {
        players = new deque<int>;
    }

    HungerGame(const HungerGame& h) = delete;
    HungerGame operator=(const HungerGame& h) = delete;

    ~HungerGame() {
        delete players;
    }

    bool fight() {
        bool res = false;
        deque<int> *survived = new deque<int>;
        int player;
        while (!players->empty()) {
            player = players->front();
            players->pop_front();
            if (survived->empty() || survived->back() > player)
                survived->push_back(player);
            else if (survived->back() < player) {
                res = true;
                if (!players->empty()) {
                    survived->push_back(players->front());
                    players->pop_front();
                }
            }
        }
        delete players;
        players = survived;
        return res;
    }

    void add(int num) {
        players->push_back(num);
    }
};

//int main() {
//    HungerGame game;
//    int n, day = 0, temp;
//    cin >> n;
//    for (int i = 0; i < n; ++i) {
//        cin >> temp;
//        game.add(temp);
//    }
//    while (game.fight())
//        day++;
//    cout << day;
//}

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;


int main() {
    int N =0;
    cin>>N;
    vector<int> arr(N);
    vector<int> eliminations(N);
    stack<int> st;
    for(int i=0;i<N;i++){
        cin >> arr[i];
    }
    for(int i=N-1;i>-1;i--){
        while(!st.empty() && arr[i]< arr[st.top()]){
            eliminations[i] = std::max(eliminations[st.top()],eliminations[i]+1);
            st.pop();
        }
        st.push(i);
    }
    cout<< *std::max_element(eliminations.begin(),eliminations.end());
}