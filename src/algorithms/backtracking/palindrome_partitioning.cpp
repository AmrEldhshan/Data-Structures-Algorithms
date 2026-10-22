#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Palindrome partitioning (backtracking)
//
// Cut the string into pieces so that every piece is a palindrome. At each
// position, try every possible end, recurse on the rest, then remove the piece.
//
// Time:  O(n * 2^n) worst case
// Space: O(n)
// ---------------------------------------------------------------------------
bool isPalindrome(const string& text, int left, int right) {
    while (left < right) {
        if (text[left++] != text[right--]) return false;
    }
    return true;
}

void partition(const string& text, int start, vector<string>& current,
               vector<vector<string>>& results) {
    if (start == static_cast<int>(text.size())) {
        results.push_back(current);
        return;
    }

    for (int end = start; end < static_cast<int>(text.size()); ++end) {
        if (!isPalindrome(text, start, end)) continue;

        current.push_back(text.substr(start, end - start + 1));
        partition(text, end + 1, current, results);
        current.pop_back();
    }
}

int main() {
    string text = "aab";

    vector<vector<string>> results;
    vector<string> current;
    partition(text, 0, current, results);

    cout << "palindrome partitions of \"" << text << "\":\n";
    for (const auto& pieces : results) {
        cout << "  ";
        for (size_t i = 0; i < pieces.size(); ++i) {
            if (i != 0) cout << " | ";
            cout << pieces[i];
        }
        cout << '\n';
    }

    return 0;
}
