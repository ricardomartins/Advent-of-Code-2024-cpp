#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const char GUARD_UP = '^';
const char GUARD_DOWN = 'v';
const char GUARD_LEFT = '<';
const char GUARD_RIGHT = '>';
const char OBSTACLE = '#';
const char EMPTY = '.';
const char EMPTY_VISITED = 'X';

std::vector<std::vector<char> > world;

/**
* returns false when the guard exits the world, true otherwise
*/
auto iterateWorld() -> bool {
    for (int y = 0; y < world.size(); y++) {
        for (int x = 0; x < world[y].size(); x++) {
            const char element = world[y][x];
            int nextX;
            int nextY;
            char toRight;
            switch (element) {
                case GUARD_UP:
                    nextX = x;
                    nextY = y - 1;
                    toRight = GUARD_RIGHT;
                    break;
                case GUARD_RIGHT:
                    nextX = x + 1;
                    nextY = y;
                    toRight = GUARD_DOWN;
                    break;
                case GUARD_DOWN:
                    nextX = x;
                    nextY = y + 1;
                    toRight = GUARD_LEFT;
                    break;
                case GUARD_LEFT:
                    nextX = x - 1;
                    nextY = y;
                    toRight = GUARD_UP;
                    break;
                default: continue;
            }
            world[y][x] = EMPTY_VISITED;
            if (nextX < 0 || nextX >= world[y].size() || nextY < 0 || nextY >= world.size()) {
                return false;
            }
            if (world[nextY][nextX] == OBSTACLE) {
                world[y][x] = toRight;
            } else {
                world[nextY][nextX] = element;
            }
            return true;
        }
    }
    return true;
}

auto main() -> int {
    std::ifstream file("./day6_input"); // open this file for reading
    if (!file) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    long result = 0;

    std::string line;
    while (std::getline(file, line)) {
        std::vector vectorLine(line.begin(), line.end());
        world.push_back(vectorLine);
    }
    file.close();

    while (iterateWorld()) {}

    for (auto &row: world) {
        for (const auto &element: row) {
            if (element == 'X') {
                result++;
            }
        }
    }

    std::cout << "Result: " << result << '\n';
    return 0;
}
