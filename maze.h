#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string>
#include "node.h"

class Maze {
public:
    std::vector<std::string> grid;
    Node start;
    Node end;

    // Конструктор по умолчанию
    Maze() : start(0, 0), end(0, 0) {}

    bool load(const std::string& filename);
    bool isValidPosition(int x, int y) const;
};

#endif