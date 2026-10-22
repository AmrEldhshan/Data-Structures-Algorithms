#include "data_structures/probabilistic/count_min_sketch.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    CountMinSketch<string> sketch(64, 4);

    vector<string> words = {"apple", "banana", "apple", "cherry", "apple",
                            "banana", "date", "cherry", "apple"};
    for (const string& word : words) sketch.add(word);

    cout << "frequency estimates:\n";
    for (const char* word : {"apple", "banana", "cherry", "date", "elder"}) {
        cout << "  " << word << " -> " << sketch.estimate(word) << '\n';
    }

    cout << "width = " << sketch.width() << ", depth = " << sketch.depth()
         << '\n';

    return 0;
}
