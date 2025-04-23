#include <iostream>
#include <fstream>
#include <string>
#include <regex>

int main() {
    std::ifstream file("./day3_input"); // open file for reading
    if (!file) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    long result = 0;
    std::regex regex("mul\\(([0-9]{1,3}),([0-9]{1,3})\\)");

    std::string line;
    while (std::getline(file, line)) {

        auto searchStart(line.cbegin());

        std::smatch match;
        while (regex_search(searchStart, line.cend(), match, regex)) {

            result += stol(match[1]) * stol(match[2]);

            for (const auto& m : match) {
                std::cout << m << '\n';
            }
            searchStart = match.suffix().first;
        }
    }

    std::cout << result << '\n';

    file.close();
    return 0;
}
