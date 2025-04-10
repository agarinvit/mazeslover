#include "algorithms.h"
#include <queue>
#include <stack>
#include <unordered_set>
#include <random>
#include <chrono>
#include <iostream>
#include <cmath>

#include "visualize.h"

int  heuristic(int x1, int x2, int y1, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

int calculatePathLength(Node* node) {
    int length = 0;
    while (node != nullptr) {
        length++;
        node = node->parent;
    }
    return length - 1; // Subtract 1 to exclude the start node
}

Node* randomSearch(const Maze& maze) {
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count()); // Random number generator
    std::uniform_int_distribution<int> dist(0, 3); // For random direction selection

    Node* current = new Node(maze.start.x, maze.start.y); // Start node
    int steps = 0;
    constexpr int maxSteps = 100000; // Maximum steps to prevent infinite loops

    std::unordered_set<Node, NodeHash> visited;
    std::unordered_set<Node, NodeHash> openedNodes;

    visited.insert(*current);
    openedNodes.insert(*current);

    while (steps < maxSteps) {
        // Goal check
        if (current->x == maze.end.x && current->y == maze.end.y) {
            std::cout << "Random Search found the goal in " << steps << " steps!" << std::endl;
            visualizePath(maze, current, openedNodes);
            std::cout << "Nodes expanded: " << openedNodes.size() << std::endl;
            std::cout << "Path length: " << current->cost << std::endl;
            return current;
        }

        // Collect valid moves
        std::vector<Node*> possibleMoves;
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; ++i) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            if (maze.isValidPosition(nx, ny)) {
                Node* next = new Node(nx, ny, current, current->cost + 1);

                // Skip if already visited or in openedNodes
                if (visited.find(*next) == visited.end() && openedNodes.find(*next) == openedNodes.end()) {
                    possibleMoves.push_back(next);
                } else {
                    delete next; // Free memory
                }
            }
        }

        // Randomly select a move
        if (!possibleMoves.empty()) {
            int randomIndex = dist(rng) % possibleMoves.size(); // Random index
            Node* next = possibleMoves[randomIndex];

            visited.insert(*next);
            openedNodes.insert(*next);
            current = next;
        } else {
            // Backtrack if no moves are available
            if (current->parent) {
                current = current->parent;
            } else {
                break; // No more moves and no parent to backtrack to
            }
        }

        steps++;
    }

    std::cout << "Chyba hledani cesty po " << maxSteps << " steps." << std::endl;
    return nullptr;
}


