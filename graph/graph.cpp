#include "bits/stdc++.h"
#include "../astar/astar.h"

class Graph_Node {
private:
    std::string value;
    double heuristic;
    std::vector<std::pair<Graph_Node*, double>> neighbors; // pair of (neighbor_node, edge_weight)

public:
    Graph_Node(std::string val, double h = 0) : value(val), heuristic(h) {}

    void addNeighbor(Graph_Node* neighbor, double weight = 1.0) {
        // Check if neighbor already exists
        for (const auto& pair : neighbors) {
            if (pair.first == neighbor) {
                return; // Skip if already connected
            }
        }
        neighbors.push_back(std::make_pair(neighbor, weight));
    }

    std::string getValue() const { return value; }
    double getHeuristic() const { return heuristic; }
    const std::vector<std::pair<Graph_Node*, double>>& getNeighbors() const { return neighbors; }
};

class Graph {
private:
    std::unordered_map<std::string, Graph_Node*> nodes;

public:
    // Destructor to clean up dynamically allocated nodes
    ~Graph() {
        for (auto& pair : nodes) {
            delete pair.second;
        }
    }

    Graph_Node* addNode(const std::string& value, double heuristic = 0.0) {
        if (nodes.find(value) == nodes.end()) {
            nodes[value] = new Graph_Node(value, heuristic);
        }
        return nodes[value];
    }

    void addEdge(const std::string& value1, const std::string& value2, double weight = 1.0) {
        Graph_Node* node1 = addNode(value1);
        Graph_Node* node2 = addNode(value2);

        // Add edges in both directions
        node1->addNeighbor(node2, weight);
        node2->addNeighbor(node1, weight);
    }

    Graph_Node* getNode(const std::string& value) {
        auto it = nodes.find(value);
        return (it != nodes.end()) ? it->second : nullptr;
    }

    std::vector<std::pair<Graph_Node*, double>> getNeighbors(const std::string& value) {
        Graph_Node* node = getNode(value);
        if (node) {
            return node->getNeighbors();
        }
        return std::vector<std::pair<Graph_Node*, double>>();
    }

    void printGraph() const {
        for (const auto& pair : nodes) {
            Graph_Node* node = pair.second;
            std::cout << "Node(" << node->getValue() << ", h=" << node->getHeuristic() << "): Neighbors = ";
            
            const auto& neighbors = node->getNeighbors();
            std::cout << "[";
            for (size_t i = 0; i < neighbors.size(); ++i) {
                if (i > 0) std::cout << ", ";
                std::cout << neighbors[i].first->getValue() << "(w=" << neighbors[i].second << ")";
            }
            std::cout << "]" << std::endl;
        }
    }
};

class graph_list : public State<Graph_Node*> {
public:
    Graph* graph_1;

    graph_list() {
        graph_1 = new Graph();
    }

    int hn(Graph_Node* current, Graph_Node* dest) {
        return current->getHeuristic();
    }

    vector<pair<Graph_Node*, int>> fn_neighbours(Graph_Node* state) {
        vector<pair<Graph_Node*, int>> nextStates;
        // cout << state->getValue() << " -> ";
        for(auto& [node, cost]: state->getNeighbors()) {
            nextStates.push_back({node, cost});
            // cout << node->getValue() << " ";
        }
        // cout << endl;

        return nextStates;
    }


    // bool operator==(const State& other) {
    //     return other.data->getValue() == data->getValue() && other.data->getValue() == data->getValue();
    // }

    // bool operator<(const State& rhs) {
    //     return data->getValue() < rhs.data->getValue();
    // }

    void print_state(Graph_Node* currentState) {
        cout << currentState->getValue() << endl;
    }
};

int main() {
    // Add nodes with heuristic values
    graph_list* g = new graph_list();
    g->graph_1->addNode("A", 10.0);
    g->graph_1->addNode("B", 8.0);
    g->graph_1->addNode("C", 5.0);
    g->graph_1->addNode("D", 7.0);
    g->graph_1->addNode("E", 3.0);
    g->graph_1->addNode("F", 6.0);
    g->graph_1->addNode("G", 3.0);
    g->graph_1->addNode("H", 3.0);
    g->graph_1->addNode("I", 1.0);
    g->graph_1->addNode("J", 0.0);

    // Create edges between nodes
    g->graph_1->addEdge("A", "B", 6.0);
    g->graph_1->addEdge("A", "F", 3.0);
    g->graph_1->addEdge("B", "D", 2.0);
    g->graph_1->addEdge("B", "C", 3.0);
    g->graph_1->addEdge("C", "D", 1.0);
    g->graph_1->addEdge("C", "E", 5.0);
    g->graph_1->addEdge("D", "E", 8.0);
    g->graph_1->addEdge("E", "I", 5.0);
    g->graph_1->addEdge("E", "J", 5.0);
    g->graph_1->addEdge("I", "J", 3.0);
    g->graph_1->addEdge("I", "G", 3.0);
    g->graph_1->addEdge("I", "H", 5.0);
    g->graph_1->addEdge("F", "G", 3.0);
    g->graph_1->addEdge("F", "H", 2.0);

    Node<Graph_Node*>* res = A_star<Graph_Node*>(g, g->graph_1->getNode("A"), g->graph_1->getNode("J"));
    while(res != NULL) {
        if(res->parent == NULL) {
            cout << res->data->getValue();
            break;
        }
        cout << res->data->getValue() << " -> ";
        res = res->parent;
    }

    return 0;
}