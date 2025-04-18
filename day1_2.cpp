#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <string>

int main() {
    std::ifstream file("./day1_input"); // open file for reading
    if (!file) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    std::list<long> leftList;
    std::list<long> rightList;

    std::string line;
    while (std::getline(file, line)) {
        auto leftNumber = stol(line.substr(0, line.find(' ')));
        leftList.push_back(leftNumber);

        auto rightNumber = stol(line.substr(line.find_last_of(' ') + 1));
        rightList.push_back(rightNumber);
    }

    std::map<long, unsigned int> rightQuantitiesMap;

    long result = 0;

    for (long & leftIt : leftList) {
        unsigned int quant;
        if (rightQuantitiesMap.count(leftIt) > 0) {
            quant = rightQuantitiesMap[leftIt];
        } else {
            quant = 0;
            for (long & rightIt : rightList) {
                if (rightIt == leftIt) {
                    quant++;
                }
            }
            rightQuantitiesMap[leftIt] = quant;
        }

        result += quant * leftIt;
    }

    std::cout << result << '\n';

    file.close();
    return 0;
}
