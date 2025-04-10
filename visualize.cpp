#include "visualize.h"
#include <iostream>
#include <unordered_set> // Добавьте эту строку

void visualizePath(const Maze& maze, const Node* path, const std::unordered_set<Node, NodeHash>& openedNodes) {
    std::vector<std::string> display = maze.grid;

    // Отмечаем открытые узлы
    for (const auto& node : openedNodes) {
        if (display[node.y][node.x] == ' ') {
            display[node.y][node.x] = '#';
        }
    }

    // Отмечаем путь
    const Node* current = path;
    while (current) {
        if (display[current->y][current->x] == ' ' || display[current->y][current->x] == '#') {
            display[current->y][current->x] = 'o';
        }
        current = current->parent;
    }

    // Отмечаем начальную и конечную точки
    display[maze.start.y][maze.start.x] = 'S';
    display[maze.end.y][maze.end.x] = 'E';

    // Выводим лабиринт
    for (const auto& row : display) {
        std::cout << row << std::endl;
    }

    // Вывод легенды
    std::cout << "--------------" << std::endl;
    std::cout << "S Start" << std::endl;
    std::cout << "E End" << std::endl;
    std::cout << "# Opened node" << std::endl;
    std::cout << "o Path" << std::endl;
    std::cout << "X Wall" << std::endl;
    std::cout << "space Fresh node" << std::endl;
    std::cout << "--------------" << std::endl;
}