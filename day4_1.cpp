#include <iostream>
#include <fstream>
#include <string>
#include <list>

std::string get(std::list<std::string> _list, const int _i){
    auto it = _list.begin();
    for(int i=0; i<_i; i++){
        ++it;
    }
    return *it;
}

int main() {
    std::ifstream file("./day4_input"); // open file for reading
    if (!file) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    std::string word = "XMAS";

    long result = 0;

    std::list<std::string> buffer;
    int lineIndex = -3;

    std::string line;
    while (std::getline(file, line)) {
        buffer.push_back(line);

        if (lineIndex >= 0) {
            auto lineLength = get(buffer,lineIndex).length();

            for (int i = 0; i < lineLength; i++) {
                std::string word360;
                std::string word45;
                std::string word90;
                std::string word135;
                std::string word180;
                std::string word225;
                std::string word270;
                std::string word315;

                for (int wi = 0; wi < word.length(); wi++) {
                    auto up = lineIndex - wi;
                    auto down = lineIndex + wi;
                    auto left = i - wi;
                    auto right = i + wi;

                    if (right < lineLength) {
                        word360.push_back(get(buffer, lineIndex)[right]);
                    }
                    if (up >= 0 && right < lineLength) {
                        word45.push_back(get(buffer, up)[right]);
                    }
                    if (up >= 0) {
                        word90.push_back(get(buffer, up)[i]);
                    }
                    if (up >= 0 && left >= 0) {
                        word135.push_back(get(buffer, up)[left]);
                    }
                    if (left >= 0) {
                        word180.push_back(get(buffer, lineIndex)[left]);
                    }
                    if (down < buffer.size() && left >= 0) {
                        word225.push_back(get(buffer, down)[left]);
                    }
                    if (down < buffer.size()) {
                        word270.push_back(get(buffer, down)[i]);
                    }
                    if (down < buffer.size() && right < lineLength) {
                        word315.push_back(get(buffer, down)[right]);
                    }
                }
                if (word360 == word) {
                    result++;
                }
                if (word45 == word) {
                    result++;
                }
                if (word90 == word) {
                    result++;
                }
                if (word135 == word) {
                    result++;
                }
                if (word180 == word) {
                    result++;
                }
                if (word225 == word) {
                    result++;
                }
                if (word270 == word) {
                    result++;
                }
                if (word315 == word) {
                    result++;
                }
            }
        }
        if (lineIndex == 3) {
            buffer.pop_front();
        }
        if (lineIndex < 3) {
            lineIndex++;
        }
    }
    while (buffer.size() > 3) {
        if (lineIndex >= 0) {
            auto lineLength = get(buffer,lineIndex).length();

            for (int i = 0; i < lineLength; i++) {
                std::string word360;
                std::string word45;
                std::string word90;
                std::string word135;
                std::string word180;

                for (int wi = 0; wi < word.length(); wi++) {
                    auto up = lineIndex - wi;
                    auto left = i - wi;
                    auto right = i + wi;

                    if (right < lineLength) {
                        word360.push_back(get(buffer, lineIndex)[right]);
                    }
                    if (up >= 0 && right < lineLength) {
                        word45.push_back(get(buffer, up)[right]);
                    }
                    if (up >= 0) {
                        word90.push_back(get(buffer, up)[i]);
                    }
                    if (up >= 0 && left >= 0) {
                        word135.push_back(get(buffer, up)[left]);
                    }
                    if (left >= 0) {
                        word180.push_back(get(buffer, lineIndex)[left]);
                    }
                }
                if (word360 == word) {
                    result++;
                }
                if (word45 == word) {
                    result++;
                }
                if (word90 == word) {
                    result++;
                }
                if (word135 == word) {
                    result++;
                }
                if (word180 == word) {
                    result++;
                }
            }
        }

        buffer.pop_front();
    }

    std::cout << result << '\n';

    file.close();
    return 0;
}
