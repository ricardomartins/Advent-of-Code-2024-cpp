#include <complex>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

auto main() -> int {
    std::ifstream file("./day7/day7_input"); // open this file for reading
    if (!file) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    long result = 0;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);

        long long leftTerm;
        char limiter;
        std::vector<int> rightTerms;
        iss >> leftTerm >> limiter;
        int num;
        while (iss >> num) {
            rightTerms.push_back(num);
        }
        std::cout << "Left: " << leftTerm << "; Right: ";
        for (auto rightTerm: rightTerms) {
            std::cout << rightTerm << " ";
        }
        std::cout << '\n';

        int operators = std::pow(3, rightTerms.size() - 1) - 1;
        std::cout << "Initial operators: " << operators << '\n';
        for (; operators >= 0; operators--) {
            unsigned int currentOperators = operators;

            long long partialResult = rightTerms[0];
            std::cout << partialResult;
            for (int i = 1; i < rightTerms.size(); i++) {
                auto opera = currentOperators % 3;

                switch (opera) {
                    case 0:
                        std::cout << " + " << rightTerms[i];
                        partialResult += rightTerms[i];
                        break;
                    case 1:
                        std::cout << " * " << rightTerms[i];
                        partialResult *= rightTerms[i];
                        break;
                    case 2:
                        std::cout << " || " << rightTerms[i];
                        auto term = rightTerms[i];
                        while (term > 0) {
                            partialResult *= 10;
                            term /= 10;
                        }
                        partialResult += rightTerms[i];
                        break;
                }

                currentOperators /= 3;
            }
            std::cout << " = " << partialResult << '\n';
            if (partialResult == leftTerm) {
                std::cout << "Correct calibration found: " << partialResult << '\n';
                result += partialResult;
                break;
            }
        }
    }
    file.close();

    std::cout << "Result: " << result << '\n';
    return 0;
}
