#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

template <class T>
class Node {
public:
    T data;
    Node* parent;
    int cost;

    Node(T data) {
        this->data = data;
        this->parent = nullptr;
        this->cost = 0;
    }

    Node(T data, Node* parent) {
        this->data = data;
        this->parent = parent;
        this->cost = 0;
    }

    Node(T data, Node* parent, int cost) {
        this->cost = cost;
        this->data = data;
        this->parent = parent;
    }

    bool operator==(const Node& other) const {
        return data == other.data;
    }
};

template <typename T>
class State {
public:
    T data;

    virtual int hn(T current, T goal) = 0;
    virtual vector<pair<T, int>> fn_neighbours(T best_node) = 0;
    virtual void print_state(T state) = 0;
};

template <typename T>
struct Compare {
    bool operator()(const pair<int, Node<T>*>& a, const pair<int, Node<T>*>& b) {
        return a.first > b.first;
    }
};

template <typename T>
struct NodeComparator {
    bool operator()(const Node<T>* a, const Node<T>* b) const {
        return a->data < b->data;
    }
};

template <typename T>
Node<T>* A_star(State<T>* QClass, T initialState, T finalState);

#include "astar.cpp"  // Include the implementation file

#endif // ASTAR_H
