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

int guardX = -1;
int guardY = -1;
char guardDirection;

/**
* returns false when the guard exits the world, true otherwise
*/
auto iterateWorld() -> bool {
    int forwardX = 0;
    int forwardY = 0;
    char toRight;

    switch (guardDirection) {
        case GUARD_UP:
            forwardY = -1;
            toRight = GUARD_RIGHT;
            break;
        case GUARD_RIGHT:
            forwardX = 1;
            toRight = GUARD_DOWN;
            break;
        case GUARD_DOWN:
            forwardY = 1;
            toRight = GUARD_LEFT;
            break;
        case GUARD_LEFT:
            forwardX = -1;
            toRight = GUARD_UP;
            break;
        default: break;
    }
    int x = guardX;
    int y = guardY;
    while (true) {
        if (x < 0 || x >= world[guardY].size() || y < 0 || y >= world.size()) {
            return false;
        }
        if (world[y][x] == OBSTACLE) {
            guardDirection = toRight;
            guardX = x - forwardX;
            guardY = y - forwardY;
            return true;
        }

        world[y][x] = EMPTY_VISITED;

        x += forwardX;
        y += forwardY;
    }
}

auto main() -> int {
    std::ifstream file("./day6_input"); // open this file for reading
    if (!file) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    long result = 0;

    std::string line;
    int i = 0;
    while (std::getline(file, line)) {
        std::vector<char> vectorLine;
        std::vector<char> solutionLine;
        for (int j = 0; j < line.length(); j++) {
            char element = line[j];
            char solutionElement = element;
            if (element == GUARD_UP || element == GUARD_DOWN || element == GUARD_LEFT || element == GUARD_RIGHT) {
                guardX = j;
                guardY = i;
                guardDirection = element;
                element = EMPTY;
            }
            vectorLine.push_back(element);
            solutionLine.push_back(solutionElement);
        }
        world.push_back(vectorLine);
        i++;
    }
    file.close();

    while (iterateWorld()) {}

    for (auto &row: world) {
        for (const auto &element: row) {
            if (element == EMPTY_VISITED) {
                result++;
            }
        }
    }

    std::cout << "Result: " << result << '\n';
    return 0;
}
