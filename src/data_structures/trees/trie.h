#ifndef DSA_TRIE_H
#define DSA_TRIE_H

#include <array>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

// ---------------------------------------------------------------------------
// Trie (prefix tree)
//
// Each node represents one prefix. A child pointer labelled 'a'..'z' leads to
// the prefix with that letter appended. `terminal` marks a complete word.
//
// Looking up a string of length L costs O(L), independent of how many words
// are stored. The price is memory: up to 26 pointers per node.
//
// Only lowercase letters 'a'..'z' are accepted.
// ---------------------------------------------------------------------------
class Trie {
public:
    Trie() : root_(std::make_unique<Node>()) {}

    void insert(const std::string& word) {
        Node* current = root_.get();

        for (char letter : word) {
            int index = letterIndex(letter);
            if (!current->children[index]) {
                current->children[index] = std::make_unique<Node>();
            }
            current = current->children[index].get();
        }

        current->terminal = true;
    }

    bool contains(const std::string& word) const {
        const Node* node = findNode(word);
        return node != nullptr && node->terminal;
    }

    bool startsWith(const std::string& prefix) const {
        return findNode(prefix) != nullptr;
    }

    // All stored words that begin with `prefix`, in alphabetical order.
    std::vector<std::string> wordsWithPrefix(const std::string& prefix) const {
        std::vector<std::string> words;
        const Node* node = findNode(prefix);
        if (!node) return words;

        collect(node, prefix, words);
        return words;
    }

    int countWords() const { return countWords(root_.get()); }

private:
    struct Node {
        std::array<std::unique_ptr<Node>, 26> children{};
        bool terminal = false;
    };

    static int letterIndex(char letter) {
        if (letter < 'a' || letter > 'z') {
            throw std::invalid_argument("Trie: only lowercase a-z is supported");
        }
        return letter - 'a';
    }

    const Node* findNode(const std::string& prefix) const {
        const Node* current = root_.get();

        for (char letter : prefix) {
            int index = letterIndex(letter);
            if (!current->children[index]) return nullptr;
            current = current->children[index].get();
        }

        return current;
    }

    static void collect(const Node* node, const std::string& prefix,
                        std::vector<std::string>& words) {
        if (node->terminal) words.push_back(prefix);

        for (int index = 0; index < 26; ++index) {
            if (!node->children[index]) continue;
            collect(node->children[index].get(),
                    prefix + static_cast<char>('a' + index), words);
        }
    }

    static int countWords(const Node* node) {
        int total = node->terminal ? 1 : 0;
        for (const auto& child : node->children) {
            if (child) total += countWords(child.get());
        }
        return total;
    }

    std::unique_ptr<Node> root_;
};

#endif // DSA_TRIE_H
