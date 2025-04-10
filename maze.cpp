#include "maze.h"
#include <fstream>
#include <iostream>

bool Maze::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("start") != std::string::npos) {
            sscanf(line.c_str(), "start %d, %d", &start.x, &start.y);
        } else if (line.find("end") != std::string::npos) {
            sscanf(line.c_str(), "end %d, %d", &end.x, &end.y);
        } else {
            grid.push_back(line);
        }
    }

    return true;
}

bool Maze::isValidPosition(int x, int y) const {
    // Приводим x и y к size_t для сравнения
    size_t ux = static_cast<size_t>(x);
    size_t uy = static_cast<size_t>(y);

    // Проверяем границы и свободное пространство
    return x >= 0 && ux < grid[0].size() && y >= 0 && uy < grid.size() && grid[y][x] == ' ';
}