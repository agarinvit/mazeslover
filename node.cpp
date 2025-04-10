#include "node.h"
#include <functional> // Для std::hash
#include <cstddef>

Node::Node(int x, int y, Node* parent, int cost, int heuristic)
    : x(x), y(y), parent(parent), cost(cost), heuristic(heuristic) {}

bool Node::operator==(const Node& other) const {
    return x == other.x && y == other.y;
}

size_t NodeHash::operator()(const Node& node) const {
    return std::hash<int>()(node.x) ^ std::hash<int>()(node.y);
}