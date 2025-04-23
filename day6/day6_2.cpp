#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const char OBSTACLE = '#';
const char EMPTY = '.';
const char EMPTY_SOLUTION = 'O';

class Guard {
public:
    enum class Direction : char {
        UP = '^',
        RIGHT = '>',
        DOWN = 'v',
        LEFT = '<',
    };

    Guard(const int x, const int y, const Direction direction) : x(x), y(y), direction(direction) {
    }

    void move() {
        switch (direction) {
            case Direction::UP:
                y--;
                break;
            case Direction::DOWN:
                y++;
                break;
            case Direction::LEFT:
                x--;
                break;
            case Direction::RIGHT:
                x++;
                break;
        }
    }

    void turnRight() {
        switch (direction) {
            case Direction::UP:
                direction = Direction::RIGHT;
                break;
            case Direction::DOWN:
                direction = Direction::LEFT;
                break;
            case Direction::LEFT:
                direction = Direction::UP;
                break;
            case Direction::RIGHT:
                direction = Direction::DOWN;
                break;
        }
    }

    [[nodiscard]] int getX() const { return x; }
    [[nodiscard]] int getY() const { return y; }
    [[nodiscard]] Direction getDirection() const { return direction; }

    [[nodiscard]] int getNextX() const {
        return x + (direction == Direction::RIGHT ? 1 : direction == Direction::LEFT ? -1 : 0);
    }

    [[nodiscard]] int getNextY() const {
        return y + (direction == Direction::DOWN ? 1 : direction == Direction::UP ? -1 : 0);
    }

    [[nodiscard]] int getPreviousX() const {
        return -getNextX();
    }

    [[nodiscard]] int getPreviousY() const {
        return -getNextY();
    }

private:
    int x;
    int y;
    Direction direction;
};

Guard guard(-1, -1, Guard::Direction::UP);

std::vector<std::vector<char> > world;

[[nodiscard]] bool findLoopForObstacleIn(const int obstacleX, const int obstacleY, Guard virtualGuard) {
    std::cout << "Searching loop for : " << obstacleX << " , " << obstacleY << '\n';

    std::vector<std::pair<int, int> > foundObstacles;

    while (true) {
        const int currentX = virtualGuard.getX();
        const int currentY = virtualGuard.getY();
        const int nextX = virtualGuard.getNextX();
        const int nextY = virtualGuard.getNextY();

        // Guard left the world
        if (currentX < 0 || currentX >= world[currentY].size() || currentY < 0 || currentY >= world.size()) {
            std::cout << "Loop NOT FOUND for: " << obstacleX << " , " << obstacleY << '\n';
            std::cout << "Found obstacles: " << '\n';
            for (auto &foundObstacle: foundObstacles) {
                std::cout << "- " << foundObstacle.first << " , " << foundObstacle.second << '\n';
            }
            return false;
        }

        // Guard found an obstacle, so turn
        if (nextX >= 0 && nextX < world[nextY].size() && nextY >= 0 && nextY < world.size() &&
            world[nextY][nextX] == OBSTACLE || (obstacleX == nextX && obstacleY == nextY)
        ) {
            virtualGuard.turnRight();

            foundObstacles.emplace_back(nextX, nextY);

            if (foundObstacles.size() > 3) {
                const std::pair<int, int> beforeLastObstacle = foundObstacles[foundObstacles.size() - 2];
                const std::pair<int, int> lastObstacle = foundObstacles[foundObstacles.size() - 1];
                for (int i = foundObstacles.size() - 4; i >= 0; i--) {
                    if (beforeLastObstacle.first == foundObstacles[i].first &&
                        beforeLastObstacle.second == foundObstacles[i].second &&
                        lastObstacle.first == foundObstacles[i + 1].first &&
                        lastObstacle.second == foundObstacles[i + 1].second
                    ) {
                        std::cout << "Loop WAS FOUND for: " << obstacleX << " , " << obstacleY << '\n';
                        std::cout << "Found obstacles: " << '\n';
                        for (auto &foundObstacle: foundObstacles) {
                            std::cout << "- " << foundObstacle.first << " , " << foundObstacle.second << '\n';
                        }
                        return true;
                    }
                }
            }
            continue;
        }

        // Go forward
        virtualGuard.move();
    }
}

void simulateWorld() {
    Guard originalGuard(guard.getX(), guard.getY(), guard.getDirection());
    while (true) {
        const int currentX = guard.getX();
        const int currentY = guard.getY();
        const int nextX = guard.getNextX();
        const int nextY = guard.getNextY();

        // Guard left the world
        if (currentX < 0 || currentX >= world[currentY].size() || currentY < 0 || currentY >= world.size()) {
            return;
        }

        if (nextX >= 0 && nextX < world[nextY].size() && nextY >= 0 && nextY < world.size()) {
            // Guard found an obstacle, so turn
            if (world[nextY][nextX] == OBSTACLE) {
                guard.turnRight();
                continue;
            }

            if (findLoopForObstacleIn(nextX, nextY, Guard(originalGuard.getX(), originalGuard.getY(), originalGuard.getDirection()))) {
                world[nextY][nextX] = EMPTY_SOLUTION;
            }
        }

        // Go forward
        guard.move();
    }
}

auto main() -> int {
    std::ifstream file("./day6_input"); // open this file for reading
    if (!file) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    std::string line;
    int i = 0;
    while (std::getline(file, line)) {
        std::vector<char> vectorLine;
        std::vector<char> solutionLine;
        for (int j = 0; j < line.length(); j++) {
            char element = line[j];
            char solutionElement = element;
            if (element == static_cast<char>(Guard::Direction::UP) ||
                element == static_cast<char>(Guard::Direction::DOWN) ||
                element == static_cast<char>(Guard::Direction::LEFT) ||
                element == static_cast<char>(Guard::Direction::RIGHT)) {
                guard = Guard(j, i, static_cast<Guard::Direction>(element));
                element = EMPTY;
            }
            vectorLine.push_back(element);
            solutionLine.push_back(solutionElement);
        }
        world.push_back(vectorLine);
        i++;
    }
    file.close();

    simulateWorld();

    int result = 0;

    for (auto &row: world) {
        for (const auto &element: row) {
            if (element == EMPTY_SOLUTION) {
                result++;
            }
        }
    }

    std::cout << "Result: " << result << '\n';
    return 0;
}
