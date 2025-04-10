#ifndef VISUALIZE_H
#define VISUALIZE_H

#include "maze.h"
#include "node.h"
#include <unordered_set> // Добавьте эту строку

void visualizePath(const Maze& maze, const Node* path, const std::unordered_set<Node, NodeHash>& openedNodes);

#endif