#include <array>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Aho-Corasick
//
// Multi-pattern matching in one pass over the text:
//   1. Build a trie of all patterns.
//   2. Add failure links, similar to KMP's prefix function but for a tree.
//   3. Walk the text; every node reached reports all patterns ending there.
//
// Time:  O(total pattern length + text length + matches)
// Space: O(total pattern length * alphabet)
// ---------------------------------------------------------------------------
class AhoCorasick {
public:
    explicit AhoCorasick(const vector<string>& patterns) : patterns_(patterns) {
        nodes_.push_back(Node{});
        for (int i = 0; i < static_cast<int>(patterns.size()); ++i) {
            insert(patterns[i], i);
        }
        buildFailureLinks();
    }

    vector<pair<int, int>> search(const string& text) const {
        vector<pair<int, int>> matches; // (position, pattern index)
        int state = 0;

        for (int position = 0; position < static_cast<int>(text.size()); ++position) {
            int letter = text[position] - 'a';
            state = nodes_[state].next[letter];

            for (int patternIndex : nodes_[state].output) {
                int start = position - static_cast<int>(patterns_[patternIndex].size()) + 1;
                matches.push_back({start, patternIndex});
            }
        }

        return matches;
    }

private:
    struct Node {
        array<int, 26> next;
        int failure = 0;
        vector<int> output;

        Node() { next.fill(-1); }
    };

    void insert(const string& pattern, int index) {
        int node = 0;
        for (char letter : pattern) {
            int c = letter - 'a';
            if (nodes_[node].next[c] == -1) {
                nodes_[node].next[c] = static_cast<int>(nodes_.size());
                nodes_.push_back(Node{});
            }
            node = nodes_[node].next[c];
        }
        nodes_[node].output.push_back(index);
    }

    void buildFailureLinks() {
        queue<int> pending;

        for (int c = 0; c < 26; ++c) {
            int child = nodes_[0].next[c];
            if (child != -1) {
                nodes_[child].failure = 0;
                pending.push(child);
            } else {
                nodes_[0].next[c] = 0;
            }
        }

        while (!pending.empty()) {
            int current = pending.front();
            pending.pop();

            for (int c = 0; c < 26; ++c) {
                int child = nodes_[current].next[c];

                if (child != -1) {
                    nodes_[child].failure = nodes_[nodes_[current].failure].next[c];
                    pending.push(child);

                    // Patterns that end at the failure node also end here.
                    const vector<int>& inherited =
                        nodes_[nodes_[child].failure].output;
                    nodes_[child].output.insert(nodes_[child].output.end(),
                                                inherited.begin(), inherited.end());
                } else {
                    nodes_[current].next[c] = nodes_[nodes_[current].failure].next[c];
                }
            }
        }
    }

    vector<string> patterns_;
    vector<Node> nodes_;
};

int main() {
    vector<string> patterns = {"he", "she", "his", "hers"};
    string text = "ushers";
    AhoCorasick matcher(patterns);

    cout << "text: " << text << "\npatterns: ";
    for (const string& pattern : patterns) cout << pattern << ' ';
    cout << "\n\nmatches:\n";

    for (const auto& [position, index] : matcher.search(text)) {
        cout << "  \"" << patterns[index] << "\" at index " << position << '\n';
    }

    return 0;
}
