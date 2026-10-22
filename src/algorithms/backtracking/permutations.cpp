#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Permutations, combinations, and subsets (backtracking)
//
// All three use the same idea: build a partial answer, recurse, then undo the
// choice. Only the stopping condition and the loop bounds differ.
//
// Permutations: order matters, each element used once.
// Combinations: order does not matter, choose k elements.
// Subsets:      every element is either included or excluded.
// ---------------------------------------------------------------------------
void generatePermutations(string& text, int start,
                          vector<string>& results) {
    if (start == static_cast<int>(text.size())) {
        results.push_back(text);
        return;
    }

    for (int i = start; i < static_cast<int>(text.size()); ++i) {
        swap(text[start], text[i]);
        generatePermutations(text, start + 1, results);
        swap(text[start], text[i]);
    }
}

void generateCombinations(const vector<int>& values, int start, int k,
                          vector<int>& current,
                          vector<vector<int>>& results) {
    if (static_cast<int>(current.size()) == k) {
        results.push_back(current);
        return;
    }

    for (int i = start; i < static_cast<int>(values.size()); ++i) {
        current.push_back(values[i]);
        generateCombinations(values, i + 1, k, current, results);
        current.pop_back();
    }
}

void generateSubsets(const vector<int>& values, int index,
                     vector<int>& current,
                     vector<vector<int>>& results) {
    if (index == static_cast<int>(values.size())) {
        results.push_back(current);
        return;
    }

    // Exclude values[index].
    generateSubsets(values, index + 1, current, results);

    // Include values[index].
    current.push_back(values[index]);
    generateSubsets(values, index + 1, current, results);
    current.pop_back();
}

int main() {
    string letters = "ABC";
    vector<string> permutations;
    generatePermutations(letters, 0, permutations);
    cout << "permutations of ABC: ";
    for (const string& permutation : permutations) cout << permutation << ' ';
    cout << "\n\n";

    vector<int> values = {1, 2, 3, 4};
    vector<int> current;
    vector<vector<int>> combinations;
    generateCombinations(values, 0, 2, current, combinations);
    cout << "2-element combinations of 1..4: ";
    for (const auto& combination : combinations) {
        cout << '(';
        for (int value : combination) cout << value;
        cout << ") ";
    }
    cout << "\n\n";

    vector<vector<int>> subsets;
    generateSubsets(values, 0, current, subsets);
    cout << "subsets of 1..4: ";
    for (const auto& subset : subsets) {
        cout << '{';
        for (int value : subset) cout << value;
        cout << "} ";
    }
    cout << '\n';

    return 0;
}
