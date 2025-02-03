#include "bits/stdc++.h"
#include "../astar/astar.h"

class water_jug : public State<pair<int, int>> {
public:
    int maxFirst = 4;
    int maxSecond = 5;
    // water_jug(pair<int, int> data) {
    //     this->data = data;
    // }

    int hn(pair<int, int> current, pair<int, int> final) {
        return abs(current.first-final.first) + abs(current.second-final.second);
    }

    vector<pair<pair<int, int>, int>> fn_neighbours(pair<int, int> state) {
        vector<pair<pair<int, int>, int>> nextStates;
        int maxFirst = this->maxFirst;
        int maxSecond = this->maxSecond;
        
        if (state.first > 0)
            nextStates.push_back({{0, state.second}, 1});
        if (state.second > 0)
            nextStates.push_back({{state.first, 0}, 1});
        if (state.first < maxFirst)
            nextStates.push_back({{maxFirst, state.second}, 1});
        if (state.second < maxSecond)
            nextStates.push_back({{state.first, maxSecond}, 1});

        if (state.first > 0 && state.second < maxSecond)
            nextStates.push_back({{max(0, state.first - (maxSecond - state.second)), 
                                                min(maxSecond, state.first + state.second)}, 1});

        if (state.second > 0 && state.first < maxFirst)
            nextStates.push_back({{min(maxFirst, state.first + state.second), 
                                                max(0, state.second - (maxFirst - state.first))}, 1});

        return nextStates;
    }


    bool operator==(const State& other) {
        return other.data.first == data.first && other.data.second == data.second;
    }

    void print_state(pair<int, int> currentState) {
        cout << currentState.first << ", " << currentState.second << endl;
    }
};


int main() {
    State<pair<int, int>>* w = new water_jug();
    Node<pair<int, int>>* res = A_star<pair<int, int>>(w, {0, 0}, {2, 0});

    while(res != NULL) {
        w->print_state(res->data);
        res = res->parent;
    }

    return 0;
}