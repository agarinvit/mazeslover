#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "maze.h"
#include "node.h"

Node* randomSearch(const Maze& maze);
Node* dfs(const Maze& maze);
Node* bfs(const Maze& maze);
Node* greedySearch(const Maze& maze);
Node* aStarSearch(const Maze& maze);

#endif