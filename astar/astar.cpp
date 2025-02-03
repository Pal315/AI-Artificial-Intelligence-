#include "astar.h"

template <typename T>
Node<T>* A_star(State<T>* QClass, T initialState, T finalState) {
    priority_queue<pair<int, Node<T>*>, vector<pair<int, Node<T>*>>, Compare<T>> pq;
    set<Node<T>*, NodeComparator<T>> open;
    set<Node<T>*, NodeComparator<T>> closed;
    Node<T>* root = new Node<T>(initialState);

    open.insert(root);
    pq.push({QClass->hn(initialState, finalState), root});

    while (!pq.empty()) {
        auto [priority, current] = pq.top();
        pq.pop();

        open.erase(current);

        if (current->data == finalState) {
            return current;
        }

        closed.insert(current);

        vector<pair<T, int>> neighbours = QClass->fn_neighbours(current->data);
        for (auto& [neighbour_data, cost] : neighbours) {
            Node<T>* neighbour = new Node<T>(neighbour_data, current, current->cost + cost);
            int hnCost = QClass->hn(neighbour->data, finalState);
            int totalCost = cost + neighbour->cost + hnCost;

            if (closed.count(neighbour)) {
                auto old_closed = closed.find(neighbour);
                if ((*old_closed)->cost > neighbour->cost) {
                    closed.erase(old_closed);
                    open.insert(neighbour);
                    pq.push({totalCost, neighbour});
                } else {
                    delete neighbour;
                }
                continue;
            }

            auto it = open.find(neighbour);
            if (it != open.end()) {
                if ((*it)->cost > neighbour->cost) {
                    open.erase(it);
                    open.insert(neighbour);
                    pq.push({totalCost, neighbour});
                } else {
                    delete neighbour;
                }
                continue;
            }

            open.insert(neighbour);
            pq.push({totalCost, neighbour});
        }
    }

    cout << "The problem could not be solved" << endl;
    return nullptr;
}