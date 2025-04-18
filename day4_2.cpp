#include <iostream>
#include <fstream>
#include <string>
#include <list>

bool isXmas(const char(* strs)[3]) {
    const std::string word = "MAS";
    const std::string reverseWord = "SAM";

    std::string slash;
    std::string reverseSlash;
    for(int i=0; i < 3; i++) {
        slash.push_back(strs[i][i]);
        reverseSlash.push_back(strs[2 - i][i]);
    }
    return (slash == word || slash == reverseWord) && (reverseSlash == word || reverseSlash == reverseWord);
}

int main() {
    std::ifstream file("./day4_input"); // open file for reading
    if (!file) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    long result = 0;

    std::list<std::string> buffer;

    std::string line;
    while (std::getline(file, line)) {
        buffer.push_back(line);
        if (buffer.size() > 3) {
            buffer.pop_front();
        }
        if (buffer.size() == 3) {
            for (int i = 0; i < line.size() - 2; i++){
                char square[3][3];

                int m = 0;
                for (auto bufferLine: buffer){
                    for (int n = 0; n < 3; n++){
                        square[m][n] = bufferLine[i + n];
                    }
                    m++;
                }

                if (isXmas(square)) {
                    result++;
                }
            }
        }
    }
    file.close();

    std::cout << result << '\n';
    return 0;
}
