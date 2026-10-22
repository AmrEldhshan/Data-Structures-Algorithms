#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Huffman coding (greedy)
//
// Build a binary tree in which frequent characters have short codes. Repeatedly
// merge the two least frequent nodes; a min-priority queue makes each merge
// O(log n).
//
// The resulting code is prefix-free: no code is a prefix of another, so the
// bit stream can be decoded without separators.
//
// Time:  O(n log n)
// Space: O(n)
// ---------------------------------------------------------------------------
struct Node {
    char letter;
    int frequency;
    shared_ptr<Node> left;
    shared_ptr<Node> right;

    bool isLeaf() const { return !left && !right; }
};

struct Compare {
    bool operator()(const shared_ptr<Node>& a, const shared_ptr<Node>& b) const {
        return a->frequency > b->frequency; // min-heap
    }
};

void buildCodes(const shared_ptr<Node>& node, const string& prefix,
                unordered_map<char, string>& codes) {
    if (!node) return;

    if (node->isLeaf()) {
        codes[node->letter] = prefix.empty() ? "0" : prefix;
        return;
    }

    buildCodes(node->left, prefix + "0", codes);
    buildCodes(node->right, prefix + "1", codes);
}

int main() {
    string text = "abracadabra";
    unordered_map<char, int> frequencies;
    for (char letter : text) ++frequencies[letter];

    priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, Compare> queue;

    for (const auto& [letter, frequency] : frequencies) {
        queue.push(make_shared<Node>(Node{letter, frequency, nullptr, nullptr}));
    }

    while (queue.size() > 1) {
        shared_ptr<Node> first = queue.top();
        queue.pop();
        shared_ptr<Node> second = queue.top();
        queue.pop();

        auto parent = make_shared<Node>(
            Node{'\0', first->frequency + second->frequency, first, second});
        queue.push(parent);
    }

    shared_ptr<Node> root = queue.top();
    unordered_map<char, string> codes;
    buildCodes(root, "", codes);

    cout << "text: " << text << "\n\n";
    cout << "Huffman codes:\n";
    for (const auto& [letter, code] : codes) {
        cout << "  " << letter << " : " << code << '\n';
    }

    int encodedBits = 0;
    for (char letter : text) encodedBits += static_cast<int>(codes[letter].size());
    cout << "\noriginal bits (8 per char): " << text.size() * 8 << '\n';
    cout << "encoded bits:               " << encodedBits << '\n';

    return 0;
}
