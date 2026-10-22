#ifndef DSA_RADIX_TREE_H
#define DSA_RADIX_TREE_H

#include <algorithm>
#include <cstddef>
#include <map>
#include <memory>
#include <string>
#include <vector>

// ---------------------------------------------------------------------------
// Radix tree (compressed trie)
//
// A trie whose single-child chains are compressed into one edge label. Each
// node stores an edge string and a map from the first character of each child
// edge to the child. Insertion splits an edge when the new word diverges.
//
// insert / contains: O(length of key)
// ---------------------------------------------------------------------------
class RadixTree {
public:
    RadixTree() : root_(std::make_unique<Node>()) {}

    void insert(const std::string& word) {
        Node* node = root_.get();
        std::size_t position = 0;

        while (position < word.size()) {
            char first = word[position];
            auto iterator = node->children.find(first);

            if (iterator == node->children.end()) {
                auto child = std::make_unique<Node>();
                child->edge = word.substr(position);
                child->terminal = true;
                node->children[first] = std::move(child);
                ++size_;
                return;
            }

            Node* child = iterator->second.get();
            std::size_t common = 0;
            while (common < child->edge.size() &&
                   position + common < word.size() &&
                   child->edge[common] == word[position + common]) {
                ++common;
            }

            if (common == child->edge.size()) {
                position += common;
                node = child;
                continue;
            }

            // Split the existing edge at the divergence point.
            auto split = std::make_unique<Node>();
            split->edge = child->edge.substr(common);
            split->terminal = child->terminal;
            split->children = std::move(child->children);

            child->edge = child->edge.substr(0, common);
            child->terminal = false;
            child->children.clear();
            child->children[split->edge[0]] = std::move(split);

            position += common;

            if (position == word.size()) {
                child->terminal = true;
                ++size_;
                return;
            }

            auto leaf = std::make_unique<Node>();
            leaf->edge = word.substr(position);
            leaf->terminal = true;
            child->children[word[position]] = std::move(leaf);
            ++size_;
            return;
        }

        if (!node->terminal) {
            node->terminal = true;
            ++size_;
        }
    }

    bool contains(const std::string& word) const {
        const Node* node = root_.get();
        std::size_t position = 0;

        while (position < word.size()) {
            auto iterator = node->children.find(word[position]);
            if (iterator == node->children.end()) return false;

            const Node* child = iterator->second.get();
            if (word.compare(position, child->edge.size(), child->edge) != 0) {
                return false;
            }

            position += child->edge.size();
            node = child;
        }

        return node->terminal;
    }

    // True when `prefix` labels a path, even if it ends inside an edge.
    bool containsPrefix(const std::string& prefix) const {
        const Node* node = root_.get();
        std::size_t position = 0;

        while (position < prefix.size()) {
            auto iterator = node->children.find(prefix[position]);
            if (iterator == node->children.end()) return false;

            const Node* child = iterator->second.get();
            std::size_t remaining = prefix.size() - position;
            std::size_t compareLength = std::min(remaining, child->edge.size());

            if (child->edge.compare(0, compareLength,
                                    prefix, position, compareLength) != 0) {
                return false;
            }

            if (remaining <= child->edge.size()) return true;

            position += child->edge.size();
            node = child;
        }

        return true;
    }

    std::vector<std::string> words() const {
        std::vector<std::string> result;
        collect(root_.get(), "", result);
        return result;
    }

    // Number of stored words that start with `prefix`.
    std::size_t countPrefix(const std::string& prefix) const {
        const Node* node = root_.get();
        std::size_t position = 0;

        while (position < prefix.size()) {
            auto iterator = node->children.find(prefix[position]);
            if (iterator == node->children.end()) return 0;

            const Node* child = iterator->second.get();
            std::size_t remaining = prefix.size() - position;
            std::size_t compareLength = std::min(remaining, child->edge.size());

            if (child->edge.compare(0, compareLength,
                                    prefix, position, compareLength) != 0) {
                return 0;
            }

            if (remaining <= child->edge.size()) return countTerminals(child);

            position += child->edge.size();
            node = child;
        }

        return countTerminals(node);
    }

    std::size_t size() const { return size_; }

private:
    struct Node {
        std::string edge;
        bool terminal = false;
        std::map<char, std::unique_ptr<Node>> children;
    };

    std::unique_ptr<Node> root_;
    std::size_t size_ = 0;

    static std::size_t countTerminals(const Node* node) {
        std::size_t result = node->terminal ? 1 : 0;
        for (const auto& entry : node->children) {
            result += countTerminals(entry.second.get());
        }
        return result;
    }

    static void collect(const Node* node, const std::string& prefix,
                        std::vector<std::string>& result) {
        if (node->terminal) result.push_back(prefix);

        for (const auto& [character, child] : node->children) {
            (void)character;
            collect(child.get(), prefix + child->edge, result);
        }
    }
};

#endif
