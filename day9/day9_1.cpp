#include <iostream>
#include <fstream>
#include <string>
#include <vector>

constexpr int FREE = -1;

std::vector<int> undense(const std::vector<int> &denseDiskMap) {
    std::vector<int> result;

    for (int i = 0; i < denseDiskMap.size(); i++) {
        const auto digit = denseDiskMap[i];
        result.insert(result.end(), digit, i % 2 ? FREE : i / 2);
    }
    return result;
}

void fragment(std::vector<int> &diskMap) {
    auto freeCursor = 0;
    auto fileCursor = diskMap.size() - 1;
    while (true) {
        while (diskMap[freeCursor] != FREE) { freeCursor++; }
        while (diskMap[fileCursor] == FREE) { fileCursor--; }
        if (freeCursor >= fileCursor) { break; }
        const auto temp = diskMap[freeCursor];
        diskMap[freeCursor] = diskMap[fileCursor];
        diskMap[fileCursor] = temp;
    }
}

auto main() -> int {
    std::ifstream file("./day9/input"); // open this file for reading
    if (!file) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    std::string denseDiskMapString;
    std::string line;
    while (std::getline(file, line)) {
        denseDiskMapString += line;
    }
    file.close();

    std::vector<int> denseDiskMap;
    denseDiskMap.reserve(denseDiskMapString.length());

    for (char c: denseDiskMapString) {
        denseDiskMap.push_back(c - '0');
    }

    auto diskMap = undense(denseDiskMap);

    fragment(diskMap);

    for (int i: diskMap) { std::cout << i << " "; }

    long long result = 0;
    for (int i = 0; i < diskMap.size(); i++) {
        if (diskMap[i] != FREE) {
            result += i * diskMap[i];
        }
    }

    std::cout << "\n\nResult: " << result << '\n';
    return 0;
}
