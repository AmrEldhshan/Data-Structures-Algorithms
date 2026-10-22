#include "data_structures/trees/radix_tree.h"

#include <iostream>
#include <string>

using namespace std;

int main() {
    RadixTree tree;
    for (const char* word : {"car", "cart", "carbon", "dog", "do", "dot"}) {
        tree.insert(word);
    }

    cout << "words (" << tree.size() << "): ";
    for (const string& word : tree.words()) cout << word << ' ';
    cout << '\n';

    for (const char* word : {"car", "cart", "ca", "dog", "dodge"}) {
        cout << "contains \"" << word << "\": " << boolalpha
             << tree.contains(word) << '\n';
    }

    cout << "prefix \"car\" count: " << tree.countPrefix("car") << '\n';
    cout << "prefix \"do\" count: " << tree.countPrefix("do") << '\n';

    return 0;
}
