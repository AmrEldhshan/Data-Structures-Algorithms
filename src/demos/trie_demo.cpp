#include "data_structures/trees/trie.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    Trie trie;

    for (const char* word : {"cat", "car", "card", "care", "dog", "do"}) {
        trie.insert(word);
    }

    cout << "Words stored: " << trie.countWords() << "\n\n";

    for (const char* word : {"cat", "ca", "care", "cow"}) {
        cout << "contains(\"" << word << "\") = "
             << (trie.contains(word) ? "true" : "false") << '\n';
    }

    cout << "\nstartsWith(\"car\") = "
         << (trie.startsWith("car") ? "true" : "false") << '\n';

    for (const char* prefix : {"ca", "do", "z"}) {
        vector<string> words = trie.wordsWithPrefix(prefix);
        cout << "prefix \"" << prefix << "\": ";
        if (words.empty()) {
            cout << "(none)";
        } else {
            for (const string& word : words) cout << word << ' ';
        }
        cout << '\n';
    }

    return 0;
}
