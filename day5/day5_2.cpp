#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <array>
#include <sstream>
#include <vector>

bool makeValid(std::vector<int> & numbers, const std::list<std::array<int, 2>> & rules) {
    bool finalValid = true;

    bool valid = true;
    do {
        valid = true;
        for (int i = 0; i < numbers.size() - 1; i++) {
            const int first = numbers[i];
            for (int j = i + 1; j < numbers.size(); j++) {
                const int second = numbers[j];

                for (auto rule: rules) {
                    if (first == rule[1] && second == rule[0]) {
                        const int temp = numbers[i];
                        numbers[i] = numbers[j];
                        numbers[j] = temp;

                        valid = false;
                        finalValid = false;
                    }
                }
            }
        }
    } while(!valid);
    return finalValid;
}

int main() {
    std::ifstream file("./day5_input"); // open file for reading
    if (!file) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    long result = 0;
    long validAmount = 0;
    long invalidAmount = 0;

    std::list<std::array<int, 2>> rules;

    std::string line;
    while (std::getline(file, line)) {
        if (line.find('|') != std::string::npos) {
            line.replace(line.find('|'), 1, " ");

            std::istringstream iss(line);
            std::array<int, 2> rule{};
            int number;
            int ruleIndex = 0;
            while (iss >> number) {
                rule[ruleIndex++] = number;
            }
            rules.push_back(rule);
            std::cout << "Rule: " << rule[0] << '|' << rule[1] << '\n';
        } else if (line.find(',') != std::string::npos) {
            std::cout << "Update: " << line << '\n';

            for (int i = 0; i < line.length(); i++) {
                if (line[i] == ',') {
                    line[i] = ' ';
                }
            }

            std::vector<int> numbers;
            int number;
            std::istringstream iss(line);
            while (iss >> number) {
                numbers.push_back(number);
            }

            if (!makeValid(numbers, rules)) {
                result += numbers[numbers.size() / 2];
                invalidAmount++;
            } else {
                validAmount++;
            }
        }
    }
    file.close();

    std::cout << "Result: " << result << '\n';
    std::cout << "Valid amount: " << validAmount << '\n';
    std::cout << "Invalid amount: " << invalidAmount << '\n';
    return 0;
}
