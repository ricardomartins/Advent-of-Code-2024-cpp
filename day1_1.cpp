#include <iostream>
#include <fstream>
#include <list>
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
        long leftNumber = stol(line.substr(0, line.find(' ')));
        leftList.push_back(leftNumber);

        long rightNumber = stol(line.substr(line.find_last_of(' ') + 1));
        rightList.push_back(rightNumber);
    }
    leftList.sort();
    rightList.sort();

    long result = 0;

    std::list<long>::iterator leftIt;
    std::list<long>::iterator rightIt;
    for (leftIt = leftList.begin(), rightIt = rightList.begin(); leftIt != leftList.end() && rightIt != rightList.end(); ++leftIt, ++rightIt){
        result += labs(*leftIt - *rightIt);
    }
    std::cout << result << '\n';

    file.close();
    return 0;
}
