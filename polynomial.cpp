#include <bits/stdc++.h>
#include <nlohmann/json.hpp> // Include JSON library
#include <fstream>
using namespace std;
using json = nlohmann::json;

// Function to decode a string in a given base into long long
long long decodeValue(const string &val, int base) {
    long long result = 0;
    for (char c : val) {
        int digit;
        if (isdigit(c)) digit = c - '0';
        else if (isalpha(c)) digit = tolower(c) - 'a' + 10;
        else throw invalid_argument("Invalid character in value");
        if (digit >= base) throw invalid_argument("Digit out of range for base");
        result = result * base + digit;
    }
    return result;
}

// Function to compute Lagrange Interpolation at x=0 (constant term)
long long lagrangeInterpolation(const vector<pair<long long, long long>> &points, int k) {
    long long c = 0;
    int used = min((int)points.size(), k);

    for (int i = 0; i < used; i++) {
        long double term = points[i].second;
        for (int j = 0; j < used; j++) {
            if (i == j) continue;
            term *= (0.0 - points[j].first);
            term /= (points[i].first - points[j].first);
        }
        c += llround(term);
    }
    return c;
}

int main() {
    // Path to your JSON file
    string path = "C:\\Users\\nachi\\Desktop\\Hashira Assignment\\data.json";
    ifstream inFile(path);
    if (!inFile.is_open()) {
        cerr << "Error opening file: " << path << endl;
        return 1;
    }

    json input;
    inFile >> input;

    int n = input["keys"]["n"];
    int k = input["keys"]["k"];

    vector<pair<long long, long long>> points;

    for (auto it = input.begin(); it != input.end(); ++it) {
        if (it.key() == "keys") continue;

        long long x = stoll(it.key());
        int base = stoi(it.value()["base"].get<string>());
        string val = it.value()["value"].get<string>();

        long long y = decodeValue(val, base);
        points.push_back({x, y});
    }

    // Compute constant c
    long long c = lagrangeInterpolation(points, k);

    cout << c << endl;
    return 0;
}
