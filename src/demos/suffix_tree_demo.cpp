#include "data_structures/trees/suffix_tree.h"

#include <iostream>
#include <string>

using namespace std;

int main() {
    string text = "banana";
    SuffixTree tree(text);

    cout << "text: " << text << '\n';
    cout << "suffixes inserted: " << tree.suffixCount() << '\n';

    for (const char* pattern : {"ana", "ban", "nan", "xyz", "a"}) {
        cout << "  \"" << pattern << "\": contains = " << boolalpha
             << tree.contains(pattern)
             << ", occurrences = " << tree.occurrences(pattern) << '\n';
    }

    return 0;
}
