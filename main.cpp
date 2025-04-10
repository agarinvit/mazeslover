#include <iostream>
#include "maze.h"
#include "algorithms.h"
#include "visualize.h"
#include <chrono>
int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Invalid input\n" << std::endl;
        std::cerr << "Usage: " << argv[0] << " <maze_file> <algorithm>" << std::endl;
        std::cerr << "Algorithms: random, dfs, bfs, greedy, astar" << std::endl;
        return EXIT_FAILURE;
    }

    Maze maze;
    if (!maze.load(argv[1])) {
        std::cerr << "Failed to load maze from file: " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    // Выбор алгоритма
    std::string algorithm = argv[2];
    Node* result = nullptr;

    if (algorithm == "random") {   // ig its good ?
        result = randomSearch(maze);
    } else if (algorithm == "dfs") {
        result = dfs(maze);
    } else if (algorithm == "bfs") {
        result = bfs(maze);
    } else if (algorithm == "greedy") {
        result = greedySearch(maze);
    } else if (algorithm == "astar") {
        result = aStarSearch(maze);
    } else {
        std::cerr << "Invalid input.\n" << std::endl;
        return EXIT_FAILURE;
    }

    // Вывод результата
    if (result) {
        std::unordered_set<Node, NodeHash> openedNodes; // Множество открытых узлов
        visualizePath(maze, result, openedNodes);
        std::cout << "Path length: " << result->cost << std::endl;
    } else {
        std::cout << "No path found." << std::endl;
    }

    return EXIT_SUCCESS;
}