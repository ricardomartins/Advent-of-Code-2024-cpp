#include <iostream>
#include <fstream>
#include <string>
#include <vector>

constexpr char GUARD_UP = '^';
constexpr char GUARD_DOWN = 'v';
constexpr char GUARD_LEFT = '<';
constexpr char GUARD_RIGHT = '>';
constexpr char OBSTACLE = '#';
constexpr char EMPTY = '.';
constexpr char EMPTY_VISITED_BASE = 0b11110000;
constexpr char EMPTY_VISITED_UP_FLAG = 0b00001000;
constexpr char EMPTY_VISITED_DOWN_FLAG = 0b00000100;
constexpr char EMPTY_VISITED_LEFT_FLAG = 0b00000010;
constexpr char EMPTY_VISITED_RIGHT_FLAG = 0b00000001;
constexpr char SOLUTION = 'O';

std::vector<std::vector<char> > world;
std::vector<std::vector<char> > solution;

int guardX = -1;
int guardY = -1;
char guardDirection;

void print_world_state() {
    std::cout << "\nEstado atual do mundo:" << std::endl;
    for (const auto& linha : world) {
        for (const char element : linha) {
            // Verifica se é um elemento visitado (com flags)
            if ((element & EMPTY_VISITED_BASE) == EMPTY_VISITED_BASE) {
                const bool vertical = element & EMPTY_VISITED_UP_FLAG || element & EMPTY_VISITED_DOWN_FLAG;
                const bool horizontal = element & EMPTY_VISITED_LEFT_FLAG || element & EMPTY_VISITED_RIGHT_FLAG;

                if (vertical && horizontal) {
                    std::cout << '+';
                } else if (vertical) {
                    std::cout << '|';
                } else if (horizontal) {
                    std::cout << '-';
                } else {
                    std::cout << '.';
                }
            } else {
                std::cout << element;
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Guard position: (" << guardX << ", " << guardY << "), Direction: " << guardDirection << std::endl;
    std::cout << "------------------------" << std::endl;
}

/**
* returns false when the guard exits the world, true otherwise
*/
auto iterateWorld() -> bool {
    print_world_state();

    int forwardX = 0;
    int forwardY = 0;
    char toRight;
    char visitedFlag;
    char toRightVisitedFlag;
    char fromRightVisitedFlag;
    switch (guardDirection) {
        case GUARD_UP:
            forwardY = -1;
            toRight = GUARD_RIGHT;
            visitedFlag = EMPTY_VISITED_UP_FLAG;
            toRightVisitedFlag = EMPTY_VISITED_RIGHT_FLAG;
            fromRightVisitedFlag = EMPTY_VISITED_LEFT_FLAG;
            break;
        case GUARD_RIGHT:
            forwardX = 1;
            toRight = GUARD_DOWN;
            visitedFlag = EMPTY_VISITED_RIGHT_FLAG;
            toRightVisitedFlag = EMPTY_VISITED_DOWN_FLAG;
            fromRightVisitedFlag = EMPTY_VISITED_UP_FLAG;
            break;
        case GUARD_DOWN:
            forwardY = 1;
            toRight = GUARD_LEFT;
            visitedFlag = EMPTY_VISITED_DOWN_FLAG;
            toRightVisitedFlag = EMPTY_VISITED_LEFT_FLAG;
            fromRightVisitedFlag = EMPTY_VISITED_RIGHT_FLAG;
            break;
        case GUARD_LEFT:
            forwardX = -1;
            toRight = GUARD_UP;
            visitedFlag = EMPTY_VISITED_LEFT_FLAG;
            toRightVisitedFlag = EMPTY_VISITED_UP_FLAG;
            fromRightVisitedFlag = EMPTY_VISITED_DOWN_FLAG;
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
            break;
        }
        if (world[y][x] & toRightVisitedFlag) {
            if (solution[y + forwardY][x + forwardX] == EMPTY) {
                solution[y + forwardY][x + forwardX] = SOLUTION;
            }
        }
        world[y][x] |= visitedFlag;

        x += forwardX;
        y += forwardY;
    }
    x = guardX - forwardX;
    y = guardY - forwardY;
    while (true) {
        if (x < 0 || x >= world[guardY].size() || y < 0 || y >= world.size() || world[y][x] == OBSTACLE) {
            break;
        }

        /*
         * ^ - y-1 -> x-1
         * > - x+1 -> y-1
         * v - y+1 -> x+1
         * < - x-1 -> y+1
         */
        if (world[y][x] & fromRightVisitedFlag) {
            if (solution[y + forwardX][x - forwardY] == EMPTY) {
                solution[y + forwardX][x - forwardY] = SOLUTION;
            }
        }

        world[y][x] |= visitedFlag;

        x -= forwardX;
        y -= forwardY;
    }

    return true;
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
            if (element == GUARD_UP || element == GUARD_DOWN || element == GUARD_LEFT || element == GUARD_RIGHT) {
                guardX = j;
                guardY = i;
                guardDirection = element;
                element = EMPTY_VISITED_BASE;
            } else if (element == EMPTY) {
                element = EMPTY_VISITED_BASE;
            }
            vectorLine.push_back(element);
            solutionLine.push_back(solutionElement);
        }
        solution.push_back(solutionLine);
        world.push_back(vectorLine);
        i++;
    }
    file.close();

    while (iterateWorld()) {
    }

    long result = 0;

    for (auto &row: solution) {
        for (const auto &element: row) {
            if (element == SOLUTION) {
                result++;
            }
        }
    }

    std::cout << "Result: " << result << '\n';
    return 0;
}