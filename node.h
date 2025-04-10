#ifndef NODE_H
#define NODE_H

#include <functional> // Для std::hash
#include <cstddef>

struct Node {
    int x, y;
    Node* parent;
    int cost;
    int heuristic;

    Node(int x, int y, Node* parent = nullptr, int cost = 0, int heuristic = 0);
    bool operator==(const Node& other) const;
};

struct NodeHash {
    size_t operator()(const Node& node) const;
};



#endif