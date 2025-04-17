#include <iostream>
#include <string>
#include <cctype>

std::string columnToLetters(int col) {
    std::string result;
    while (col > 0) {
        col--; // Adjust for 1-based indexing
        result = char('A' + (col % 26)) + result;
        col /= 26;
    }
    return result;
}

int lettersToColumn(const std::string& letters) {
    int col = 0;
    for (char c : letters) {
        col = col * 26 + (c - 'A' + 1);
    }
    return col;
}

void convertSpreadsheetNotation(const std::string& input) {
    if (input[0] == 'R' && std::isdigit(input[1]) && input.find('C') != std::string::npos) {
        // RXCY format
        int row, col;
        sscanf(input.c_str(), "R%dC%d", &row, &col);
        std::cout << columnToLetters(col) << row << '\n';
    } else {
        // Excel-style format
        std::string letters;
        int row = 0;
        for (char c : input) {
            if (std::isalpha(c)) {
                letters += c;
            } else {
                row = row * 10 + (c - '0');
            }
        }
        std::cout << "R" << row << "C" << lettersToColumn(letters) << '\n';
    }
}

int main() {
    int n;
    std::cin >> n;
    while (n--) {
        std::string input;
        std::cin >> input;
        convertSpreadsheetNotation(input);
    }
    return 0;
}