#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

auto columnToLetters = [](int col) {
    string result;
    while (col > 0) {
        col--;
        result.insert(result.begin(), char('A' + (col % 26)));
        col /= 26;
    }
    return result;
};

auto lettersToColumn = [](const string& letters) {
    return accumulate(letters.begin(), letters.end(), 0,
        [](int acc, char c) { return acc * 26 + (c - 'A' + 1); });
};

auto convert = [](const string& input) {
    if (input[0] == 'R' && isdigit(input[1]) && input.find('C') != string::npos) {
        auto cPos = input.find('C');
        int row = stoi(input.substr(1, cPos - 1));
        int col = stoi(input.substr(cPos + 1));
        return columnToLetters(col) + to_string(row);
    } else {
        string letters, digits;
        for (char c : input) isalpha(c) ? letters.push_back(c) : digits.push_back(c);
        return "R" + digits + "C" + to_string(lettersToColumn(letters));
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<string> inputs(n), outputs(n);
    for (int i = 0; i < n; i++) cin >> inputs[i];
    #pragma omp parallel for
    for (int i = 0; i < n; i++) outputs[i] = convert(inputs[i]);
    for (auto& out : outputs) cout << out << '\n';
}
