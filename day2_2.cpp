#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int main() {
    std::ifstream file("./day2_input"); // open file for reading
    if (!file) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    long result = 0;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);

        int number;
        std::vector<int> numbers;
        while (iss >> number) {
            numbers.push_back(number);
        }

        for (int i = 0; i < numbers.size(); i++) {
            bool firstReached = false;
            bool secondReached = false;
            int lastNum;
            int lastDiff;
            bool looksGood = true;
            for (int j = 0; j < numbers.size(); j++) {
                if (j != i) {
                    auto num = numbers[j];

                    std::cout << "Num: " << num << '\n';
                    if (!firstReached) {
                        firstReached = true;
                    } else {
                        int diff = num - lastNum;
                        std::cout << "lastDiff: " << lastDiff << "; diff: " << diff << '\n';

                        if (auto absDiff = abs(diff); absDiff < 1 || absDiff > 3) {
                            std::cout << "Looks BAD! Large gap.\n";
                            looksGood = false;
                            break;
                        }

                        if (!secondReached) {
                            secondReached = true;
                        } else {
                            if (diff * lastDiff <= 0) {
                                std::cout << "Looks BAD! Reverse trend.\n";
                                looksGood = false;
                                break;
                            }
                        }
                        lastDiff = diff;
                    }
                    lastNum = num;
                }
            }
            if (looksGood) {
                result++;
                break;
            }
        }
    }

    std::cout << result << '\n';

    file.close();
    return 0;
}
