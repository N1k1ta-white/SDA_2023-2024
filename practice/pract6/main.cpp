#include <iostream>
#include <set>

#define SI set<int>

using namespace std;

int querySet(SI& s) {

    // Middle element


    int ans = lower_bound(s.begin(), s.end(), );
}

int main() {
//    int N;
//    cin >> N;
//
//
//    //1 - Add
//    //2 - Query
//    //3 - RMV
//
//    SI s;
//
//    for (int i = 0; i < N; ++i) {
//        int opcode;
//        int num;
//
//        cin >> opcode;
//        if (opcode == 1) {
//            cin >> num;
//            s.insert(num);
//        }
//        if (opcode == 2) {
//            cin >> num;
//            s.erase(num);
//        }
//        if (opcode == 3) {
//            cin >> num;
//            cout << querySet(s, num);
//        }
//    }

    // Left is number left of median
    // Right is number right of median
    // Greatest element in left is median
    set<int> left, right;

    int N;
    cin >> N;

    int opcode, num;
    for (int i = 0; i < N; ++i) {
        //Add
        if (opcode == 1) {
            cin >> num;
            if (num > *(--left.end())) {
                right.insert(num);
                if (right.size() - left.size() > 2) {
                    left.insert()
                }
            }
        }
    }
}
