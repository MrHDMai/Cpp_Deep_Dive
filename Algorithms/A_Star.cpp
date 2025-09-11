#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <memory>

struct Node {
    int x, y;
    float f, g, h;
    Node* parent;
    bool obstacle;

    // Default constructor required for vector resize
    Node() : x(0), y(0), f(0), g(0), h(0), parent(nullptr), obstacle(false) {}
    
    // Parameterized constructor
    Node(int x, int y) : x(x), y(y), f(0), g(0), h(0), parent(nullptr), obstacle(false) {}

    bool operator==(const Node& other) const {
        return x == other.x && y == other.y;
    }

    struct Hash {
        size_t operator()(const Node& node) const {
            return std::hash<int>()(node.x) ^ std::hash<int>()(node.y);
        }
    };
};

class AStar {
private:
    std::vector<std::vector<Node>> grid;
    int width, height;

    // Heuristic function (Manhattan distance)
    float heuristic(const Node& a, const Node& b) {
        return std::abs(a.x - b.x) + std::abs(a.y - b.y);
    }

public:
    AStar(int width, int height) : width(width), height(height) {
        // Initialize grid with nodes
        grid.resize(height);
        for (int i = 0; i < height; ++i) {
            grid[i].resize(width);
            for (int j = 0; j < width; ++j) {
                grid[i][j] = Node(i, j);
            }
        }
    }

    void setObstacle(int x, int y) {
        if (x >= 0 && x < height && y >= 0 && y < width) {
            grid[x][y].obstacle = true;
        }
    }

    void clearObstacle(int x, int y) {
        if (x >= 0 && x < height && y >= 0 && y < width) {
            grid[x][y].obstacle = false;
        }
    }

    std::vector<Node*> findPath(const Node& start, const Node& goal) {
        // Check if start or goal is an obstacle
        if (grid[start.x][start.y].obstacle || grid[goal.x][goal.y].obstacle) {
            return {};
        }

        // Custom comparator for priority_queue
        auto cmp = [](Node* left, Node* right) { return left->f > right->f; };
        std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> openList(cmp);
        std::unordered_map<Node, Node*, Node::Hash> nodeMap;

        // Initialize start node
        Node* startNode = &grid[start.x][start.y];
        startNode->g = 0;
        startNode->h = heuristic(*startNode, goal);
        startNode->f = startNode->g + startNode->h;
        openList.push(startNode);
        nodeMap[*startNode] = startNode;

        // Directions: up, down, left, right, and diagonals (8-way movement)
        const int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
        const int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};
        const float cost[] = {1.0, 1.0, 1.0, 1.0, 1.414, 1.414, 1.414, 1.414};

        while (!openList.empty()) {
            Node* current = openList.top();
            openList.pop();

            if (current->x == goal.x && current->y == goal.y) {
                // Reconstruct path
                std::vector<Node*> path;
                while (current != nullptr) {
                    path.push_back(current);
                    current = current->parent;
                }
                std::reverse(path.begin(), path.end());
                return path;
            }

            for (int i = 0; i < 8; ++i) {
                int nx = current->x + dx[i];
                int ny = current->y + dy[i];

                // Check bounds and obstacles
                if (nx < 0 || nx >= height || ny < 0 || ny >= width || grid[nx][ny].obstacle)
                    continue;

                Node* neighbor = &grid[nx][ny];
                float tentative_g = current->g + cost[i];

                // Check if we found a better path
                auto it = nodeMap.find(*neighbor);
                if (it == nodeMap.end() || tentative_g < neighbor->g) {
                    neighbor->parent = current;
                    neighbor->g = tentative_g;
                    neighbor->h = heuristic(*neighbor, goal);
                    neighbor->f = neighbor->g + neighbor->h;

                    if (it == nodeMap.end()) {
                        openList.push(neighbor);
                        nodeMap[*neighbor] = neighbor;
                    }
                }
            }
        }

        return {}; // No path found
    }

    void visualizePath(const std::vector<Node*>& path) {
        // Create a copy of the grid for visualization
        std::vector<std::vector<char>> display(height, std::vector<char>(width, '.'));

        // Mark obstacles
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (grid[i][j].obstacle) {
                    display[i][j] = '#';
                }
            }
        }

        // Mark path
        for (Node* node : path) {
            display[node->x][node->y] = '*';
        }

        // Mark start and goal if path exists
        if (!path.empty()) {
            display[path.front()->x][path.front()->y] = 'S';
            display[path.back()->x][path.back()->y] = 'G';
        }

        // Print the grid
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                std::cout << display[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    // Create a 10x10 grid
    AStar astar(10, 10);

    // Add some obstacles
    for (int i = 3; i <= 7; ++i) {
        astar.setObstacle(i, 5);
    }
    astar.setObstacle(2, 4);
    astar.setObstacle(2, 6);

    // Define start and goal nodes
    Node start(0, 0);
    Node goal(9, 9);

    // Find path
    std::vector<Node*> path = astar.findPath(start, goal);

    // Display results
    if (path.empty()) {
        std::cout << "No path found!" << std::endl;
    } else {
        std::cout << "Path found with " << path.size() << " steps:" << std::endl;
        astar.visualizePath(path);
        
        // Print coordinates of the path
        std::cout << "\nPath coordinates:\n";
        for (Node* node : path) {
            std::cout << "(" << node->x << ", " << node->y << ") ";
        }
        std::cout << std::endl;
    }

    return 0;
}