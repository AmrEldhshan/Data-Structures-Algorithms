#include "data_structures/strings/suffix_automaton.h"

#include <iostream>
#include <string>

using namespace std;

int main() {
    string text = "abracadabra";
    SuffixAutomaton automaton(text);

    cout << "text: " << text << '\n';
    cout << "states: " << automaton.stateCount() << '\n';
    cout << "distinct substrings: " << automaton.distinctSubstrings() << '\n';

    for (const char* pattern : {"abra", "cad", "xyz", "a", "bra"}) {
        cout << "  contains \"" << pattern << "\": " << boolalpha
             << automaton.contains(pattern)
             << ", occurrences = " << automaton.occurrences(pattern) << '\n';
    }

    return 0;
}
