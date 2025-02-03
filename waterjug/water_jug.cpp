#include <bits/stdc++.h>

using namespace std;

bool isEqual(pair<int, int> initialState, pair<int, int> goalState)
{
    return initialState.first == goalState.first && initialState.second == goalState.second;
}

int encode(int x, int y, int maxSecond)
{
    return x * (maxSecond + 1) + y;
}

pair<int, int> decode(int encoded, int maxSecond)
{
    return {encoded / (maxSecond + 1), encoded % (maxSecond + 1)};
}

void solve(pair<int, int> initial, pair<int, int> final, int maxFirst, int maxSecond)
{
    unordered_map<int, int> status;
    int initialEncoded = encode(initial.first, initial.second, maxSecond);
    int finalEncoded = encode(final.first, final.second, maxSecond);

    status[initialEncoded] = 0;
    queue<int> q;
    q.push(initialEncoded);
    int checks = 0;

    while (!q.empty())
    {
        int currentEncoded = q.front();
        q.pop();

        auto state = decode(currentEncoded, maxSecond);

        if (status.find(currentEncoded) == status.end())
        {
            cout << "Some error occurred";
            return;
        }

        if (isEqual(state, final))
        {
            cout << "Goal State reached" << endl;
            cout << "Number of checks: " << checks;
            return;
        }
        checks++;

        vector<pair<int, int>> nextStates = {
            {0, state.second},                          // Empty first jug
            {maxFirst, state.second},                  // Fill first jug
            {state.first, 0},                          // Empty second jug
            {state.first, maxSecond},                  // Fill second jug
            {max(0, state.first - (maxSecond - state.second)), min(maxSecond, state.first + state.second)}, // Pour first into second
            {min(maxFirst, state.first + state.second), max(0, state.second - (maxFirst - state.first))}    // Pour second into first
        };

        for (auto nextState : nextStates)
        {
            cout << "Next state: " << nextState.first << " " << nextState.second << endl;
            int nextEncoded = encode(nextState.first, nextState.second, maxSecond);
            if (status.find(nextEncoded) == status.end())
            {
                status[nextEncoded] = 0;
                q.push(nextEncoded);
            }
        }
        cout << endl;
    }

    cout << "No solution found for the given initial and final states";
}

int main()
{
    pair<int, int> initialState = {0, 0};
    pair<int, int> finalState = {2, 0};
    int maxValueFirst = 4;
    int maxValueSecond = 5;

    solve(initialState, finalState, maxValueFirst, maxValueSecond);

    return 0;
}