Node* dfs(const Maze& maze) {
    std::stack<Node*> stack;
    std::unordered_set<Node, NodeHash> visited;
    std::unordered_set<Node, NodeHash> openedNodes;

    Node* startNode = new Node(maze.start.x, maze.start.y);
    stack.push(startNode);
    openedNodes.insert(*startNode);

    while (!stack.empty()) {
        Node* current = stack.top();
        stack.pop();

        // Goal check
        if (current->x == maze.end.x && current->y == maze.end.y) {
            std::cout << "DFS found the goal!" << std::endl;
            visualizePath(maze, current, openedNodes);
            std::cout << "Nodes expanded: " << openedNodes.size() << std::endl;
            std::cout << "Path length: " << current->cost << std::endl;
            return current;
        }

        // Skip if already visited
        if (visited.find(*current) != visited.end()) {
            delete current; // Free memory
            continue;
        }

        // Mark as visited
        visited.insert(*current);

        // Explore neighbors
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; ++i) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            if (maze.isValidPosition(nx, ny)) {
                Node* next = new Node(nx, ny, current, current->cost + 1);

                // Skip if already in stack or visited
                if (!visited.contains(*next)) {
                    stack.push(next);
                    openedNodes.insert(*next);
                } else {
                    delete next; // Free memory
                }
            }
        }
    }

    std::cout << "Chyba hledani cesty" << std::endl;
    return nullptr;
}
Node* bfs(const Maze& maze) {
    std::queue<Node*> queue;
    std::unordered_set<Node, NodeHash> visited;
    std::unordered_set<Node, NodeHash> openedNodes;

    Node* startNode = new Node(maze.start.x, maze.start.y);
    queue.push(startNode);
    openedNodes.insert(*startNode);

    while (!queue.empty()) {
        Node* current = queue.front();
        queue.pop();

        // Goal check
        if (current->x == maze.end.x && current->y == maze.end.y) {
            std::cout << "BFS found the goal!" << std::endl;
            visualizePath(maze, current, openedNodes);
            std::cout << "Nodes expanded: " << openedNodes.size() << std::endl;
            std::cout << "Path length: " << current->cost << std::endl;
            return current;
        }

        // Skip if already visited
        if (visited.find(*current) != visited.end()) {
            delete current; // Free memory
            continue;
        }

        // Mark as visited
        visited.insert(*current);

        // Explore neighbors
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; ++i) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            if (maze.isValidPosition(nx, ny)) {
                Node* next = new Node(nx, ny, current, current->cost + 1);

                // Skip if already in queue or visited
                if (visited.find(*next) == visited.end() && openedNodes.find(*next) == openedNodes.end()) {
                    queue.push(next);
                    openedNodes.insert(*next);
                } else {
                    delete next; // Free memory
                }
            }
        }
    }

    std::cout << "Chyba hledani cesty" << std::endl;
    return nullptr;
}
Node* greedySearch(const Maze& maze) {
    auto compare = [](Node* a, Node* b) {
        return a->heuristic > b->heuristic; // Min-heap based on heuristic
    };
    std::priority_queue<Node*, std::vector<Node*>, decltype(compare)> pq(compare);

    std::unordered_set<Node, NodeHash> visited;
    std::unordered_set<Node, NodeHash> openedNodes;

    Node* startNode = new Node(maze.start.x, maze.start.y);
    startNode->heuristic = heuristic(startNode->x, startNode->y, maze.end.x, maze.end.y);
    pq.push(startNode);
    openedNodes.insert(*startNode);

    while (!pq.empty()) {
        Node* current = pq.top();
        pq.pop();

        // Goal check
        if (current->x == maze.end.x && current->y == maze.end.y) {
            std::cout << "Greedy Search found the goal!" << std::endl;
            visualizePath(maze, current, openedNodes);
            std::cout << "Nodes expanded: " << openedNodes.size() << std::endl;
            std::cout << "Path length: " << current->cost << std::endl;
            return current;
        }

        // Skip if already visited
        if (visited.find(*current) != visited.end()) {
            delete current; // Free memory
            continue;
        }

        // Mark as visited
        visited.insert(*current);

        // Explore neighbors
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; ++i) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            if (maze.isValidPosition(nx, ny)) {
                Node* next = new Node(nx, ny, current, current->cost + 1);
                next->heuristic = heuristic(nx, ny, maze.end.x, maze.end.y);

                // Skip if already in queue or visited
                if (visited.find(*next) == visited.end() && openedNodes.find(*next) == openedNodes.end()) {
                    pq.push(next);
                    openedNodes.insert(*next);
                } else {
                    delete next; // Free memory
                }
            }
        }
    }

    std::cout << "Chyba hledani cesty." << std::endl;
    return nullptr;
}
Node* aStarSearch(const Maze& maze) {
    auto compare = [](Node* a, Node* b) {
        return (a->cost + a->heuristic) > (b->cost + b->heuristic);
    };
    std::priority_queue<Node*, std::vector<Node*>, decltype(compare)> queue(compare);

    std::unordered_set<Node, NodeHash> visited;
    std::unordered_set<Node, NodeHash> openedNodes; // Множество открытых узлов

    Node* startNode = new Node(maze.start.x, maze.start.y);
    startNode->cost = 0;
    startNode->heuristic = heuristic(startNode->x, startNode->y, maze.end.x, maze.end.y);
    queue.push(startNode);
    openedNodes.insert(*startNode);

    while (!queue.empty()) {
        Node* current = queue.top();
        queue.pop();

        // Если текущий узел — это цель, возвращаем его
        if (current->x == maze.end.x && current->y == maze.end.y) {
            std::cout << "A* Search found the goal!" << std::endl;

            // Визуализация пути
            visualizePath(maze, current, openedNodes);

            // Вывод количества открытых узлов и длины пути
            std::cout << "Nodes expanded: " << openedNodes.size() << std::endl;
            std::cout << "Path length: " << current->cost << std::endl;

            return current;
        }

        // Если узел уже посещён, пропускаем его
        if (visited.find(*current) != visited.end()) {
            continue;
        }

        // Помечаем узел как посещённый
        visited.insert(*current);

        // Визуализация текущего состояния
        visualizePath(maze, current, openedNodes);

        // Исследуем соседние узлы (вверх, вниз, влево, вправо)
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; ++i) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            // Проверяем, что новая позиция допустима
            if (maze.isValidPosition(nx, ny)) {
                Node* next = new Node(nx, ny, current);
                next->cost = current->cost + 1;
                next->heuristic = heuristic(nx, ny, maze.end.x, maze.end.y);
                queue.push(next);
                openedNodes.insert(*next); // Добавляем узел в открытые
            }
        }
    }

    // Если очередь пуста и цель не найдена, возвращаем nullptr
    std::cout << "A* Search failed to find a path." << std::endl;
    return nullptr;
}
