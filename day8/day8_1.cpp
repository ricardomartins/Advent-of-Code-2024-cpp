#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

constexpr char EMPTY = '.';

class AntennaType {
public:
    explicit AntennaType(const char type) : type(type) {
    }

    void addLocation(int x, int y) {
        for (auto [otherX, otherY]: locations) {
            const auto xDiff = x - otherX;
            const auto yDiff = y - otherY;
            antinodes.push_back(std::make_pair(x + xDiff, y + yDiff));
            antinodes.push_back(std::make_pair(otherX - xDiff, otherY - yDiff));
        }

        locations.push_back(std::make_pair(x, y));
    }

    void print() {
        std::cout << "Type: " << type << "\nLocations: ";
        for (auto [x, y]: locations)
            std::cout << "(" << x << "," << y << ") ";
        std::cout << "\nAntinodes: ";
        for (auto [x, y]: antinodes)
            std::cout << "(" << x << "," << y << ") ";
        std::cout << '\n';
    }

    std::vector<std::vector<char>> printAsMap(const int width, const int height) {
        std::vector map(height, std::vector(width, EMPTY));
        for (auto [x, y]: locations) {
            if (x >= 0 && x < width && y >= 0 && y < height) {
                map[y][x] = type;
            }
        }
        for (auto [x, y]: antinodes) {
            if (x >= 0 && x < width && y >= 0 && y < height) {
                if (map[y][x] == EMPTY) {
                    map[y][x] = '#';
                } else {
                    map[y][x] = '!';
                }
            }
        }
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                std::cout << map[i][j];
            }
            std::cout << '\n';
        }
        return map;
    }

    std::vector<std::pair<int, int> > getAntinodes() { return antinodes; }

    std::vector<std::vector<char>> getAntinodesAsMap(const int width, const int height) {
        std::vector map(height, std::vector(width, EMPTY));
        for (auto [x, y]: antinodes) {
            if (x >= 0 && x < width && y >= 0 && y < height) {
                if (map[y][x] == EMPTY) {
                    map[y][x] = '#';
                } else {
                    map[y][x] = '!';
                }
            }
        }
        return map;
    }

private:
    char type;
    std::vector<std::pair<int, int> > locations;
    std::vector<std::pair<int, int> > antinodes;
};

auto main() -> int {
    std::ifstream file("./day8/day8_input"); // open this file for reading
    if (!file) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    std::map<char, AntennaType> antennas;
    int width;
    int height;

    std::string line;
    int i = 0;
    while (std::getline(file, line)) {
        width = line.size();
        for (int j = 0; j < width; j++) {
            if (const auto type = line[j]; type != EMPTY) {
                if (antennas.count(type) == 0) {
                    antennas.emplace(type, AntennaType(type));
                }
                antennas.at(type).addLocation(j, i);
            }
        }
        i++;
    }
    file.close();
    height = i;

    long result = 0;

    std::vector map(height, std::vector(width, EMPTY));

    for (auto [type, antenna]: antennas) {
        antenna.print();
        auto antennaMap = antenna.getAntinodesAsMap(width, height);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (antennaMap[i][j] != EMPTY) {
                    if (map[i][j] == EMPTY) {
                        map[i][j] = antennaMap[i][j];
                    } else {
                        map[i][j] = '!';
                    }
                }
            }
        }
    }

    std::cout << '\n';
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j] != EMPTY) {
                result++;
            }
            std::cout << map[i][j];
        }
        std::cout << '\n';
    }

    std::cout << "Result: " << result << '\n';
    return 0;
}
