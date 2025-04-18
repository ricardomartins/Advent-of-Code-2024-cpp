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
    std::regex regex(R"((mul)\(([0-9]{1,3}),([0-9]{1,3})\)|(do)\(\)|(don't)\(\))");
    bool enabled = true;

    std::string line;
    while (std::getline(file, line)) {

        auto searchStart(line.cbegin());

        std::smatch match;
        while (regex_search(searchStart, line.cend(), match, regex)) {
            for (const auto& m : match) {
                std::cout << m << '\n';
            }

            if (match[4] == "do") {
                std::cout << "Enabling" << '\n';
                enabled = true;
            } else if (match[5] == "don't") {
                std::cout << "Disabling" << '\n';
                enabled = false;
            } else if (match[1] == "mul" && enabled) {
                std::cout << "Multiplying" << '\n';
                result += stol(match[2]) * stol(match[3]);
            }

            searchStart = match.suffix().first;
        }
    }

    std::cout << result << '\n';

    file.close();
    return 0;
}
